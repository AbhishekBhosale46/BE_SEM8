#include<bits/stdc++.h>
#include<cstdlib>
#include<ctime>
#include<omp.h>
using namespace std;

long long maxSeq(vector<long long> &arr){
    long long maximum = arr[0];
    for(long long i=0; i<arr.size(); i++){
        if(arr[i]>maximum){
            maximum = arr[i];
        }
    }
    return maximum;
}

long long maxPar(vector<long long> &arr){
    long long maximum = arr[0];
    #pragma omp parallel for reduction(max:maximum)
    for(long long i=0; i<arr.size(); i++){
        if(arr[i]>maximum){
            maximum = arr[i];
        }
    }
    return maximum;
}

long long minSeq(vector<long long> &arr){
    long long minimum = arr[0];
    for(long long i=0; i<arr.size(); i++){
        if(arr[i]<minimum){
            minimum = arr[i];
        }
    }
    return minimum;
}

long long minPar(vector<long long> &arr){
    long long minimum = arr[0];
    #pragma omp parallel for reduction(min:minimum)
    for(long long i=0; i<arr.size(); i++){
        if(arr[i]<minimum){
            minimum = arr[i];
        }
    }
    return minimum;
}

long long sumSeq(vector<long long> &arr){
    long long sum = 0;
    for(long long i=0; i<arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

long long sumPar(vector<long long> &arr){
    long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(long long i=0; i<arr.size(); i++){
        sum += arr[i];
    }
    return sum;
}

int main(){

    long long n = 1000000;
    vector<long long> arr(n);

    srand(time(0));
    for(int i=0; i<n; i++){
        arr.push_back(rand()%1000);
    }

    double start = omp_get_wtime();
    maxSeq(arr);
    double end = omp_get_wtime();
    cout<<"Max Seq time : "<<end-start<<endl;

    start = omp_get_wtime();
    maxPar(arr);
    end = omp_get_wtime();
    cout<<"Max Par time : "<<end-start<<endl;

    return 0;
}