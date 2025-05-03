#include<bits/stdc++.h>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void bubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        int phase = i%2;
        #pragma omp parallel for default(none) shared(arr, n, phase)
        for(int j=phase; j<n-1; j+=2){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}


int main(){
    
    vector<int> arr(10000);
    
    srand(time(0));
    for(int i=0; i<10000; i++){
        arr[i] = rand();
    }

    vector<int> arrSeq = arr;
    vector<int> arrPar = arr;

    double start = omp_get_wtime();
    bubbleSort(arrSeq);
    double end = omp_get_wtime();
    cout << "Sequential Time: " << end - start << " seconds" << endl;

    start = omp_get_wtime();
    parallelBubbleSort(arrPar);
    end = omp_get_wtime();
    cout << "Parallel Time: " << end - start << " seconds" << endl;

    bool same = (arrSeq == arrPar);
    cout << "Sorting correctness: " << (same ? "PASSED" : "FAILED") << endl;

    return 0;
}