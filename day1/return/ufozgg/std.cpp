#include<cstdio>
int n,m;
int q,k,s;
int main()
{
	int i,j,v0,p0,v,p;
	int T;
	for(scanf("%d",&T);T;--T)
	{
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;++i)
		{
			scanf("%d%d%d%d",&u,&v,&l,&a);
		}
		scanf("%d%d%d",&q,&k,&s);
		for(i=1;i<=q;++i)
		{
			scanf("%d%d",&v0,&p0);
			v=(v0+k*ans-1)%n+1;
			p=(p0+k*ans)%s;
			
		}
	}
	return 0;
} 
