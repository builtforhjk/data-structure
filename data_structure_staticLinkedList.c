#include <stdio.h>
#include <stdlib.h>
#define element_type int
#define capacity 20
typedef struct{
	element_type data;
	int cur;
}staticLinkList;
typedef enum {OK, ERROR, WARNINIG} Status;
Status init_SL(staticLinkList ** sL){
	*sL = (staticLinkList *)malloc(sizeof(staticLinkList)*(capacity+1));
	if(!sL) return ERROR;
	(*sL)[0].data = 0;
	(*sL)[0].cur = 0;
	return OK;
}
Status print_SL(staticLinkList * sL){
	if(!sL[0].data) return WARNINIG;
	int i = sL[0].cur;
	for(;i != 0; i = sL[i].cur){
		printf("%d ",sL[i].data);
	}
	return OK;
}
Status thePrint_SL(staticLinkList * sL){
	if(!sL[0].data) return WARNINIG;
	int i = 0;
	for(;i <= sL[0].data; ++i){
		printf("%d ",sL[i].cur);
	}
	return OK;
}
Status insert_SL(staticLinkList ** sL, int value, int pos){
	if((*sL)[0].data >= capacity) return WARNINIG;
	if(!pos) return WARNINIG;
	int op = 0;
	int i = 0;
	while(i+1 != pos){
		op = (*sL)[op].cur;
		++i;
		if(i > (*sL)[0].data) return ERROR;
	}
	(*sL)[(*sL)[0].data+1].data = value;
	(*sL)[(*sL)[0].data+1].cur = (*sL)[op].cur;
	(*sL)[0].data += 1;
	(*sL)[op].cur = (*sL)[0].data;
	return OK;
}
int main(){
	staticLinkList * SL_list;
	init_SL(&SL_list);
	insert_SL(&SL_list, 10, 1);
	insert_SL(&SL_list, 20, 1);
	insert_SL(&SL_list, 15, 3);
	print_SL(SL_list);
	printf("\n");
	thePrint_SL(SL_list);
	return 0;
}
