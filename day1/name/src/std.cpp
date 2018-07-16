#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<assert.h>
#include<queue>
#include<string>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=1000500;
int maxdep=0;
char str[N>>1];
char qs[N>>1];
int n;
int go[N][26],tot,last,fail[N],len[N];
int ort[N];
void initsam(){
	tot=last=1;
}
void append(int c,int rt){
	int p=last;int np=++tot;len[np]=len[p]+1;ort[np]=rt;last=np;
    for(;p&&(!go[p][c]);p=fail[p])go[p][c]=np;
    if(!p){
        fail[np]=1;//lct::newson(1,np,pos);
    	return;
    }
    int gt=go[p][c];
    if(len[p]+1==len[gt]){
        fail[np]=gt;//lct::newson(gt,np,pos);
		return; 
	}
    int nt=++tot;len[nt]=len[p]+1;fail[nt]=fail[gt];fail[gt]=nt;
    fail[np]=nt;
    rep(i,0,25)go[nt][i]=go[gt][i];for(;p&&go[p][c]==gt;p=fail[p])go[p][c]=nt;
}
int root[N];
int cl[N*30],cr[N*30],sum[N*30],segtot;
int id[N];
void segadd(int &me,int l,int r,int x,int v){
	int d=++segtot;
	cl[d]=cl[me];
	cr[d]=cr[me];
	sum[d]=sum[me]+v;
	me=d;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)segadd(cl[me],l,mid,x,v);
	else segadd(cr[me],mid+1,r,x,v);
}
int merge(int a,int b,int l,int r){
	if(!a||!b)return a+b;
	if(l==r){
		int c=++segtot;
		sum[c]=sum[a]+sum[b];
		return c;
	}
	int mid=(l+r)>>1;
	int d=++segtot;
	cl[d]=merge(cl[a],cl[b],l,mid);
	cr[d]=merge(cr[a],cr[b],mid+1,r);
	sum[d]=sum[cl[d]]+sum[cr[d]];
	assert(sum[d]==sum[a]+sum[b]);
	return d;
}
inline bool cmplen(const int &x,const int &y){
	return len[x]<len[y];
}
struct lk{
	int np,p;
	lk(int _np=0,int _p=0):np(_np),p(_p){}
};
int head[N];
lk stree[N];
int stot;
int dfn[N],ed[N],dftot;
int dep[N];
int ff[21][N];
int segask(int me,int l,int r,int up){
	if(l>up)return 0;
	if(!sum[me])return 0;
	if(l==r)return l;
	int mid=(l+r)>>1;
	int x=segask(cr[me],mid+1,r,up);
	if(x)return x;
	return segask(cl[me],l,mid,up);
}
int asklen(int me,int l,int r){
	int t=segask(root[me],1,n,r);
	int res=min(len[me],max(t-l+1,0));
	return res;
}
void dfs(int x){
	dfn[x]=++dftot;
	for(int u=head[x];u;u=stree[u].np){
		int y=stree[u].p;
		dep[y]=dep[x]+1;
		maxdep=max(maxdep,dep[y]);
		dfs(y);
	}
	ed[x]=dftot;
}
int lca(int a,int b){
	if(dep[a]<dep[b])swap(a,b);
	per(i,20,0)if((1<<i)&(dep[a]-dep[b]))a=ff[i][a];
	if(a==b)return a;
	per(i,20,0)if(ff[i][a]!=ff[i][b]){
		a=ff[i][a];b=ff[i][b];
	}
	return fail[a];
}
void initall(){
	initsam();
	rep(i,1,n){
		append(str[i]-'a',i);
	}
	rep(i,1,tot)id[i]=i;
	sort(id+1,id+1+tot,cmplen);
	per(i,tot,1){
		int x=id[i];
		if(ort[x]){
			segadd(root[x],1,n,ort[x],1);
		}
		if(fail[x])root[fail[x]]=merge(root[fail[x]],root[x],1,n);
	}
	rep(i,1,tot)if(fail[i]){
		stree[++stot]=lk(head[fail[i]],i);
		head[fail[i]]=stot;
	}
	dfs(1);
	rep(i,1,tot){
		ff[0][i]=fail[i];
	}
	rep(j,1,20)rep(i,1,tot)ff[j][i]=ff[j-1][ff[j-1][i]];
}
pii trace[N<<1];
int t;
void walk(int l,int r){
	t=0;
	int now=1;
	int nowlen=0;
	int m=strlen(qs+1);
	rep(i,1,m){
		while(now!=1&&!go[now][qs[i]-'a']){
			now=fail[now];
			nowlen=min(nowlen,len[now]);
		}
		if(!go[now][qs[i]-'a']){
			now=1;
			nowlen=0;
		}
		else{
			now=go[now][qs[i]-'a'];
			nowlen++;
		}
		while(now!=1){
			int rp=min(asklen(now,l,r),nowlen);
			if(rp>=len[fail[now]]+1){
				nowlen=rp;
				break;	
			}
			now=fail[now];
			nowlen=min(nowlen,len[now]);
		}
		trace[++t]=pii(now,nowlen);
	}
}
inline bool cmp2(const pii &x,const pii &y){
	if(x.fi!=y.fi)return dfn[x.fi]<dfn[y.fi];
	return x.se>y.se;
}
pii po[N<<1];
int m=0;
int dj[N];
int cho;
int ret=0;
//
namespace core{
	int head[N],np[N],tot,p[N];
	int stk[N],t;
	int malen[N];
	int fa[N];
	void dfs(int x){
		for(int u=head[x];u;u=np[u]){
			int y=p[u];
			dfs(y);
			malen[x]=max(malen[x],malen[y]);
		}
		malen[x]=min(malen[x],len[x]);
	}
	void sou(int x){
		if(!x)return;
		if(dj[x]==cho)return;
		dj[x]=cho;
		++ret;
		sou(fail[x]);
	}
	LL calcit(pii *a,int n){
		rep(i,1,tot)np[i]=p[i]=0;tot=0;
		rep(i,1,n)head[a[i].fi]=0,malen[a[i].fi]=a[i].se;

		/*
		++cho;ret=0;
		rep(i,1,n)sou(a[i].fi);
		cerr<<ret<<endl;
		*/
		t=0;
		stk[t=1]=a[1].fi;
		assert(stk[1]==1);
		rep(i,2,n){
			int x=a[i].fi;
			while(!(dfn[stk[t]]<=dfn[x]&&ed[x]<=ed[stk[t]]))--t;
			fa[x]=stk[t];
			++tot;p[tot]=x;np[tot]=head[fa[x]];head[fa[x]]=tot;
			stk[++t]=x;
		}
		dfs(1);
		LL ans=0;
		rep(i,1,n){
			int x=a[i].fi;
			ans+=malen[x]-len[fa[x]];
		}
		return ans;
	}
};
//
LL work(int l,int r){
	walk(l,r);
	if(!t){
		return 0;
	}
	sort(trace+1,trace+1+t,cmp2);
	m=0;
	rep(i,1,t)if((i==1)||(trace[i].fi!=trace[i-1].fi))po[++m]=trace[i];
	int om=m;
	rep(i,1,om-1)po[++m]=pii(lca(po[i].fi,po[i+1].fi),0);
	po[++m]=pii(1,0);
	sort(po+1,po+1+m,cmp2);
	om=m;m=0;
	rep(i,1,om)if(i==1||(po[i].fi!=po[i-1].fi))po[++m]=po[i];
	return core::calcit(po,m);
}
namespace simplesam{
	int go[N][26],tot,last,fail[N],len[N];
	void initsam(){
		rep(i,1,tot){
			fail[i]=len[i]=0;
			rep(j,0,25)go[i][j]=0;
		}
		tot=last=1;
	}
	void append(int c,int rt){
		int p=last;int np=++tot;len[np]=len[p]+1;ort[np]=rt;last=np;
	    for(;p&&(!go[p][c]);p=fail[p])go[p][c]=np;
	    if(!p){
	        fail[np]=1;//lct::newson(1,np,pos);return;
	    	return;
	    }
	    int gt=go[p][c];
	    if(len[p]+1==len[gt]){
	        fail[np]=gt;//lct::newson(gt,np,pos);
			return; 
		}
	    int nt=++tot;len[nt]=len[p]+1;fail[nt]=fail[gt];fail[gt]=nt;
	    fail[np]=nt;
	    rep(i,0,25)go[nt][i]=go[gt][i];for(;p&&go[p][c]==gt;p=fail[p])go[p][c]=nt;
	}
	LL calc(char *s){
		int n=strlen(s+1);
		initsam();
		rep(i,1,n)append(s[i]-'a',i);
		LL ans=0;
		rep(i,1,tot)ans+=len[i]-len[fail[i]];
		return ans;
	}
}
int main(){
	//freopen("name.in","r",stdin);
	//freopen("name.out","w",stdout);
	scanf("%s",str+1);
	n=strlen(str+1);
	initall();
	int Q;scanf("%d",&Q);
	cerr<<Q<<endl;
	while(Q--){
		int l,r;scanf("%s%d%d",qs+1,&l,&r);
		assert(1<=l&&l<=r&&r<=n);
		printf("%lld\n",simplesam::calc(qs)-work(l,r));
	}
	cerr<<"maxdep:"<<maxdep<<endl;
	return 0;
}





