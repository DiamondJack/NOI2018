#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>
#include <cmath>
#include <set>
#include <map>
#include <iostream>
 
#define rep(i, l, r) for(int i=l; i<=r; i++)
#define dow(i, l, r) for(int i=l; i>=r; i--)
#define clr(x, c) memset(x, c, sizeof(x))
#define travel(x) for(edge *p=fir[x]; p; p=p->n)
#define all(x) (x).begin,(x).end
#define pb push_back
#define fi first
#define se second
#define l(x) Left[x]
#define r(x) Right[x]
#define lowbit(x) (x&-x)
 
using namespace std;
 
typedef long long ll;
typedef pair<int,int> Pii;
typedef pair<ll,int> Pli;
typedef long double ld;
typedef unsigned long long ull;
 
inline int read()
{
	int x=0, f=0; char ch=getchar();
	while (ch<'0' || '9'<ch) f|=ch=='-', ch=getchar();
	while ('0'<=ch && ch<='9') x=x*10+ch-'0', ch=getchar();
	return f?-x:x;
}

#define maxn 500009
#define maxc 1000009

struct edge{int y; edge *n;} e[maxn], *fir[maxn], *pt=e;
inline void AddE(int x, int y){pt->y=y, pt->n=fir[x], fir[x]=pt++;}

int n; double k; int a[maxn], b[maxn], c[maxn], sz[maxn];

int rt, cn, Left[maxc], Right[maxc], s[maxc];

int X, Y;
void Add(int l, int r, int &t)
{
	if (l==r) {s[t]+=Y; return;}
	int mid=(l+r)>>1;
	if (X<=mid) Add(l,mid,l(t)); else Add(mid+1,r,r(t));
	s[t]=s[l(t)]+s[r(t)];
}

void Build(int l, int r, int &t)
{
	t=++cn; if (l==r) return;
	int mid=(l+r)>>1;
	Build(l,mid,l(t)); Build(mid+1,r,r(t));
}

inline int Find(int x)
{
	int t=rt, l=1, r=n; while (l!=r)
	{
		if (s[r(t)]<x) 
			x-=s[r(t)], t=l(t), r=(l+r)/2;
		else
			t=r(t), l=(l+r)/2+1;
	} return l;
}

int main()
{
	scanf("%d%lf", &n, &k);
	rep(i, 1, n) a[i]=read(); sort(a+1, a+1+n);
	dow(i, n, 1) if (a[i]==a[i+1]) c[i]=c[i+1]+1; else c[i]=1;
	Build(1,n,rt);
	if (k==1) {rep(i, 1, n) b[i]=a[n-i+1];} else
	{
		dow(i, n, 1) AddE((int)(i/k),i), sz[(int)(i/k)]+=(++sz[i]);
		travel(0) X=p->y, Y=sz[p->y], Add(1,n,rt);
		for(int i=1,x; i<=n; i++)
		{
			b[x=Find(c[i])]=a[i];
			X=x, Y=-sz[x], Add(1,n,rt);
			travel(x) X=p->y, Y=sz[p->y], Add(1,n,rt);
		}
	}
	rep(i, 1, n) printf("%d%c", b[i], i==n?'\n':' ');
	return 0;
}