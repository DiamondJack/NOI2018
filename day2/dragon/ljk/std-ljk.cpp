#include<cstdio>
#include<algorithm>
#include<set>
#define N 100000

long long exgcd(long long a,long long b,long long&x,long long&y)
{
	if(a<b)return exgcd(b,a,y,x);
	if(b==0)
		{
		x=1;
		y=0;
		return a;
		}
	long long d=exgcd(b,a%b,x,y);
	long long tmpx=y;
	long long tmpy=x-a/b*y;
	x=tmpx;
	y=tmpy;
	return d;
}

long long product_mod(long long a,long long b,long long mod)
{
	if(b==0)return 0;
	long long t=product_mod(a,b>>1,mod);
	if(b&1)
		return (t+t+a)%mod;
	return (t+t)%mod;
}

int life[N];
int cure[N];
int drop[N];
int attack[N];

int T,n,m;
std::multiset<int>sword;
typedef std::multiset<int>::iterator IT;

int main()
{
scanf("%d",&T);
while(T--)
	{
	scanf("%d%d",&n,&m);
	sword.clear();
	for(int i=0;i<n;++i)scanf("%d",life+i);
	for(int i=0;i<n;++i)scanf("%d",cure+i);
	for(int i=0;i<n;++i)scanf("%d",drop+i);
	for(int i=0;i<m;++i)
		{
		int tmp;
		scanf("%d",&tmp);
		sword.insert(tmp);
		}
	int max=0;
	for(int i=0;i<n;++i)
		if(cure[i]!=1)
			{
			max=-1;
			break;
			}
		else
			max=std::max(max,life[i]);
	if(~max)
		{
		printf("%d\n",max);
		continue;
		}
	for(int i=0;i<n;++i)
		{
		IT tmp=sword.lower_bound(life[i]);
		if(tmp!=sword.begin()&&*tmp!=life[i])--tmp;
		attack[i]=*tmp;
		sword.erase(tmp);
		sword.insert(drop[i]);
		}
	long long ans=0;
	long long mod=1;
	long long x,y;
	bool flag=true;
	for(int i=0;i<n;++i)
		{
		long long d=exgcd(attack[i]*mod,cure[i],x,y);
		if((life[i]-ans*attack[i])%d)
			{
			flag=false;
			break;
			}
		long long tmp=mod;
		long long gcd=d;
		long long tmpx=x;
		d=exgcd(mod,cure[i],x,y);
		mod=mod/d*cure[i];
		ans+=product_mod(tmp,product_mod(tmpx,(life[i]-ans*attack[i])/gcd,mod),mod);
		ans%=mod;
		}
	if(flag)
		{
		if(ans<=0)ans+=mod;
		printf("%lld\n",ans);
		}
	else
		printf("-1\n");
	}
return 0;
}
