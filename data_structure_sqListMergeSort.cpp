#include <iostream>
using namespace std;
void mergeSort(int * searchList,int begin, int end){
	if(end - begin == 1){
		if(searchList[begin] > searchList[end]){
			swap(searchList[begin], searchList[end]);
		}
		return;
	}
	else if(end == begin){
		return;
	}
	mergeSort(searchList, begin, (begin+end)/2);
	mergeSort(searchList, (begin+end)/2 + 1, end);
	int * dstList = new int[end-begin+1];
	int originPos = 0;
	int pos1 = begin;
	int pos2 = (begin+end)/2+1;
	while(1){
		if(pos1 > (begin+end)/2 && pos2 > end){
			break;
		}
		else if(pos1 > (begin+end)/2){
			dstList[originPos] = searchList[pos2];
			++pos2;
		}
		else if(pos2 > end){
			dstList[originPos] = searchList[pos1];
			++pos1;
		}
		else if(searchList[pos1] < searchList[pos2]){
			dstList[originPos] = searchList[pos1];
			++pos1;
		}
		else {
			dstList[originPos] = searchList[pos2];
			++pos2;
		}
		++originPos;
	}
	for(int i = begin; i <= end; ++i){
		searchList[i] = dstList[i - begin];
	}
	delete []dstList;
}
int main(){
	int a[36] = {13,21,15,4,67,34,12,66,8,1,73,21,13,21,15,4,67,34,12,66,8,1,73,21,13,21,15,4,67,34,12,66,8,1,73,21};
	mergeSort(a, 0,35);
	for(int i : a){
		cout<<i<<" ";
	}
	cout<<endl;
	return 0;
}