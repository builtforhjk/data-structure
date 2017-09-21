#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define npos -1
#define FALSE 0
#define TRUE 1
/*
ADT ScatterDiagram{
	D:{Point(x,y)}
	R:{<Point,Point>}
	P:{
		//初始化
		Status STDiagram_init(ScatterDiagram * SD);
		//查找
		Iterator STDiagram_find(ScatterDiagram * SD, Point p);
		//插入
		Status STDiagram_insert(ScatterDiagram * SD, Point p);
		//重新分配空间
		Status STDiagram_resize(ScatterDiagram * SD,int increment);
		//删除
		Status STDiagram_erase(ScatterDiagram * SD,Point p);
		//元素个数
		type_size STDiagram_size(ScatterDiagram * SD);
		//第一个元素索引
		Iterator STDiagram_begin(ScatterDiagram * SD);
		//最后一个元素后一位索引
		Iterator STDiagram_end(ScatterDiagram * SD);
		//容器是否为空
		BOOL STDiagram_empty(ScatterDiagram * SD);
		//清空容器
		Status STDiagram_clear(ScatterDiagram * SD);
		//返回指定索引的值
		Point STDiagram_at(ScatterDiagram * SD, Iterator pos);
	}
}
*/
typedef struct Point{
	int x;
	int y;
}Point;
typedef struct ScatterDiagram{
	Point * base;
	int size;
}ScatterDiagram;
typedef int Iterator;
typedef int type_size;
typedef int BOOL;
typedef enum{OK, WARNING, ERROR}Status;
Status STDiagram_init(ScatterDiagram * SD){
	SD->base = (Point *)malloc(sizeof(Point)*MAX_SIZE);
	if(!SD->base) return ERROR;
	SD->size = 0;
	return OK;
}
Iterator STDiagram_find(ScatterDiagram * SD, Point p){
	Iterator itor;
	for(itor = 0; itor < SD->size; ++itor){
		if(SD->base[itor].x == p.x && SD->base[itor].y == p.y){
			return itor;
		}
	}
	return npos;
}
Status STDiagram_insert(ScatterDiagram * SD, Point p){
	if(SD->size == MAX_SIZE) return ERROR;
	if(STDiagram_find(SD, p) != npos) return WARNING;
	SD->base[SD->size].x = p.x;
	SD->base[SD->size].y = p.y;
	++SD->size;
	return OK;
}
Status STDiagram_resize(ScatterDiagram * SD,int increment){
	Point * co = (Point*)malloc(sizeof(Point)*SD->size);
	int i;
	for(i = 0; i < SD->size; ++i){
		co[i].x = SD->base[i].x;
		co[i].y = SD->base[i].y;
 	}
	free(SD->base);
	SD->base = NULL;
	SD->base = (Point *)malloc(sizeof(Point)*(SD->size+increment));
	if(!SD->base) return ERROR;
	for(i = 0; i < SD->size; ++i){
		SD->base[i].x = co[i].x;
		SD->base[i].y = co[i].y;
	}
	free(co);
	SD->size += increment;
	return OK;
}
Status STDiagram_erase(ScatterDiagram * SD,Point p){
	Iterator itor = STDiagram_find(SD, p);
	if(itor == npos) return ERROR;
	for(; itor < (SD->size-1); ++itor){
		SD->base[itor].x = SD->base[itor+1].x;
		SD->base[itor].y = SD->base[itor+1].y;
	}
	--SD->size;
	return OK;
}
type_size STDiagram_size(ScatterDiagram * SD){
	return SD->size;
}
Iterator STDiagram_begin(ScatterDiagram * SD){
	return 0;
}
Iterator STDiagram_end(ScatterDiagram * SD){
	return SD->size;
}
BOOL STDiagram_empty(ScatterDiagram * SD){
	return SD->size == 0;
}
Status STDiagram_clear(ScatterDiagram * SD){
	if(!SD->base) return ERROR;
	free(SD->base);
	SD->base = (Point*)malloc(sizeof(Point)*MAX_SIZE);
	SD->size = 0;
	return OK;
}
Point STDiagram_at(ScatterDiagram * SD, Iterator pos){
	return SD->base[pos];
}
void print(ScatterDiagram * SD){
	Iterator itor;
	for(itor = STDiagram_begin(SD); itor != STDiagram_end(SD); ++itor){
		Point p = STDiagram_at(SD,itor);
		printf("(x: %d, y: %d)\n", p.x, p.y);
	}
}
int main(){
	printf("loading...\n");
	ScatterDiagram SD;
	if(STDiagram_init(&SD) == ERROR) printf("ERROR: initialization false\n");
	else printf("success\n");
	BOOL terminate = FALSE;
	printf("$STD -Command:\n");
	printf("-1: print\n");
	printf("-2: insert\n");
	printf("-3: find\n");
	printf("-4: delete\n");
	printf("-5: increase\n");
	printf("-6: clear\n");
	printf("-7: size\n");
	printf("-8: quit\n");
	int type;
	while(1){
		if(terminate == TRUE) break;
		scanf("%d",&type);
		switch(type){
			case 1: {
				printf("Command: Print\n");
				if(STDiagram_empty(&SD) == TRUE) printf("Empty\n");
				else print(&SD);
				break;
			}
			case 2: {
				printf("Command: insert (input format: x y)\n");
				Point p;
				scanf("%d%d",&p.x,&p.y);
				Status state = STDiagram_insert(&SD, p);
				if(state == ERROR) printf("ERROR: NO space to insert new element. Fixed by command \"5\" to increase container's capacity.\n");
				else if(state == WARNING) printf("WARNING: insert value has already existed\n");
				else printf("insert (%d,%d) done\n",p.x, p.y);
				break;
			}
			case 3: {
				printf("Command: find (input format: x y)\n");
				Point p;
				scanf("%d%d",&p.x,&p.y);
				Iterator itor = STDiagram_find(&SD, p);
				if(itor == npos) printf("can not find\n");
				else printf("Info:\nindex: %d\ndescription: (%d,%d)\n",itor+1, STDiagram_at(&SD, itor).x, STDiagram_at(&SD, itor).y);
				break;
			}
			case 4: {
				printf("Command: delete (input format: x y)\n");
				Point p;
				scanf("%d%d",&p.x,&p.y);
				Status state = STDiagram_erase(&SD, p);
				if(state == ERROR) printf("can not find\n");
				else printf("delete (%d,%d) done\n",p.x, p.y);
				break;
			}
			case 5: {
				printf("Command: increase container's capacity\n");
				printf("increment: ");
				int increment;
				scanf("%d",&increment);
				Status state = STDiagram_resize(&SD, increment);
				if(state == ERROR) printf("ERROR: unable to resize\n");
				else printf("resize done\n");
				break;
			}
			case 6: {
				printf("Command: clear\n");
				Status state = STDiagram_clear(&SD);
				if(state == ERROR) printf("ERROR\n");
				else printf("clear done\n");
				break;
			}
			case 7: {
				printf("Command: acquire size\n");
				printf("%d\n", STDiagram_size(&SD));
				break;
			}
			case 8:
				terminate = TRUE;
				printf("Command: quit\n");
				break;
			default:break;
		}
	}
	return 0;
}