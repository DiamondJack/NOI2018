#include<cstdio>
#include<algorithm>
#include<set>
#define N 100000

long long read()
{
long long ret=0;
char c=getchar();
while(c<'0'||c>'9')c=getchar();
while(c>='0'&&c<='9')
	{
	ret=(ret<<3)+(ret<<1);
	ret+=c-'0';
	c=getchar();
	}
return ret;
}

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
	if(b==-1)return (-a)%mod;
	long long t=product_mod(a,b>>1,mod);
	if(b&1)
		return (t+t+a)%mod;
	return (t+t)%mod;
}

long long life[N];
long long cure[N];
long long drop[N];
long long attack[N];

int T,n,m;
std::multiset<long long>sword;
typedef std::multiset<long long>::iterator IT;

int main()
{
scanf("%d",&T);
while(T--)
	{
	scanf("%d%d",&n,&m);
	sword.clear();
	for(int i=0;i<n;++i)life[i]=read();
	for(int i=0;i<n;++i)cure[i]=read();
	for(int i=0;i<n;++i)drop[i]=read();
	for(int i=0;i<m;++i)
		{
		long long tmp=read();
		sword.insert(tmp);
		}
	for(int i=0;i<n;++i)
		{
		IT tmp=sword.lower_bound(life[i]);
		if(tmp!=sword.begin()&&*tmp!=life[i])--tmp;
		attack[i]=*tmp;
		sword.erase(tmp);
		sword.insert(drop[i]);
		}
	long long max=0;
	for(int i=0;i<n;++i)
		if(cure[i]!=1)
			{
			max=-1;
			break;
			}
		else
			max=std::max(max,(life[i]+attack[i]-1)/attack[i]);
	if(~max)
		{
		printf("%lld\n",max);
		continue;
		}
	long long ans=0;
	long long mod=1;
	long long x,y;
	bool flag=true;
	for(int i=0;i<n;++i)
		{
		long long d=exgcd(cure[i],attack[i],x,y);
		if(life[i]%d)
			{
			flag=false;
			break;
			}
		life[i]/=d;
		cure[i]/=d;
		attack[i]/=d;
		}
	for(int i=0;i<n&&flag;++i)
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
		printf("%lld\n",ans%mod);
		}
	else
		printf("-1\n");
	}
return 0;
}
