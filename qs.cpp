#include<iostream>
#include<cilk/cilk.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;


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



void print(int *A, int n){
	for(int i = 0; i < n; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
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
	quicksort(A, 0, sizeof(A)/sizeof(int));
	// int p = -1;
	// partition(A, 0, (sizeof(A)/sizeof(int)), &p);
	print(A, sizeof(A)/sizeof(int));
	// printf("\n%d\n", p);


}