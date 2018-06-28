#include <bits/stdc++.h>

using namespace std;

// #define MULTIPLE_CASES

namespace Yazid{

typedef long long ll;
typedef pair<int,int> pii;
#define pb push_back
#define mp make_pair

#ifdef FAST_READ
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}
#endif
#ifndef FAST_READ
inline int read(){
	int ret;
	scanf("%d",&ret);
	return ret;
}
#endif


const int N=400005;
const int M=800005;
const int _logn=20;
const int inf=2e9;
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


int mind[N];

#ifdef DIJKSTRA
bool flag[N];
priority_queue<pii,vector<pii>, greater<pii> > pq;
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
#endif

#ifdef SPFA
int q[N],qh,qt;
bool exist[N];
void spfa(int _s){
	memset(mind,127,sizeof(mind));
	memset(exist,0,sizeof(exist));
	qh=qt=0;
	q[++qt]=_s;exist[_s]=1;mind[_s]=0;
	while (qh!=qt){
		int u=q[(++qh)%=n];
		for (int i=g[u];i;i=e[i].next){
			int v=e[i].adj;
			if (mind[v]<=mind[u]+e[i].len) continue;
			mind[v]=mind[u]+e[i].len;
			if (exist[v]) continue;
			q[(++qt)%=n]=v;
			exist[v]=1;
		}
		exist[u]=0;
	}
}
#endif

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
int _u[M],_v[M],_l[M],_a[M],_m;
int id[M];
bool cmp(int u,int v){
	return _a[u]>_a[v];
}
int bl[N];
void kruskal(){
	sort(id+1,id+_m+1,cmp);
	for (int i=1;i<=n;++i){
		bl[i]=i;
		valP[i]=inf;
	}
	memset(fa,0,sizeof(fa));
	us.init(n);
	int stamp=n;
	for (int i=1;i<=_m;++i){
		int u=us.find(_u[id[i]]);
		int v=us.find(_v[id[i]]);
		if (u==v) continue;
		fa[bl[u]]=fa[bl[v]]=++stamp;
		mind[stamp]=min(mind[bl[u]],mind[bl[v]]);
		valP[stamp]=_a[id[i]]-1;
		bl[us._union(u,v)]=stamp;
	}
	assert(stamp==n*2-1);
}


int F[N][_logn+1];
void constructF(){
	for (int i=2*n-1;i>=0;--i)
		F[i][0]=fa[i];
	for (int k=1;k<=_logn;++k)
		for (int i=2*n-1;i>0;--i)
			F[i][k]=F[F[i][k-1]][k-1];
}

int multiplicate(int v,int p){
	#ifdef DEBUG
	printf("v=%d p=%d\n",v,p);
	#endif
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
	for (int i=1;i<=_m;++i){
		id[i]=i;
		_u[i]=read();
		_v[i]=read();
		_l[i]=read();
		_a[i]=read();
		addEdge(_u[i],_v[i],_l[i]);
	}
	#ifdef DIJKSTRA
	dijkstra(1);
	cerr<<"[ Yazid Info ] Dijkstra finished."<<endl;
	#endif
	#ifdef SPFA
	spfa(1);
	cerr<<"[ Yazid Info ] SPFA finished."<<endl;
	#endif
	
	clear();
	kruskal();
	cerr<<"[ Yazid Info ] Kruskal finished."<<endl;
	
	constructF();
	cerr<<"[ Yazid Info ] Array F constructed."<<endl;
	
	#ifdef DEBUG
	for (int i=1;i<=2*n-1;++i)
		printf("%d : valP=%d mind=%d fa=%d\n",i,valP[i],mind[i],fa[i]);
	#endif
	for (int Q=read(),K=read(),S=read(),lastans=0;Q;--Q){
		int v=(read()+K*lastans-1)%n+1;
		int p=(read()+K*lastans)%(S+1);
		int top=multiplicate(v,p);
		printf("%d\n",lastans=mind[top]);
	}
	cerr<<"[ Yazid Info ] Yazid is good."<<endl;
}

};

#ifdef __MAIN__
int main(int argc,char** argv){
#ifdef MULTIPLE_CASES
for (int T=read();T;T--)
#endif
	Yazid::__main__();
	return 0;
}
#endif