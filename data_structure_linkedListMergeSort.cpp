#include <iostream>
#include <time.h>
using namespace std;
struct ListNode{
	int val;
	ListNode * next;
	ListNode(int x):val(x),next(NULL){}
	ListNode(){};
};
class SingleLinkedList{
public:
	SingleLinkedList():root(NULL),tail(NULL),length(0){}
	void append(int value){
		ListNode * temp = new ListNode(value);
		if(!length){
			root = temp;
			tail = root;
		}
		else{
			tail->next = temp;
			tail = tail->next;
		}
		++length;
	}
	void sort(){
		root = sortList();
	}
	ListNode * sortList(){
		return mergeSort(root, tail);
	}
	ListNode * mergeSort(ListNode * begin, ListNode * end){
		if(begin->next == NULL){
			return begin;
		}
		else if(begin->next->next == NULL){
			if(begin->val > end->val){
				ListNode * temp = end;
				begin->next = NULL;
				temp->next = begin;
				return temp;
			}
			else{
				return begin;
			}
		}
		ListNode * fast = begin;
		ListNode * slow = begin;
		while(fast->next && fast->next->next){
			fast = fast->next->next;
			slow = slow->next;
		}
		ListNode * p = slow->next;
		slow->next = NULL;
		ListNode * left = mergeSort(begin, slow);
		ListNode * right = mergeSort(p, end);
		ListNode * dump = NULL;
		if(left->val > right->val){
			dump = right;
			right = right->next;
		}
		else{
			dump = left;
			left = left->next;
		}
		ListNode * origin = dump;
		while(1){
			if(left == NULL && right == NULL){
				break;
			}
			else if(left == NULL) {
				dump->next = right;
				right = right->next;
			}
			else if(right == NULL){
				dump->next = left;
				left = left->next;
			}
			else if(left->val > right->val){
				dump->next = right;
				right = right->next;
			}
			else{
				dump->next = left;
				left = left->next;
			}
			dump = dump->next;
		}
		return origin;
	}
	void print(){
		ListNode * p = root;
		cout<<"There are "<<length<<" ListNodes in the single linked list"<<endl;
		while(p){
			cout<<p->val<<" ";
			p = p->next;
		}
		if(!length)
			return;
		cout<<endl;
	}
private:
	ListNode * root;
	ListNode * tail;
	int length;
};
int main(){
	SingleLinkedList list;
	srand(time(0));
	for(int i = 0; i < 100; ++i){
		list.append(rand()%100);
	}
	list.print();
	list.sort();
	list.print();
	return 0;
}