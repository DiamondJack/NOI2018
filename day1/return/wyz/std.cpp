#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back
#define mp make_pair
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
}

namespace Yazid{

const int N=400005;
const int M=800005;
const int _logn=20;
const int inf=1e9;
#define bin(x) (1<<(x))

struct Edge{
	int adj,next,len;
	Edge(){}
	Edge(int _adj,int _next,int _len):adj(_adj),next(_next),len(_len){}
} e[M];
int n,g[N],m;
void addEdge(int u,int v,int w=0){
	e[++m]=Edge(v,g[u],w);g[u]=m;
	e[++m]=Edge(u,g[v],w);g[v]=m;
}
void clear(){
	memset(g,0,sizeof(g));m=1;
}


bool flag[N];
priority_queue<pii,vector<pii>, greater<pii> > pq;
int mind[N];

void dijkstra(int _s){
	memset(mind,127,sizeof(mind));
	memset(flag,0,sizeof(flag));
	while (!pq.empty()) pq.pop();
	pq.push(mp(mind[_s]=0,_s));
	while (!pq.empty()){
		int u=pq.top().second;
		pq.pop();
		if (!flag[u]){
			flag[u]=1;
			for (int i=g[u];i;i=e[i].next){
				int v=e[i].adj;
				if (mind[v]<=mind[u]+e[i].len) continue;
				mind[v]=mind[u]+e[i].len;
				pq.push(mp(mind[v],v));
			}
		}
	}
}


struct UnionSet{
	int f[N];
	void makeSet(int x){f[x]=x;}
	void init(int n){for (int i=1;i<=n;++i) makeSet(i);}
	int find(int x){return f[x]=f[x]==x?x:find(f[x]);}
	int _union(int x,int y){
		if (find(x)==find(y)) return -1;
		return f[f[x]]=f[y];
	}
} us;

int fa[N],valP[N];
int _u[M],_v[M],_l[M],_w[N],_a[M],_vp[M],_m;
int id[M];
bool cmp(int u,int v){
	return _a[u]>_a[v];
}
int bl[N];
void kruskal(){
	for (int i=1;i<=n;++i){
		bl[i]=i;
		valP[i]=inf;
	}
	memset(fa,0,sizeof(fa));
	us.init(n);
	int stamp=n;
	for (int i=1;i<=_m;++i){
		int u=us.find(_u[i]);
		int v=us.find(_v[i]);
		if (u==v) continue;
		fa[bl[u]]=fa[bl[v]]=++stamp;
		mind[stamp]=min(mind[bl[u]],mind[bl[v]]);
		valP[stamp]=_vp[i];
		bl[us._union(u,v)]=stamp;
	}
	assert(stamp==n*2-1);
}


int F[N][_logn];
void constructF(){
	memcpy(F[0],fa,sizeof(fa));
	for (int k=1;k<=_logn;++k)
		for (int i=2*n-1;i;--i)
			F[i][k]=F[F[i][k-1]][k-1];
}

int multiplicate(int v,int p){
	for (int k=_logn;k>=0;--k){
		int anc=F[v][k];
		if (anc==0||p>valP[anc]) continue;
		v=anc;
	}
	return v;
}

void __main__(){
	n=read();
	_m=read();
	clear();
	ll sumArea=0;
	for (int i=1;i<=_m;++i){
		id[i]=i;
		_u[i]=read();
		_v[i]=read();
		_l[i]=read();
		_w[i]=read();
		_a[i]=read();
		addEdge(_u[i],_v[i],_l[i]);
		sumArea+=_l[i]*_w[i];
	}
	dijkstra(1);
	
	clear();
	sort(id+1,id+_m+1,cmp);
	ll nowArea=0,sumP=0;
	_a[_m+1]=0;
	for (int i=_m;i>0;--i){
		sumP+=nowArea*(_a[i]-_a[i+1]);
		if (sumP==0) _vp[i]=0;
		else _vp[i]=(sumP-1)/sumArea+1;
		nowArea+=_l[i]*_w[i];
	}
	kruskal();
	
	constructF();
	
	for (int Q=read(),K=read(),S=read(),lastans=0;Q;--Q){
		int v=(read()+lastans-1)%n+1;
		int p=(read()+lastans)%(S+1);
		int top=multiplicate(v,p);
		printf("%d\n",lastans=mind[top]);
	}
}

};

int main(int argc,char** argv){
	Yazid::__main__();
	return 0;
}