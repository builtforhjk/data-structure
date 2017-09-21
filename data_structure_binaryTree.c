#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node{
	int weight;
	struct Node * lchild;
	struct Node * rchild;
}Node, *BITree;
BITree root;
typedef enum{OK, ERROR, WARNING}Status;
typedef union{
	int _var_1;
	Node * _var_2;
	Status _var_3;
}_returnType;
void BITree_insert(BITree * T, int value){
	if(!(*T)){
		*T = (BITree)malloc(sizeof(Node));
		(*T)->weight = value;
		(*T)->lchild = (*T)->rchild = NULL;
	}
	else{
		if(value < (*T)->weight) BITree_insert(&(*T)->lchild,value);
		else if(value > (*T)->weight) BITree_insert(&(*T)->rchild,value);
		else return;
	}
}
Status BITree_init(BITree * T, const int value[],const int size){
	*T = (BITree)malloc(sizeof(Node));
	if(!(*T)) return ERROR;
	if(size == 0) return WARNING;
	int i = 1;
	(*T)->weight = value[0];
	(*T)->lchild = (*T)->rchild = NULL;
	while(i < size){
		BITree_insert(T,value[i]);
		++i;
	}
	return OK;
}
void BITree_inOrderTraversal(BITree T, _returnType (* func)(BITree)){
	if(!T) return;
	BITree_inOrderTraversal(T->lchild,func);
	func(T);
	BITree_inOrderTraversal(T->rchild,func);
}
void BITree_preOrderTraversal(BITree T, _returnType (* func)(BITree)){
	if(!T) return;
	func(T);
	BITree_preOrderTraversal(T->lchild,func);
	BITree_preOrderTraversal(T->rchild,func);
}
void BITree_postOrderTraversal(BITree T, _returnType (* func)(BITree)){
	if(!T) return;
	BITree_postOrderTraversal(T->lchild,func);
	BITree_postOrderTraversal(T->rchild,func);
	func(T);
}
void BITree_levelTraversal(BITree T, _returnType (* func)(BITree)){
	Node queue[10000];
	int head = 0, rear = 0;
	queue[rear++] = *T;
	while(rear != head){
		Node tmp = queue[head++];
		if(tmp.lchild) queue[rear++] = *(tmp.lchild);
		if(tmp.rchild) queue[rear++] = *(tmp.rchild);
		func(&tmp);
	}
}
_returnType Tprint(Node * node){
	_returnType state;
	state._var_3 = ERROR;
	if(!node) return state;
	printf("[%d] ",node->weight);
	state._var_3 = OK;
	return state;
}
int BITree_depth(BITree T){
	if(!T) return 0;
	int left = BITree_depth(T->lchild)+1;
	int right = BITree_depth(T->rchild)+1;
	return (left>right?left:right);
}
_returnType Tsize(BITree T){
	static _returnType count;
	++count._var_1;
	return count;
}
void BITree_sort(BITree T){
	BITree_inOrderTraversal(T, Tprint);
}
int BITree_size(BITree T){
	BITree_inOrderTraversal(T, Tsize);
	return Tsize(T)._var_1-1;
}
void BITree_LLRotate(Node * cur, Node * parent,int direct){
	Node * tmp = cur->lchild;
	cur->lchild = tmp->rchild;
	tmp->rchild = cur;
	if(cur == root) root = tmp;
	else if(direct) parent->rchild = tmp;
	else parent->lchild = tmp;
}
void BITree_RRRotate(Node * cur, Node * parent, int direct){
	Node * tmp = cur->rchild;
	cur->rchild = tmp->lchild;
	tmp->lchild = cur;
	if(cur == root) root = tmp;
	else if(direct) parent->rchild = tmp;
	else parent->lchild = tmp;
}
void BITree_RLRatate(Node * cur, Node * parent){
	BITree_LLRotate(cur->rchild, cur,1);
	BITree_RRRotate(cur, parent,1);
}
void BITree_LRRatate(Node * cur, Node * parent){
	BITree_RRRotate(cur->lchild,cur,0);
	BITree_LLRotate(cur, parent, 0);
}
int main(){
	int value[3] = {88,70,61};
	BITree_init(&root, value, 3);
	BITree_LLRotate(root, NULL, 0);
	BITree_levelTraversal(root, Tprint);
	printf("\n");
	BITree_insert(&root, 96);
	BITree_insert(&root, 120);
	BITree_RRRotate(root->rchild, root, 1);
	BITree_levelTraversal(root, Tprint);
	printf("\n");
	BITree_insert(&root, 90);
	BITree_RLRatate(root, NULL);
	BITree_levelTraversal(root, Tprint);
	printf("\n");
	BITree_insert(&root, 65);
	BITree_LRRatate(root->lchild, root);
	BITree_levelTraversal(root, Tprint);
	printf("\n");
	return 0;
}
