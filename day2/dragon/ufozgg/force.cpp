#include<cstdio>
#include<set>
using namespace std;
multiset <long long> S0;
int T;
int n,m;
long long a[100010],p[100010],atk[200010],gek[100010];
bool checkans(long long ax)
{
	for(int i=1;i<=n;++i)
		if(ax*gek[i]<a[i]||ax*gek[i]%p[i]!=a[i]%p[i])
			return false;
	return true;
}
int main()
{
	freopen("16.in","r",stdin);
	int i,j;
	for(scanf("%d",&T);T;--T)
	{
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;++i)
			scanf("%lld",a+i);
		for(i=1;i<=n;++i)
			scanf("%lld",p+i);
		for(i=1;i<=n+m;++i)
			scanf("%lld",atk+i);
		S0.clear();
		for(i=n+1;i<=n+m;++i)
			S0.insert(atk[i]);
		for(i=1;i<=n;++i)
		{
			auto w=S0.upper_bound(a[i]);
			if(w!=S0.begin())
				--w;
			gek[i]=*w;
			S0.erase(w);
			S0.insert(atk[i]);
		}
		for(long long ans=554659065370LL;ans;++ans)
			if(checkans(ans))
			{
				printf("%lld\n",ans);
				break;
			}
	}
	return 0; 
} 
