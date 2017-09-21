#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef  struct UFSet{
	int * pre;
	int find(int x){
		int r = x;
		while(pre[r] != r){
			r = pre[r];
		}
		//路径压缩
		int i = x;
		while(i != r){
			int j = pre[i];
			pre[i] = r;
			i = j;
		}
		return r;
	}
	void merge(int x, int y){
		int r_x = find(x);
		int r_y = find(y);
		if(r_x != r_y){
			pre[r_x] = r_y;
		}
	}
	UFSet(int n){
		pre = new int[n];
		for(int i = 0; i < n; ++i){
			pre[i] = i;
		}
	}
}UFSet;
