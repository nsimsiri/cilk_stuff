#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cmath>
#include "utils.h"

using namespace std;



template <class E> void printA(E *In, int n){for(int i = 0; i < n;i++){cout<<In[i]<<" ";};cout<<endl;}

template <class T>
T* newA(int n, T value){
	T* A = (T*)malloc(n*sizeof(T));
	cilk_for(int i =0; i < n; i++){A[i] = value;}
	return A;
}

template <class E, class F>
E* map(E* In, int n, F f){
	E* Out = newA(n, 0);
	cilk_for(int i = 0; i < n; i++){ Out[i]=f(In[i]);}
	return Out;
}

template <class E> E* cloneA(E* In, int n){return map(In, n, [](int x){return x;});}

template <class E, class BinaryPredicateF>
E* serial_scan(E *In, int n, BinaryPredicateF f){
	E* Out = cloneA(In, n);
	for(int i =1 ; i < n; i++){
		Out[i]=f(Out[i], Out[i-1]);
	}
	return Out;
}



template <class E, class BinaryPredicateF>
E* reduce_w_partial_prefix(E *In, int n, BinaryPredicateF f){
	E* Out = cloneA(In, n);
	for(int i = 0; i < (int)ceil(log2(n)); i++){
		int d = pow(2,i+1);
		cilk_for(int j = pow(2,i)-1; j < n-1; j+=d){
			if (j+d/2>=n) Out[n-1]=f(Out[n-1], Out[j]);
			else Out[j+d/2]=f(Out[j+d/2],Out[j]);
		}
	}
	return Out;
}

template <class E, class BinaryPredicateF>
void prescan_partial_prefix(E *In, int st, int mid, int ed, E value, BinaryPredicateF f){
	In[mid]= f(In[mid], value);
	printf("ST=%d MID=%d ED=%d\n", st, mid, ed);
	if (mid%2!=0){
		prescan_partial_prefix(In, st, (mid+st)/2, mid, value, f);
		prescan_partial_prefix(In, mid+1, (mid+1+ed)/2, ed, In[mid], f);
	}
}

// main functional interface //
template <class E, class BinaryPredicateF>
E* scan(E *In, int n, BinaryPredicateF f){
	if (n<=1) return In;
	E* Out = cloneA(In, n);
	Out = reduce_w_partial_prefix(Out, n, f);
	printA(Out, n);
	int end = 1;
	if (n%2==0) end=0;
	int root = ((int)pow(2,(int)log2(n-end))-1);
	prescan_partial_prefix(Out, 0, root, n-end, 0, f); 
	return Out;
}

template <class E, class F>
E reduce(E *In, int n, F f){ 
	E* Out = reduce_w_partial_prefix(In, n, f);
	E result = Out[n-1];
	free(Out);
	return result;
}


int main(int argc, char* argv[]){
	cout << "parallel functional interface written by Natcha Simsiri\n";
	// int A[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17}
	// int A[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	// int n = sizeof(A)/sizeof(int);
	// // int *B = map(A, sizeof(A)/sizeof(int), [](int x){return x;});
	// int *B = reduce_w_partial_prefix(A, n, [](int a, int b){ return a+b; }); 
	// printA(B, sizeof(A)/sizeof(int));

	// int C[] = {1,2,3,4,5};
	// printf("serial-scan: ");
	// int* C1 = serial_scan(C, sizeof(C)/sizeof(int), SumF<int>());
	// printA(C1, sizeof(C)/sizeof(int));
	// int *C2=scan(C, sizeof(C)/sizeof(int), [](int a, int b){ return a+b; });
	// printf("parallel-scan: ");
	// printA(C2, sizeof(C)/sizeof(int));
	int N = 5;
	if (argc > 1) N = atoi(argv[1]);
	int *D = newA(N, 1);
	printf("[Test Scan - input is array of 1's]\n");
	// printf("serial-scan: ");
	// int *D1 = serial_scan(D, N, SumF<int>());
	// printA(D1, N);
	printf("parallel-scan: ");
	int *D2 = scan(D, N, SumF<int>());
	printA(D2, N);




}
