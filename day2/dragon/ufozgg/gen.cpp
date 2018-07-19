#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<ctime>
#include<cmath>
#include<set>
#include<cassert>
using namespace std;
int n[24]={0,100000,100000,100000,100000,1000,1000,1000,1,1,1,1,1,1,100000,100000,100000,100000,100000,100000,100000};
int m[24]={0,1,1,1,1,1000,1000,1000,1,1,1,1,1,1,100000,100000,100000,100000,100000,100000,100000};
long long maxp[24]={0,1,1,1,1,100000,100000,100000,100000000,100000000,100000000,100000000,100000000,100000000,1,1,1000000000000LL,1000000000000LL,1000000000000LL,1000000000000LL,1000000000000LL};
long long maxa[24]={0,10000,10000,10000,10000,10000,10000,10000,100000000,100000000,100000000,100000000,100000000,100000000,100000000,100000000,1000000000000LL,1000000000000LL,1000000000000LL,1000000000000LL,1000000000000LL};
int maxatk[24]={0,1,1,100000,100000,100000,100000,100000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000,1000000};
int sp1[24]={0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1};
int sp2[24]={0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
char infile[10],oufile[10];
struct ty
{
	long long val,pla; 
}tmp;
bool operator < (ty c1,ty c2)
{
	if(c1.val!=c2.val)
		return c1.val<c2.val;
	return c1.pla<c2.pla;
}
multiset<ty>S0;
bool check_prime(long long Maxd)
{
	for(long long i=2;i*i<=Maxd;++i)
		if(Maxd%i==0)
			return false;
	return true;
}
long long get_rand()
{
	long long ret=rand();
	ret = ret<<15|rand();
	ret = ret<<15|rand();
	return ret;
}
long long get_prime(long long Maxd)
{
	if(Maxd>=100)
		Maxd-=get_rand()%(Maxd/5);
	while(!check_prime(Maxd))
		--Maxd;
	return Maxd;
}
long long a[100010],p[100010];
int atk[200010],cho[100010];
long long p0[10000],p0top;
long long noprime[100]={0,840,180,64,50400,5040};
multiset <long long>SS;
long long get_ans(int cas)
{
	int i;
	long long ret=0,A;
	SS.clear();
	for(i=n[cas]+1;i<=n[cas]+m[cas];++i)
		SS.insert(atk[i]);
	for(i=1;i<=n[cas];++i)
	{
		auto w=SS.upper_bound(a[i]);
		if(w!=SS.begin())
			--w;
		A=*w;
		SS.erase(w);
		if(ret<(a[i]+A-1)/A)
			ret=(a[i]+A-1)/A;
		SS.insert(atk[i]);
	}
	return ret;
}
int main()
{
	int i,j,pp;
	long long LCM;
	//freopen("1_20.gen","w",stdout);
	int cas;
	for(int cass=21;cass<=21;++cass)
	{
		if(cass!=21)
			cas=cass;
		else
			cas=cass;
		if(maxa[cas]>100)
			maxa[cas]-=get_rand()%(maxa[cas]/5);
		if(maxp[cas]>100)
			maxp[cas]-=get_rand()%(maxp[cas]/5);
		if(maxatk[cas]>100)
			maxatk[cas]-=get_rand()%(maxatk[cas]/5);
		printf("Cas %d\n",cas);
		sprintf(infile,"%d.in",cas);
		sprintf(oufile,"%d.ans",cas);
		FILE* inp=fopen(infile,"w");
		FILE* oup=fopen(oufile,"w");
		fprintf(inp,"5\n");
		for(int tt=1;tt<=5;++tt)
		{
			
			if(cass!=21)
				cas=cass;
			else
				cas=4*tt;
			if(8<=cas&&cas<=13)
			{
				long long A,B,P,ANS;
				if(tt==3)
					P=get_prime(1000000000000LL);
				else if(tt==4)
					P=get_prime(10000000000LL)*96;
				else
					P=1000000000000LL-get_rand()%100000000000LL;
				B=0;
				while(!B)
				{
					A=get_rand()%P+1;
					ANS=get_rand()%P+1;
					B=A*ANS%P;
				}
				fprintf(inp,"%lld\n%lld\n%lld\n%lld\n",B,P,1,A);
				fprintf(oup,"%lld\n",ANS);
				printf("ANS %lld\n",ANS);
				continue;
			}
		if(maxa[cas]>100)
			maxa[cas]-=get_rand()%(maxa[cas]/5);
		if(maxp[cas]>100)
			maxp[cas]-=get_rand()%(maxp[cas]/5);
		if(maxatk[cas]>100)
			maxatk[cas]-=get_rand()%(maxatk[cas]/5);
			fprintf(inp,"%d %d\n",n[cas],m[cas]);
			if(maxp[cas]==1)
			{
				for(i=1;i<=n[cas];++i)
					p[i]=1;
				LCM=1;
			}
			else
			{
				if(16<=cas&&cas<=17)
				{
					if(cas<=2)
					{
						long long p1,p2;
						p1=get_prime(1000);
						p2=get_prime(1000000000);
						for(i=1;i<=n[cas];++i)
							if(rand()&1)
								p[i]=p1;
							else
								p[i]=p2;
						LCM=p1*p2;
					}
					else if(cas==3)
					{
						long long LCM=get_prime(maxp[cas]);
						for(i=1;i<=n[cas];++i)
							p[i]=LCM;
					}
					else
					{
						long long p1,p2,p3;
						p1=get_prime(100);
						p3=get_prime(100);
						p2=get_prime(100000000);
						for(i=1;i<=n[cas];++i)
							if(rand()&1)
								p[i]=p2;
							else
							if(rand()&1)
								p[i]=p1;
							else
								p[i]=p3;
						LCM=p1*p2*p3;
					}
				}
				else
				{
					p0top=0;
					long long L0=noprime[tt];
					LCM=get_prime((sp2[cas]?1000000:1000000000000LL)/L0);
					if(LCM>maxp[cas])
						LCM=get_prime(maxp[cas]);
					for(i=1;i<=L0;++i)
						if(L0%i==0)
						{
							p0[++p0top]=i;
							if(i*LCM<=maxp[cas])
								p0[++p0top]=i*LCM;
						}
					for(i=1;i<=n[cas];++i)
						p[i]=p0[rand()%p0top+1];
					LCM*=L0;
				}
			}
			for(i=1;i<=n[cas]+m[cas];++i)
				atk[i]=get_rand()%maxatk[cas]+1;
			printf("%lld\n",LCM);
			if(LCM==1)
			{
				for(i=1;i<=n[cas];++i)
					a[i]=get_rand()%maxa[cas]+1;
			}
			else
			{
				long long ANS=LCM-get_rand()%(LCM/5);
				fprintf(oup,"%lld\n",ANS);
				S0.clear();
				for(i=n[cas]+1;i<=n[cas]+m[cas];++i)
				{
					tmp.pla=i;
					tmp.val=atk[i];
					S0.insert(tmp);
				}
				for(i=1;i<=n[cas];++i)
				{
					//ANS*atkx%p[i]==a[i]
					long long atkx=-1;
					int cc=0;//puts("x");
					while(atkx==-1||atkx*ANS%p[i]<atkx)
					{
						atkx=get_rand()%min(p[i],(long long)maxatk[cas])+1;
						++cc;
						if(cc%100==0)
							p[i]=p0[rand()%p0top+1];
					}
					//puts("xx");
					a[i]=atkx*ANS%p[i];
					//a[i]>=atkx
					//Del ( atkx , a[i] ]
					while(true)
					{
						tmp.val=atkx;
						tmp.pla=1e9;
						auto tu=S0.upper_bound(tmp);
						if(tu!=S0.end()&&(*tu).val<=a[i])
						{
							auto tty=*tu;
							S0.erase(tu);
							//printf("%lld\t%lld\n",tty.val,tty.pla);
							//getchar();
							tty.val=1;
							atk[tty.pla]=1;
							S0.insert(tty);
						}
						else
							break;
					}
					for(j=i-1;j>0;--j)
						if(a[j]>=atkx&&atkx>cho[j])
							break;
					bool flag=1;
					if(j)
					{
						tmp.val=atk[j];
						tmp.pla=j;
						auto tu=S0.find(tmp);
						if(tu==S0.end())
						{
							flag=1;
						}
						else
						{
							flag=0;
							auto tty=*tu;
							S0.erase(tu);
							atk[tty.pla]=atkx;
						}
					}
					if(flag)
					{
						if(i==1)
						{
							tmp.val=atk[n[cas]+1];
							tmp.pla=n[cas]+1;
						}
						else
						{
							tmp.val=atk[i-1];
							tmp.pla=i-1;
						}
						if(S0.find(tmp)!=S0.end())
							S0.erase(S0.find(tmp));
						tmp.val=atkx;
						if(i==1)
							atk[n[cas]+1]=atkx;
						else
							atk[i-1]=atkx;
					}
					tmp.pla=i;
					tmp.val=atk[i];
					cho[i]=atkx;
					//printf("INS %lld\n",tmp.pla);
					S0.insert(tmp);
					assert(cho[i]*ANS%p[i]==a[i]%p[i]);
				}
			printf("ANS %lld\n",ANS);
			}
			if(LCM==1)
			{
				printf("ANS %lld\n",get_ans(cas));
				fprintf(oup,"%lld\n",get_ans(cas));
			}
			for(i=1;i<=n[cas];++i)
				fprintf(inp,"%lld%c",a[i],n[cas]==i?'\n':' ');
			for(i=1;i<=n[cas];++i)
				fprintf(inp,"%lld%c",p[i],n[cas]==i?'\n':' ');
			for(i=1;i<=n[cas]+m[cas];++i)
				fprintf(inp,"%d%c",atk[i],(n[cas]==i||n[cas]+m[cas]==i)?'\n':' ');
		}
		fclose(inp);
		fclose(oup);
	}
	return 0;
}

