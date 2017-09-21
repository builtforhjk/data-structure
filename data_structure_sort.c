#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef int ElemType;
void quickSort(int * src, int left, int right){
	if(left < right){
		ElemType pivot = src[left];
		int low = left, high = right;
		while(low < high){
			while(low < high && src[high]>=pivot) --high;
			if(low == high) break;
			src[low] = src[high];
			++low;
			while(low < high && src[low]<=pivot) ++low;
			if(low == high) break;
			src[high] = src[low];
			--high;
		}
		int pos = (low+high)/2;
		src[pos] = pivot;
		quickSort(src, left, pos-1);
		quickSort(src,pos+1,right);
	}
}
void divideEvenAndOdd(int * src, int size){
	int left = 0, right = size-1;
	int pivot = src[0];
	while(left < right){
		while(left < right && src[right]%2 == 0) --right;
		src[left] = src[right];
		while(left < right && src[left]%2) ++left;
		src[right] = src[left];
	}
	src[left] = pivot;
}
//*****************************
typedef struct{
	ElemType * base;
	int flag;
}Heap;
void heapInit(Heap * H){
	H->base = (ElemType *)malloc(sizeof(ElemType)*100);
}
void heapAdjust(Heap * H, int i){
	int j = i * 2;
	ElemType temp = H->base[i];
	while(j <= H->base[0]){
		if(j < H->base[0] && H->base[j+1] > H->base[j]) ++j;
		if(H->base[j] > temp){
			H->base[i] = H->base[j];
			i = j;
		}
		else break;
		j *= 2;
	}
	H->base[i] = temp;
}
void buildMaxHeap(Heap * H){
	H->flag = 1;
	int i = H->base[0]/2;
	for(; i > 0; --i){
		heapAdjust(H,i);
	}
}
void heapSort(Heap * H){
	buildMaxHeap(H);
	int i = H->base[0];
	int k = i;
	for(; i > 1; --i){
		ElemType temp = H->base[1];
		H->base[1] = H->base[H->base[0]];
		H->base[H->base[0]] = temp;
		--H->base[0];
		heapAdjust(H, 1);
	}
	H->base[0] = k;
}
int main(){
	srand((unsigned int)time(0));
	Heap * H = (Heap *)malloc(sizeof(Heap));
	heapInit(H);
	H->base[0] = 10;
	printf("%d:\n",H->base[0]);
	int i = 1;
	for(; i <= H->base[0]; ++i){
		H->base[i] = (ElemType)rand()%100+1;
		printf("%d ",H->base[i]);
	}
	printf("\n");
	heapSort(H);
	for(i = 1; i <= H->base[0]; ++i){
		printf("%d ",H->base[i]);
	}
	printf("\n%d\n",H->flag);
}