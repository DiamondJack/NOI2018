#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define percent(x) (rand()%100<x)


using namespace std;
void EXIT(string st){
	cerr<<st<<endl;
	exit(0);
}

const int N(1e6);

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

const int maxA(1e9);
const int maxL(1e3);

int av[N];



int _u[N],_v[N],_l[N],_a[N];
int _v0[N],_p0[N];
int S;

// if fuckSpfa=1, SPFA will be fucked.
void gen(int n,int m,int Q,int graphForm,int uniqueA,int online,int index,bool fuckSpfa){
	if (fuckSpfa==0) EXIT("Fuck you!");
	int maxn(n);
	int maxm(m);
	
	if (graphForm) m=n-1;
	int K(pow(n,0.35));
	m+=K;
	if (uniqueA){
		for (int i=0;i<=m;++i) av[i]=1;
		S=1;
	}
	else{
		for (int i=0;i<=m;++i){
			av[i]=rand()%maxA+1;
			if (index==2&&percent(71)){
				av[i]=rand()%n+1;
			}
			if (index==3&&percent(71)){
				av[i]=maxA-rand()%n;
			}
		}
		S=maxA;
	}
	sort(av,av+m+1);
	
	int aIdMod(m);
	m=0;
	if (graphForm==0){
		int mxn=0;
		auto addEdge=[n,&mxn,&m,maxm](int x,int y,int l,int a){
			if (x>n||y>n) return true;
			if (m+1>maxm) return false;
			mxn=max(mxn,max(x,y));
			++m;
			_u[m]=x;
			_v[m]=y;
			_l[m]=l;
			_a[m]=av[a];
			return true;
		};
		int sz=sqrt(n)+1;
		int stamp=0;
		bool triangle=index==1;
		int s0=aIdMod-n;
		bool flag=1;
		for (int i=1,top=triangle?i:sz,last=s0+top;flag;++i,top=triangle?i:sz,last=(++s0)+top-1)
			for (int j=1;j<=top;++j){
				if (stamp+1>n){flag=0;break;}
				++stamp;
				int tmp1=rand()%max(1,aIdMod*8/14),tmp2=rand()%max(1,aIdMod*11/20);
				// printf("%d %d %d\n",i,j,top);
				if (i%2==0&&j==1) tmp1=last;
				if (i%2==1&&j==top) (triangle?tmp2:tmp1)=last;
				if (!addEdge(stamp,stamp+top,rand()%maxL+1,tmp1)){flag=0;break;}
				if (j<top) if (!addEdge(stamp,stamp+1,rand()%int(sqrt(maxL))+1,++s0)){flag=0;break;}
				if (triangle) if (!addEdge(stamp,stamp+top+1,rand()%maxL+1,tmp2)){flag=0;break;}
			}
		n=max(mxn,stamp);
	}
	else if (graphForm==1){
		m=n-1;
		for (int i=1;i<n;++i){
			_u[i]=i;
			_v[i]=i+1;
			_l[i]=rand()%maxL+1;
			_a[i]=av[i+rand()%K];
		}
	}
	else if (graphForm==2){
		m=n-1;
		for (int i=1;i<n;++i){
			_u[i]=i;
			_v[i]=i+1;
			_l[i]=rand()%maxL+1;
			_a[i]=av[i+rand()%K];
		}
	}
	else EXIT("wyzsb");
	
	
	
	for (int i=1;i<=Q;++i){
		_v0[i]=n-Rand_log(n);
		if (percent(23)) _p0[i]=randULL()%(S+1);
		else _p0[i]=_a[rand()%m];
	}
	
	
// ==========Print=================
	assert(n<=maxn);
	assert(m<=maxm);
	printf("%d %d\n",n,m);
	int* id=new int[n+2];
	int* id2=new int[m+2];
	for (int i=1;i<=n;++i) id[i]=i;
	for (int i=1;i<=m;++i) id2[i]=i;
	if (graphForm!=2){
		for (int k=0;k<7;++k) random_shuffle(id+2,id+n+1); // Don't shuffle vertex 1!!!
		for (int i=1;i<=m;++i) if (percent(50)) swap(_u[i],_v[i]);
	}
	for (int k=0;k<7;++k) random_shuffle(id2+1,id2+m+1);
	for (int i=1;i<=m;++i){
		printf("%d %d %d %d\n",id[_u[id2[i]]],id[_v[id2[i]]],_l[id2[i]],_a[id2[i]]);
	}
	printf("%d %d %d\n",Q,online,S);
	for (int i=1;i<=Q;++i){
		printf("%d %d\n",id[_v0[i]],_p0[i]);
	}
	delete[] id;
	delete[] id2;
}

int main(int argc,char **argv){
	unsigned int seed=argc>1?atoi(argv[1]):time(0);
	int T=argc>2?atoi(argv[2]):1;
	int n=argc>3?atoi(argv[3]):int(2e5);
	int m=argc>4?atoi(argv[4]):int(4e5);
	int Q=argc>5?atoi(argv[5]):int(3e5);
	int form=argc>6?atoi(argv[6]):0;
	int unqA=argc>7?atoi(argv[7]):0;
	int onln=argc>8?atoi(argv[8]):1;
	srand(seed);
	printf("%d\n",T);
	for (int i=1;i<=T;++i) gen(n,m,Q,form,unqA,onln,i,1);
	return 0;
}
