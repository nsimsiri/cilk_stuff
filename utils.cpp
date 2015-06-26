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

template <class Array, class F>
int reduce(Array *Out, Array *In, int n, F f){
	for(int i = 0; i < log2(n); i++){
		cilk_for(int j = 0; j < n)
	}
}

int main(){
	cout << "parallel functional interface written by Natcha Simsiri\n";
}
