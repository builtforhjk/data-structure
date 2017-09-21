#include <stdio.h>
#include <stdlib.h>
int KMP(const char * src, int srcSize, const char * sub,int subSize, int pos,int next[]){
	int i = pos, j = 0;
	while(i < srcSize && j < subSize){
		if(j == -1 || sub[j] == src[i]){
			++i;
			++j;
		}
		else j = next[j];
	}
	if(j == subSize) return i - subSize;
	else return -1;
}
void set_next(const char * s,int * next,int length){
	next[0] = -1;
	int i = 0, j = -1;
	while(i < length){
		if(j == -1 || s[i] == s[j]){
			++i;
			++j;
			next[i] = j;
		}
		else j = next[j];
	}
}
int main(){
	char a[9] = "abaabcac";
	int next[9];
	set_next(a, next,8);
	int i = 0;
	for(; i < 8; ++i){
		printf("[%c]:%d  ",a[i],next[i]);
	}
	printf("\n");
	char s[30] = "absdaabaabcacccd";
	printf("%d\n",KMP(s,19,a,8,0,next));
	return 0;
}