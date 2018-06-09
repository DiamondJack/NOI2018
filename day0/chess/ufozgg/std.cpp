#define INF 10000000
#include <cstdio>
int n,m;
int A[13][13];
int B[13][13];
int f[1<<22];
int p2[22]={1};
int cnt(int x)
{
	int ret = 0;
	while(x)
	{
		if(x&1)
			++ret;
		x>>=1;
	}
	return ret;
}
int square(int x)
{
	int ret=0,i,w=0;
	for(i=0;i<n+m;++i)
		if(x&p2[i])
			ret+=w;
		else
			++w;
	return ret;
}
int valA(int v,int b)
{
	int g = cnt(v&(p2[b]-1));
	return A[n-b+g][g+1];
}
int valB(int v,int b)
{
	int g = cnt(v&(p2[b]-1));
	return B[n-b+g][g+1];
}
void solve(int v,int c)
{
	int i,ret,w;
	if(c)
	{
		ret = INF;
		for(i=0;i<n+m-1;++i)
			if((p2[i]&v)==0&&(p2[i+1]&v))
			{
				w = f[v^p2[i]^p2[i+1]]-valB(v,i);
				if(w<ret)
					ret=w;
			}
	}
	else
	{
		ret = -INF;
		for(i=0;i<n+m-1;++i)
			if((p2[i]&v)==0&&(p2[i+1]&v))
			{
				w = valA(v,i)+f[v^p2[i]^p2[i+1]];
				if(w>ret)
					ret=w;
			}
	}
	f[v]=ret;
}
int main()
{
	int i,j,w;
	for(i=1;i<=21;++i)
		p2[i]=p2[i-1]*2;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			scanf("%d",A[i]+j);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			scanf("%d",B[i]+j);
	f[p2[m]-1]=0;
	for(i=p2[m];i<=p2[n+m]-p2[n];++i)
		if(cnt(i)==m)
		{
			w=n*m-square(i);
			solve(i,w&1);
		}
	printf("%d\n",f[p2[n+m]-p2[n]]);
	return 0;
}

