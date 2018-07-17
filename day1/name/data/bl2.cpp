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
typedef double db;
const int N=510000;
int go[N<<1][26],fail[N<<1],len[N<<1],tot,last;
char S[N],str[N];
void initsam(){
	rep(i,1,tot){
		len[i]=fail[i]=0;
		rep(j,0,25)go[i][j]=0;
	}
	tot=last=1;
}
void addchar(int c){
	int p=last;int np=++tot;len[np]=len[p]+1;last=np;
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
int q[N<<1];
inline bool cmp(const int &x,const int &y){
	return len[x]<len[y];
}
int zy[N<<1];
LL work(int l,int r){
	rep(i,1,tot)q[i]=i;
	sort(q+1,q+1+tot,cmp);
	rep(i,1,tot)zy[i]=0;
	int now=1;int nowlen=0;
	rep(i,l,r){
		int c=S[i]-'a';
		while(now!=1&&!go[now][c]){
			now=fail[now];
			nowlen=min(nowlen,len[now]);
		}
		if(!go[now][c]){
			nowlen=0;
		}
		else{
			now=go[now][c];
			++nowlen;
			assert(len[fail[now]]+1<=nowlen&&nowlen<=len[now]);
			zy[now]=max(zy[now],nowlen);
		}
	}
	per(i,tot,1){
		int x=q[i];
		if(fail[x]){
			zy[fail[x]]=max(zy[fail[x]],min(len[fail[x]],zy[x]));
		}
	}
	LL ans=0;
	rep(i,1,tot){
		ans+=len[i]-max(len[fail[i]],zy[i]);
	}
	return ans;
}
namespace S_sam{
	int go[N<<1][26],fail[N<<1],len[N<<1],tot,last;
	int ort[N<<1];
	int cl[N*50],cr[N*50],ma[N*50],segtot;
	int root[N<<1],n;
	void addchar(int c,int rt){
		int p=last;int np=++tot;len[np]=len[p]+1;last=np;ort[last]=rt;
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
	    rep(i,0,25)go[nt][i]=go[gt][i];
	    for(;p&&go[p][c]==gt;p=fail[p])go[p][c]=nt;
	}
	int q[N<<1];
	inline bool cmp(const int &x,const int &y){
		return len[x]<len[y];
	}
	inline void update(int me){
		ma[me]=1+ma[cl[me]]+ma[cr[me]];
	}
	void addit(int &me,int l,int r,int x){
		int d=++segtot;
		ma[d]=ma[me]+1;
		cl[d]=cl[me];
		cr[d]=cr[me];
		me=d;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid)addit(cl[me],l,mid,x);
		else addit(cr[me],mid+1,r,x);
	}
	int merge(int a,int b,int l,int r){
		if(!a||!b)return a+b;
		int c=++segtot;
		if(l==r){
			ma[c]=ma[a]+ma[b];
			return c;
		}
		int mid=(l+r)>>1;
		cl[c]=merge(cl[a],cl[b],l,mid);
		cr[c]=merge(cr[a],cr[b],mid+1,r);
		update(c);
		return c;
	}
	int segask(int me,int l,int r,int x){
		if(!me)return 0;
		if(!ma[me])return 0;
		if(l>x)return 0;
		if(l==r)return l;
		int mid=(l+r)>>1;
		int ret=segask(cr[me],mid+1,r,x);
		if(ret)return ret;
		return segask(cl[me],l,mid,x);
	}
	void init(char *str){
		tot=last=1;
		n=strlen(str+1);
		rep(i,1,n)addchar(str[i]-'a',i);
		rep(i,1,tot)q[i]=i;
		sort(q+1,q+1+tot,cmp);
		per(i,tot,1){
			int x=q[i];
			if(ort[x])addit(root[x],1,n,ort[x]);
			if(fail[x])root[fail[x]]=merge(root[fail[x]],root[x],1,n);
		}
	}
	int tr[500000][26],ts;
	int ql,qr;
	int ans=0;
	void dfs(int x,int now,int nowlen){
		if(x!=1){
			//if(nowlen==1)printf("_%d\n",segask(root[now],1,n,qr));
			if(now&&(segask(root[now],1,n,qr)-nowlen+1>=ql)){
				//printf("_%d\n",nowlen);
			}
			else ++ans;
		}
		rep(i,0,25)if(tr[x][i]){
			dfs(tr[x][i],go[now][i],nowlen+1);
		}
	}
	int calc(int l,int r,char *t){
		ans=0;
		int m=strlen(t+1);
		ql=l;
		qr=r;
		rep(i,1,ts)memset(tr[i],0,sizeof tr[i]);
		ts=1;
		rep(i,1,m){
			int now=1;
			rep(j,i,m){
				int c=t[j]-'a';
				if(!tr[now][c])tr[now][c]=++ts;
				now=tr[now][c];
			}
		}
		dfs(1,1,0);
		return ans;
	}
};
int main(){
	//freopen("name.in","r",stdin);
	//freopen("name.out","w",stdout);
	scanf("%s",S+1);
	S_sam::init(S);
	int Q;scanf("%d",&Q);
	while(Q--){
		int l,r;scanf("%s%d%d",str+1,&l,&r);
		int m=strlen(str+1);
		if(m<=300){
			printf("%d\n",S_sam::calc(l,r,str));
		}
		else{
			initsam();
			rep(i,1,m)addchar(str[i]-'a');
			printf("%lld\n",work(l,r));
		}
	}
	return 0;
}






