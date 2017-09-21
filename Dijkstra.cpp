#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef int elemType;
typedef struct Edge{
	int weigh;
	elemType rear;
	Edge(){}
	Edge(int x, elemType y): weigh(x), rear(y){}
}Edge;
typedef struct Info{
	elemType pre;
	int dist;
	bool visited;
	Info(){
		pre = -1;
		dist = 999999;
		visited = false;
	}
}Info;
map<elemType, vector<Edge> > graph;
Info * vetex;
int n,m;
elemType start_c, end_c;
void dijkstra(elemType head){
	if(head == end_c) return;
	for(auto item : graph[head]){
		if(!vetex[item.rear].visited){
			int d = vetex[head].dist + item.weigh;
			if(d < vetex[item.rear].dist){
				vetex[item.rear].dist = d;
				vetex[item.rear].pre = head;
			}
		}
	}
	elemType next = head;
	int st = 999999;
	for(int i = 1; i <= n; ++i){
		if(!vetex[i].visited){
			if(st > vetex[i].dist){
				st = vetex[i].dist;
				next = i;
			}
		}
	}
	vetex[next].visited = true;
	dijkstra(next);
}
int main(){
	cin>>n>>m;
	cin>>start_c>>end_c;
	vetex = new Info[n+1];
	for(int i = 1; i <= n; ++i){
		vetex[i] = Info();
	}
	for(int i = 0; i < m; ++i){
		elemType s,t;
		int val;
		cin>>s>>t>>val;
		graph[s].push_back(Edge(val, t));
		graph[t].push_back(Edge(val, s));
	}
	vetex[start_c].visited = true;
	vetex[start_c].dist = 0;
	dijkstra(start_c);
	vector <elemType> path;
	elemType cur = end_c;
	while(cur != -1){
		path.push_back(cur);
		cur = vetex[cur].pre;
	}
	for(auto it = path.rbegin(); it!=path.rend(); ++it){
		cout<<*it;
		if((*it) == end_c) cout<<endl;
		else cout<<"->";
	}
	return 0;
}