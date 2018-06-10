#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) (rand()%100<x)


using namespace std;

void unqPick(int *a,int l,int r){
	for (int i=l;i<=r;++i) a[i-l]=i;
	for (int k=0;k<7;++k) random_shuffle(a,a+(r-l+1));
}
void unqPick(int *a,int n){
	unqPick(a,1,n);
}
ull randULL(){return ((ull)rand()<<30)^((ull)rand()<<50)^rand();}
ll Rand(ll mod){return (unsigned long long)rand()*rand()*rand()*rand()%mod;}
const int base=2;
int Rand_log(int ub){return pow(base,1.0*rand()/RAND_MAX*(log(ub)/log(base)));}

const int P=998244353;
const int maxm=100;
const int maxQ=200005;

int op[maxQ];
int id[maxQ];

void gen(int n,int Q,int C,int type){
	int v=randULL()%(P-2)+2,u=randULL()%(v-1)+1;
	printf("%d\n",n);
	for (int i=1;i<=n;++i){
		int x=percent(3)?maxm:(rand()%(Q<=100?5:maxm)+1);
		if (type&2) x=1;
		printf("%d",x);
		if (i==n) puts("");
		else putchar(' ');
	}
	printf("%d\n",Q);
	unqPick(id,Q/2,Q);
	memset(op,0,sizeof(op));
	for (int i=0;i<C;++i) op[id[i]]=1;
	for (int i=1;i<=Q;++i){
		if (op[i]==0){
			int id=rand()%n+1;
			if ((type&1)==0) v=randULL()%(P-2)+2,u=randULL()%(v-1)+1;
			if (type&4) u=v=233;
			printf("%d %d %d %d\n",0,id,u,v);
		}
		if (op[i]==1){
			int k=n-Rand_log(n)+1;
			printf("%d %d",1,k);
			unqPick(id,n);
			for (int j=0;j<k;++j)
				printf(" %d",id[j]);
			puts("");
		}
	}
}

int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	int n=argc>2?atoi(argv[2]):100;
	int Q=argc>3?atoi(argv[3]):200000;
	int C=argc>4?atoi(argv[4]):1000;
	int type=argc>5?atoi(argv[5]):0;
	gen(n,Q,C,type);
	srand(seed);
	return 0;
}
