#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10
typedef struct Node{
	int tail;
	int head;
	int weigh;
	struct Node * next;
}Edge;
typedef struct{
	int data;
	int order;
	Edge * adjEdge;
}Vex;
typedef struct{
	Vex * base;
	int size;
}VexList;
typedef enum{OK, ERROR, WARNING}Status;
typedef struct{
	int _x;
	int _y;
	int _z;
}Triple;
Status graph_init(VexList * v){
	if(!v) return ERROR;
	v->base = (Vex*)malloc(sizeof(Vex)*MAXSIZE);
	int i = 0;
	for(;i < MAXSIZE; ++i){
		v->base[i].order = i+1;
		v->base[i].data = 0;
		v->base[i].adjEdge = NULL;
	}
	if(!v->base) return ERROR;
	v->size = MAXSIZE;
	return OK;
}
Status graph_appendEdge(VexList * v, int tail, int head, int weigh){
	if(!v) return ERROR;
	if(tail > v->size || tail < 1 || head > v->size || head < 1) return ERROR;
	Edge * e = (Edge *)malloc(sizeof(Edge));
	if(!e) return ERROR;
	e->tail = tail;
	e->head = head;
	e->weigh = weigh;
	e->next = NULL;
	if(v->base[tail-1].adjEdge == NULL) v->base[tail-1].adjEdge = e;
	else{
		Edge * p = v->base[tail-1].adjEdge;
		while(p->next) p = p->next;
		p->next = e;
	}
	Edge * r = (Edge *)malloc(sizeof(Edge));
	if(!r) return ERROR;
	r->tail = head;
	r->head = tail;
	r->weigh = weigh;
	r->next = NULL;
	if(v->base[head-1].adjEdge == NULL) v->base[head-1].adjEdge = r;
	else{
		Edge * q = v->base[head-1].adjEdge;
		while(q->next) q = q->next;
		q->next = r;
	}
	return OK;
}
Status DFS_finished(int visited[],int size){
	int i = 0;
	for(;i < size; ++i){
		if(!visited[i]) return WARNING;
	}
	return OK;
}
void DFS(VexList * v, int start, int visited[],int size){
	if(!v || start > v->size || start < 1) return;
	if(visited[start-1] == 1) return;
	visited[start-1] = 1;
	if(DFS_finished(visited,size) == OK){
		printf("[%d]",start);
		return;
	}
	printf("[%d] ",start);
	Edge * e = v->base[start-1].adjEdge;
	while(e){
		DFS(v, e->head,visited,size);
		e = e->next;
	}
}
int main(){
	VexList * graph_vexList = (VexList*)malloc(sizeof(VexList));
	graph_init(graph_vexList);
	Triple buffer[100] = {
		{1,2,10},{1,3,10},{1,4,10},{2,3,10},
		{2,4,10},{2,5,10},{3,4,10},{4,5,10}
	};
	int i = 0;
	for(;i < 8;++i){
		graph_appendEdge(graph_vexList, buffer[i]._x,buffer[i]._y,buffer[i]._z);
	}
	int visited[MAXSIZE] = {0};
	DFS(graph_vexList, 1, visited,5);
	printf("\n");
	return 0;
}
