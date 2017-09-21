#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node * next;
} Node;
typedef struct {
	Node * top;
	Node * base;
} Stack;
typedef enum {OK, ERROR, WARNING} Status;
Status initStack(Stack * stack){
	stack->base = (Node *) malloc(sizeof(Node));
	stack->base->data = 0;
	stack->base->next = NULL;
	stack->top = stack->base;
	return OK;
}
void push(Stack * stack,int value){
	Node * p = (Node *) malloc(sizeof(Node));
	p->data = value;
	p->next = stack->top;
	stack->top = p;
	stack->base->data += 1;
}
Status pop(Stack * stack, int * value){
	if(stack->top == stack->base) return WARNING;
	*value = stack->top->data;
	return OK;
}
Status stackTraverse(Stack * stack, Status (*func)(Stack *)){
	return func(stack);
}
Status printStack(Stack * stack){
	Node * p = stack->top;
	if(p == stack->base) return WARNING;
	while(p != stack->base){
		printf("%d  ",p->data);
		p = p->next;
	}
	return OK;
}
int main(){
	Stack stack;
	initStack(&stack);
	stackTraverse(&stack, printStack);
	printf("\n");
	return 0;
}
