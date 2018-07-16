#pragma GCC diagnostic error "-std=c++11"
#include<cstdio>
#include<cstdlib>
#include<set>
#include<cstring>
using namespace std;
int n,m;
int q,k,s;
struct ty{int u,v,l,a;}edge[400010];
int las[200010],to[800010],nex[800010],len[800010],at[800010],top;
int diss[200010];
struct ty2{int diss,num;}tmp,tmp2;
bool operator < (ty2 c1,ty2 c2)
{
	if(c1.diss!=c2.diss)
		return c1.diss<c2.diss;
	return c1.num<c2.num;
}
multiset <ty2> _S;
void dij(int S)
{
	memset(diss,60,sizeof(diss));
	diss[S]=0;
	tmp.diss=0;
	tmp.num=1;
	_S.insert(tmp);
	while(_S.size()>0)
	{
		auto w=_S.begin();
		tmp=*w;
		_S.erase(w);
		//printf("CC:\t%d\t%d\n",tmp.diss,tmp.num); 
		for(int i=las[tmp.num];i;i=nex[i])
			if(diss[tmp.num]+len[i]<diss[to[i]])
			{
				if(diss[to[i]]!=diss[0])
				{
					tmp2.diss=diss[to[i]];
					tmp2.num=to[i];
					_S.erase(_S.find(tmp2));
				}
				diss[to[i]]=diss[tmp.num]+len[i];
				tmp2.diss=diss[to[i]];
				tmp2.num=to[i];
				_S.insert(tmp2);
			}
	}
}
int tt[200010],tim;
int seq[200010],head,tail;
int bfs(int now,int lim)
{
	int ret=diss[now],i;
	tt[now]=tim;
	head=0;
	tail=1;
	seq[1]=now;
	while(head<tail)
	{
		++head;
		for(i=las[seq[head]];i;i=nex[i])
			if(at[i]>lim&&tt[to[i]]!=tim)
			{
				seq[++tail]=to[i];
				tt[to[i]]=tim;
				if(diss[to[i]]<ret)
					ret=diss[to[i]];
			}
	}
	return ret;
}
int main()
{
	//freopen("../data/15.in","r",stdin);
	int i,j,v0,p0,v,p,ans;
	int T;
	for(scanf("%d",&T);T;--T)
	{
		ans=0; 
		top=0;
		memset(las,0,sizeof(las));
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;++i)
		{
			scanf("%d%d%d%d",&edge[i].u,&edge[i].v,&edge[i].l,&edge[i].a);
			to[++top]=edge[i].u;
			nex[top]=las[edge[i].v];
			len[top]=edge[i].l;
			at[top]=edge[i].a;
			las[edge[i].v]=top;
			to[++top]=edge[i].v;
			nex[top]=las[edge[i].u];
			len[top]=edge[i].l;
			at[top]=edge[i].a;
			las[edge[i].u]=top;
		}
		dij(1);
		//for(i=1;i<=n;++i)
		//	printf("diss [ %d ] = %d\n",i,diss[i]);
		scanf("%d%d%d",&q,&k,&s);
		for(i=1;i<=q;++i)
		{
			//if(i%1000==0)
			//	printf("%d\n",i); 
			scanf("%d%d",&v0,&p0);
			v=(v0+k*ans-1)%n+1;
			p=(p0+k*ans)%(s+1);
			++tim;
			ans=bfs(v,p);
			//printf("S%d\t%d\n",v,p);
			printf("%d\n",ans);
		}
	}
	return 0;
} 
