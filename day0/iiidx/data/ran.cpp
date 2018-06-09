#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ctime> 
#include <cctype>
#include <cstring>

#define rep(i, l, r) for(int i = l; i <= r; i++)
#define dow(i, l, r) for(int i = l; i >= r; i--)
#define travel(x) for(edge *p=fir[x]; p; p=p->n)
#define clr(x, c) memset(x, c, sizeof(x))
#define ull unsigned long long
#define ll long long
#define inf 0xDE0B6B3A7640000

using namespace std;

int p, A=rand(), B=rand();
int Rand() {A=rand(); B=rand(); return p=(1LL*A*p+B)%(1LL<<31);}

//ull p, A=rand(), B=rand();
//ull Rand() {A=rand(); B=rand(); return p=A*p+B;}

inline int read()
{
	int x=0, f=1; char ch=getchar();
	while (!isdigit(ch)) {if (ch=='-') f=-1; ch=getchar();}
	while (isdigit(ch)) x=x*10+ch-'0', ch=getchar();
	return x*f;
}

int a[500009];

int main()
{
	int n, C, G; double k;
	scanf("%d%lf%d%d", &n, &k, &C, &G);
	
	freopen("seed.txt", "r", stdin);
	srand(read()); rep(i,1,50) Rand();
	
	if (G!=-1) rep(i, 1, G) a[i]=Rand()%C+1;
	
	printf("%d %.3lf\n", n, k);
	rep(i, 1, n) printf("%d%c", G==-1?(Rand()%C+1):a[Rand()%G+1], i==n?'\n':' ');
	
	freopen("seed.txt", "w", stdout);
	printf("%d\n", Rand());
	fclose(stdin);
	fclose(stdout);
	return 0;
}