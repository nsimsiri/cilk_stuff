
#include <iostream>
#include <algorithm>
#include <cilk/cilk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

template <class E>
void print(E *A, int n){
	for(int i = 0; i < n; i++){
		printf("%d ", A[i]);
	}
	printf("\n");


template <class E>
E* newA(int n, E k){
	E* A = (E*) malloc(n*sizeof(E));
	cilk_for(int i = 0; i < n; i++){A[i]=k;}
	return A;
}

template <class F>
int filter(int* A, int n, F f){
	bool *B = newA<bool>(n, 0);
	cilk_for(int i = 0; i < n; i++){
		if (f(A[i])) B[i] = true;
		else B[i] = false;
	}
	print<bool>(B, n);
	print<int>(A, n);
	free(B);
	return n;
}

struct isLessThanPivot { 
	int pivot; 
	isLessThanPivot(int j): pivot(j){};
	bool operator() (int x) {return x<pivot;}
};

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void partition(int *A, int start, int end, int *p){
	end = end-1;
	int pivot = A[end];
	int j = start-1;
	for(int i = start; i < end; i++){
		if (A[i] <= pivot){
			j+=1;
			swap(&A[i], &A[j]);
		}
	}	
	swap(&A[j+1], &A[end]);
	*p = j+1;
}


void quicksort(int* A, int l, int r){
	srand(time(NULL));
	if (r-l==2){
		if (A[l]>A[r-1]) swap(&A[l], &A[r-1]);
	} else if (r-l>2) {
		int p = l+(rand()%(r-l));
		swap(&A[p], &A[r-1]);
		partition(A, l, r, &p);
		cilk_spawn quicksort(A, l, p);
		quicksort(A, p+1, r);
		cilk_sync;
	}
}


int main(){
	int A[] = {1,9,2,6,3,5};
	isLessThanPivot F = isLessThanPivot(5);
	filter(A, sizeof(A)/sizeof(int), F);

	// quicksort(A, 0, sizeof(A)/sizeof(int	// int p = -1;
	// partition(A, 0, (sizeof(A)/sizeof(int)), &p);
	// print(A, sizeof(A)/sizeof(int));
	// printf("\n%d\n", p);));



}