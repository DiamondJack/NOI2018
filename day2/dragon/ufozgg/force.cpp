#pragma GCC diagnostic error "-std=c++11"
#include<cstdio>
#include<set>
#define MAXN 1000100
#define MAXM 1000100
int n,m;
long long hp[MAXN],re[MAXN],dec[MAXN];
int award[MAXN];
std::multiset<int> swords;
long long glb_gcd;
bool check_sol(long long x,long long a,long long b)
{
	long long mul=1;
	while(a&&b)
	{
		if(a==b)
			break;
		if((!a&1)&&(!b&1))
		{
			a>>=1;
			b>>=1;
			mul<<=1;
		}
		if(a>b)
			a-=b;
		else
			b-=a;
	}
	glb_gcd = mul*a;
	return x%(mul*a);
}
long long get_ans(long long hp,long long re,long long K)
{
	//x*k - hp mod re = 0
	//re * b + hp mod k = 0
	hp %= re;
	if(hp<0)
		hp+=re;
	if(hp==0)
		return 0;
	long long b;
	b = get_ans(-hp,K,re%K);
	return b;
}
bool check(long long w)
{
	int i;
	for(i=1;i<=n;++i)
		if(w*dec[i]<hp[i]||(w*dec[i]-hp[i])%re[i]!=0)
			return 0;
	return 1;
}
long long calc()
{
	long long i;
	glb_gcd=1;
	for(i=1;i<=n;++i)
		check_sol(0,glb_gcd,re[i]);
	for(i=1;i;++i)
		if(check(i))
			return i;
	return -1;
}
int main()
{
	int T,i,j,K;
	long long max_ans=0,ans;
	for(scanf("%d",&T);T;--T)
	{
		max_ans = 0;
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;++i)
			scanf("%lld",hp+i);
		for(i=1;i<=n;++i)
			scanf("%lld",re+i);
		for(i=1;i<=n;++i)
			scanf("%d",award+i);
		for(i=1;i<=m;++i)
		{
			scanf("%d",K);
			swords.insert(K);
		}
		for(i=1;i<=n;++i)
		{
			auto tmp = swords.upper_bound(hp[i]);
			if(tmp == swords.end())
				tmp = swords.begin();
			K = *tmp;
			swords.erase(K);
			if(check_sol(hp[i],re[i],K))
			{
				puts("-1");
				break;
			}
			dec[i]=K;
			swords.insert(award[i]);
		}
		if(i==n+1)
			printf("%lld\n",calc());
	}
	return 0;
}
 
