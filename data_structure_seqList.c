#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define capacity 100
#define NaN 999999
typedef int element_type;
typedef struct{
	element_type * list;
	int length;
	int size;
}seqList;
typedef enum {OK,ERROR,WARNING}status;
status initSeqList(seqList * L){
	L->list = (element_type *) malloc(sizeof(element_type)*capacity);
	L->length = 0;
	L->size = capacity;
	if(!L) return ERROR;
	else return OK;
}
status destroyList(seqList * L){
	free(L);
	return OK;
}
status getMinElement(seqList * L,int * pos,int * value){
	if(!L->length) {
		*pos = *value = NaN;
		return ERROR;
	}
	*value = L->list[0];
	int i = 1;
	for(; i < L->length; ++i){
		if(L->list[i] < *value){
			*pos = i;
			*value = L->list[i];
		}
	}
	return OK;
}
status removeMinElement(seqList * L, int * value){
	int pos = 0;
	if(getMinElement(L, &pos, value) == OK){
		L->list[pos] = L->list[L->length-1];
		--L->length;
		return OK;
	}
	return WARNING;
}
void printList(seqList * L){
	int i = 0;
	while(i < L->length){
		printf("%d  ",L->list[i]);
		++i;
	}
}
int main(){
	srand((unsigned int)time(0));
	seqList list;
	initSeqList(&list);
	int i = 0;
	for(; i < 20; ++i){
		list.list[i] = rand()%100+1;
	}
	list.length = 20;
	printList(&list);
	int value = 0;
	printf("\n");
	removeMinElement(&list, &value);
	printf("%d\n",value);
	printList(&list);
	printf("\n");
	return 0;
}
