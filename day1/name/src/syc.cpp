#include <bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
#define PER(i,x,y) for(int i=(int)x;i>=(int)y;i--)
#define FOR(i,x,y) for(int i=(int)x;i< (int)y;i++)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
using namespace std;
const int N=500005;

char s[N];

int dfn[N<<1],slen;
int ls[N*40],rs[N*40];
int rt[N<<1],segcnt,len[N<<1],Fa[20][N<<1];
int *fa=Fa[0];

namespace sam{
	int cnt=1,las=1;
	int tre[N<<1][26],dep[N<<1];
	int id[N<<1],lab[N<<1];
	
	void append(int w,int pos){
		int p=++cnt,q=las;
		len[p]=len[las]+1;
		lab[p]=pos;
		las=p;
		for(;q&&tre[q][w]==0;q=fa[q]) tre[q][w]=p;
		if(!q){
			fa[p]=1; return;
		}else{
			int gt=tre[q][w];
			if(len[q]+1==len[gt]){
				fa[p]=gt; return;
			}else{
				int nq=++cnt;
				len[nq]=len[q]+1;
				fa[nq]=fa[gt];
				fa[gt]=fa[p]=nq;
				memcpy(tre[nq],tre[gt],sizeof tre[nq]);
				for(;q&&tre[q][w]==gt;q=fa[q]) tre[q][w]=nq;
			}
		}
	}
	
	inline int cmp(const int &u,const int &v){
		return len[u]<len[v];
	}
	
	vector<int> E[N<<1];
	
	void initlca(){
		REP(i,1,19) REP(j,1,cnt) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
		REP(i,1,cnt) id[i]=i;
		sort(id+1,id+cnt+1,cmp);
		REP(i,2,cnt){
			int u=id[i];
			dep[u]=dep[fa[u]]+1;
		}
		REP(i,2,cnt) E[fa[i]].push_back(i);
	}

	int asklca(int u,int v){
		if(dep[u]<dep[v]) swap(u,v);
		PER(i,19,0) if(dep[Fa[i][u]]>=dep[v]) u=Fa[i][u];
		if(u==v) return u;
		PER(i,19,0) if(Fa[i][u]^Fa[i][v]) u=Fa[i][u],v=Fa[i][v];
		return fa[u];
	}
	
	void insert(int &x,int L,int R,int v){
		x=++segcnt;
		if(L==R) return;
		int md=(L+R)/2;
		if(v<=md) insert(ls[x],L,md,v); else insert(rs[x],md+1,R,v);
	}
	
	int merge(int u,int v){
		if(!u||!v) return u|v;
		int ret=++segcnt;
		ls[ret]=merge(ls[u],ls[v]);
		rs[ret]=merge(rs[u],rs[v]);
		return ret;
	}
	
	int dfntot;
	void dfs(int x){
		dfn[x]=++dfntot;
		if(lab[x]) insert(rt[x],1,slen,lab[x]);
		for(auto v:E[x]) dfs(v);
		for(auto v:E[x]){
			if(!rt[x]) rt[x]=rt[v]; else rt[x]=merge(rt[x],rt[v]);
		}
	}

	int askmax(int x,int l,int r){
		if(!x) return 0;
		if(l==r) return l;
		int md=(l+r)/2;
		int k1=askmax(rs[x],md+1,r);
		if(k1) return k1;
		return askmax(ls[x],l,md);
	}
	
	int ask(int x,int l,int r,int v){
		if(!x) return 0;
		if(l==r) return l;
		int md=(l+r)/2;
		if(v<=md) return ask(ls[x],l,md,v);
		int k1=ask(rs[x],md+1,r,v);
		if(k1) return k1;
		return askmax(ls[x],l,md);
	}
	
	int askpre(int x,int w){
		return ask(rt[x],1,slen,w);
	}
	
}


namespace sam2{
	int cnt=1,las=1;
	int tre[N<<1][26],len[N<<1],fa[N<<1];
	
	void init(){
		REP(i,1,cnt){
			len[i]=fa[i]=0;
			FOR(j,0,26) tre[i][j]=0;
		}
		cnt=las=1;
	}
	
	void append(int w,int pos){
		int p=++cnt,q=las;
		len[p]=len[las]+1;
		las=p;
		for(;q&&tre[q][w]==0;q=fa[q]) tre[q][w]=p;
		if(!q){
			fa[p]=1; return;
		}else{
			int gt=tre[q][w];
			if(len[q]+1==len[gt]){
				fa[p]=gt; return;
			}else{
				int nq=++cnt;
				len[nq]=len[q]+1;
				fa[nq]=fa[gt];
				fa[gt]=fa[p]=nq;
				memcpy(tre[nq],tre[gt],sizeof tre[nq]);
				for(;q&&tre[q][w]==gt;q=fa[q]) tre[q][w]=nq;
			}
		}
	}
	
	long long count(){
		long long ans=0;
		REP(i,1,cnt) ans+=len[i]-len[fa[i]];
		return ans;
	}
}


char A[N<<1]; int ql,qr,Alen;
int seqA[N<<1],seqB[N<<1],tot,id[N<<1];
long long ans;

inline int cmp(const int &u,const int &v){
	if(seqA[u]==seqA[v]) return seqB[u]<seqB[v];
	return dfn[seqA[u]]<dfn[seqA[v]];
}

void askquery(){
	int cur=1,curlen=0;
	tot=0; ans=0;
	REP(i,1,Alen){
		int w=A[i]-'a';
		while(cur&&!sam::tre[cur][w]){
			curlen=min(curlen,len[fa[cur]]); cur=fa[cur];
		}
		if(!cur){
			cur=1; curlen=0; continue;
		}
		curlen++; cur=sam::tre[cur][w];
		while(cur!=1){
			int curlas=sam::askpre(cur,qr);
			if(curlas-(len[fa[cur]]+1)+1<ql){
//			if(curlas-curlen+1<ql){
				curlen=min(curlen,len[fa[cur]]);
				cur=fa[cur];
			}else{
				curlen=min(curlen,curlas-ql+1); break;
			}
		}
		if(cur==1){
			cur=1; curlen=0; continue; 
		}
		ans+=curlen; ++tot;
		seqA[tot]=cur; seqB[tot]=curlen; id[tot]=tot;
	}
	REP(i,1,tot) id[i]=i;
	sort(id+1,id+tot+1,cmp);
	REP(i,1,tot-1){
		int k3=0;
		if(seqA[id[i]]==seqA[id[i+1]]){
			k3=min(seqB[id[i]],seqB[id[i+1]]);
		}else{
			int ww=sam::asklca(seqA[id[i]],seqA[id[i+1]]);
			k3=len[ww];
			if(ww==seqA[id[i]]) k3=seqB[id[i]];
		}
		ans-=k3;
	}
	sam2::init();
	REP(i,1,Alen) sam2::append(A[i]-'a',i);
	long long ans3=sam2::count();
	ans=ans3-ans;
	printf("%lld\n",ans);
}

int main(int argc,char** argv){
	//freopen("name.in","r",stdin);
	//freopen("name.out","w",stdout);
	
	
	scanf("%s",s+1);
	slen=strlen(s+1);
	REP(i,1,slen) sam::append(s[i]-'a',i); sam::initlca();
	sam::dfs(1);
	
	int q; scanf("%d",&q);
	int lensum=0;
	while(q--){
		scanf("%s%d%d",A+1,&ql,&qr);
		Alen=strlen(A+1);
		askquery();
	}
	
	return 0;
}
