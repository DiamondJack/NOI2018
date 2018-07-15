// #define FAST_READ
#define DIJKSTRA
#define KRUSKAL
#define MULTIPLICATE
#define NOINFO
#include "../core.hpp"

namespace Yazid{
void encrypt(){
	n=read();
	_m=read();
	printf("%d %d\n",n,_m);
	clearEdges();
	for (int i=1;i<=_m;++i){
		_u[i]=read();
		_v[i]=read();
		_l[i]=read();
		_a[i]=read();
		addEdge(_u[i],_v[i],_l[i]);
		printf("%d %d %d %d\n",_u[i],_v[i],_l[i],_a[i]);
	}
	precompute();
	
	int Q=read(),K=read(),S=read(),lastans=0;
	printf("%d %d %d\n",Q,K,S);
	while (Q--){
		int v=read();
		int p=read();
		int v0=(v-K*lastans-1)%n+1;
		int p0=(p-K*lastans)%(S+1);
		if (v0<=0) v0+=n;
		if (p0<0) p0+=S+1;
		printf("%d %d\n",v0,p0);
		lastans=query(v,p);
		// int v=(read()+K*lastans-1)%n+1;
		// int p=(read()+K*lastans)%(S+1);
	}
	Info::info("Yazid saikou!");
}
};


int main(int argc,char** argv){
#ifdef MULTIPLE_CASES
int T=read();
printf("%d\n",T);
while (T--)
#endif
	Yazid::encrypt();
	return 0;
}
