#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cilk/cilk.h>
#include <cmath>

using namespace std;

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

template <class E, class F>
E* reduce_w_partial_prefix(E *In, int n, F f){
	E* Out = map(In, [](int x){return x;});
	for(int i = 0; i < log2(n); i++){
		int d = pow(2,i+1);
		cilk_for(int j = pow(2,i)-1; j < n; j+=d){
			int next = j+(d/2);
			if (next<n){ Out[next]+=Out[j];}	
		}
	}
	return Out;
}

template <class E, class F>
E reduce(E *In, int n, F f){ 
	E* Out = reduce_w_partial_prefix(In, n, f);
	E result = Out[n-1];
	free(E);
	return result;
}

int main(){
	cout << "parallel functional interface written by Natcha Simsiri\n";
	int A[] = {1,2,3};
	int *B = map(A, sizeof(A)/sizeof(int), [](int x){return x;});
	for(int i = 0 ; i < sizeof(A)/sizeof(int); i++){
		cout << B[i] << " ";
	}
}
