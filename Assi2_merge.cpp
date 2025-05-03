#include<bits/stdc++.h>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right){

    int n1 = mid-left+1;
    int n2 = right-mid;
    vector<int> arrLeft, arrRight;

    for(int i=0; i<n1; i++){
        arrLeft.push_back(arr[left+i]);
    }

    for(int j=0; j<n2; j++){
        arrRight.push_back(arr[mid+1+j]);
    }

    int i = 0;
    int j = 0;
    int k = left;
    while(i<n1 && j<n2){
        if(arrLeft[i]<=arrRight[j]){
            arr[k] = arrLeft[i];
            i++;
        }else{
            arr[k] = arrRight[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = arrLeft[i];
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = arrRight[j];
        j++;
        k++;
    }

}

void mergeSort(vector<int> &arr, int left, int right){
    if(left<right){
        int mid = left+(right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(vector<int> &arr, int left, int right){
    if(left<right){
        int mid = left + (right-left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);
            #pragma omp section
            parallelMergeSort(arr, mid+1, right);
        }
        merge(arr, left, mid, right);
    }
}

int main(){

    vector<int> arr(500000);
    
    srand(time(0));
    for(int i=0; i<500000; i++){
        arr[i] = rand();
    }

    vector<int> arrSeq = arr;
    vector<int> arrPar = arr;

    double start = omp_get_wtime();
    mergeSort(arrSeq, 0, 500000-1);
    double end = omp_get_wtime();
    cout << "Sequential Time: " << end - start << " seconds" << endl;

    start = omp_get_wtime();
    parallelMergeSort(arrPar, 0, 500000-1);
    end = omp_get_wtime();
    cout << "Parallel Time: " << end - start << " seconds" << endl;

    bool same = (arrSeq == arrPar);
    cout << "Sorting correctness: " << (same ? "PASSED" : "FAILED") << endl;

    return 0;
}