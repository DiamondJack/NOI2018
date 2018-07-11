#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
using namespace std;
typedef long long ll;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
map<ll,int>M;
const int N=1100,NS=2400,NL=10,mo=998244353;
struct atom{
	int m;
	int A[NL],d[NL];
	ll h;
	int totd;
	void gettotd(){
		totd=0;
		for (int i=0;i<=m;i++) totd+=2-d[i];
	}
	ll gethash(){
		ll k1=0;
		for (int i=0;i<=m;++i) k1=1ll*k1*10+A[i];
		for (int i=0;i<=m;++i) k1=1ll*k1*3+d[i];
		h=k1; return k1;
	}
	void print(){
		printf("%d\n",m);
		for (int i=0;i<=m;i++) printf("%d ",A[i]); puts("");
		for (int i=0;i<=m;i++) printf("%d ",d[i]); puts("");
	}
	void checkvalid(){
		for (int i=0;i<=m;i++) if (d[i]!=2) assert(A[i]!=0); else assert(A[i]==0);
		int t[20];
		memset(t,0x00,sizeof t);
		for (int i=0;i<=m;i++) t[A[i]]+=2-d[i];
		for (int i=0;i<=m;i++) if (A[i]) assert(t[A[i]]==2);
		int num=0;
		for (int i=0;i<=m;i++) assert(A[i]<=num+1),num=max(num,A[i]);
	}
}x[NS];
int len;
int A[NL],d[NL],t[NL];
vector<pair<int,int> >gof[NS][NS],addf[NS],allP;
int idx[NS],bo[NS],sign;
vector<int>go[N];
int n,K,m,f[N][NS],size[N];
int addin(atom k1){
	k1.gethash();
	if (M[k1.h]) return M[k1.h];
	assert(len+1<NS);
	x[++len]=k1; M[k1.h]=len; return len;
}
int link(int *A,int *d,int u,int v,int n){
	if (d[u]==2||d[v]==2||A[u]==A[v]) return 0;
	d[u]++; d[v]++;
	int k1=A[u],k2=A[v];
	for (int i=0;i<=n;i++) if (A[i]==k1) A[i]=k2;
	if (d[u]==2) A[u]=0;
	if (d[v]==2) A[v]=0;
	return 1;
}
int link2(int *A,int *d,int u,int v,int n){
	if (d[u]==2||d[v]==2) return 0;
	if (A[u]!=A[v]) return link(A,d,u,v,n);
	for (int i=0;i<=n;i++)
		if (d[i]<2&&A[i]!=A[u]) return 0;
	d[u]++; d[v]++;
	if (d[u]==2) A[u]=0;
	if (d[v]==2) A[v]=0;
	return 2;
}
int checkfinal(int *A,int *d,int n){
	for (int i=0;i<=n;i++) if (A[i]){
		assert(d[i]<2); return 0;
	}
	for (int i=0;i<=n;i++) assert(d[i]==2);
	return 1;
}
void normalize(int *A,int n){
	static int w[NL*2];
	int now=0;
	memset(w,0x00,sizeof w);
	for (int i=0;i<=n;i++)
		if (A[i]){
			if (w[A[i]]) A[i]=w[A[i]];
			else {
				now++; w[A[i]]=now; A[i]=now;
			}
		}
}
atom getatom(int *A,int *d,int n){
	atom res;
	if (n>K*2){
		for (int i=K+1;i<=n-K;i++)
			if (d[i]!=2){
				res.m=-1; return res;
			}
		int now=K;
		for (int i=n-K+1;i<=n;i++){
			now++; A[now]=A[i]; d[now]=d[i];
		}
		n=now;
	}
	res.m=n;
	for (int i=0;i<=n;i++) res.A[i]=A[i];
	for (int i=0;i<=n;i++) res.d[i]=d[i];
	return res;
}
void getaddf(int k1){
	// cout<<"addf "<<k1<<endl;
	static int A[NL];
	static int d[NL];
	int m=x[k1].m;
	int now=min(K,x[k1].m);
	int ma=0; sign++;
	for (int i=0;i<=x[k1].m;++i)
		if (x[k1].d[i]!=2) ma=max(ma,x[k1].A[i]);
	for (int isl=0;isl<2;isl++){
		if (isl&&x[k1].d[0]==2) continue;
		for (int S=0;S<(1<<now);++S){
			if (__builtin_popcount(S)>2) continue;
			memcpy(A,x[k1].A,sizeof x[k1].A);
			memcpy(d,x[k1].d,sizeof x[k1].d);
			A[m+1]=ma+1; d[m+1]=0;
			if (isl){
				if (link(A,d,0,m+1,m+1)==0) continue;
			}
			int flag=0;
			for (int i=1;i<=now;i++){
				if ((S&(1<<i-1))==0) continue;
				int id=x[k1].m-now+i;
				if (link(A,d,id,m+1,m+1)==0){
					flag=1; break;
				}
			}
			if (flag) continue;
			normalize(A,m+1);
			atom res=getatom(A,d,m+1);
			if (res.m==-1) continue;
			res.checkvalid();
			int where=addin(res);
			if (bo[where]!=sign){
				bo[where]=sign; addf[k1].push_back(mp(where,1));
				idx[where]=addf[k1].size()-1;
			} else addf[k1][idx[where]].se+=1;
		}
	}
}
int gtw=0;
void trylink(int now,int mid,int n,int *A,int *d,int u,int v){
	int preA[NL*2],pred[NL*2];
	for (int i=0;i<=n;i++) preA[i]=A[i],pred[i]=d[i];
	if (now>n||now>mid+K){
		normalize(A,n);
		atom res=getatom(A,d,n);
		if (res.m!=-1){
			res.checkvalid();
			int where=addin(res);
			if (bo[where]!=sign){
				bo[where]=sign; gof[u][v].push_back(mp(where,1));
				idx[where]=gof[u][v].size()-1;++gtw;
			} else {
				assert(gof[u][v].size()>idx[where]);
				gof[u][v][idx[where]].se+=1;
			}
		}
		for (int i=0;i<=n;++i){
			A[i]=preA[i],d[i]=pred[i];
		}
		return;
	}
	if (d[now]==2||n-now+1<=K||now<=K) trylink(now+1,mid,n,A,d,u,v);
	int l=max(1,now-K);
	if (d[now]==1||(d[now]==0&&(n-now+1<=K||now<=K))){
		for (int i=l;i<=mid;i++){
			if (link(A,d,i,now,n)) trylink(now+1,mid,n,A,d,u,v);
			for (int k=0;k<=n;k++) A[k]=preA[k],d[k]=pred[k]; 
		}
	}
	if (d[now]==0){
		for (int i=l;i<=mid;i++)
			for (int j=i+1;j<=mid;j++){
				if (link(A,d,i,now,n)&&link(A,d,j,now,n)) trylink(now+1,mid,n,A,d,u,v);
				for (int k=0;k<=n;k++) A[k]=preA[k],d[k]=pred[k]; 
			}
	}
}
void getgo(int k1,int k2){
	sign++;
	if (x[k2].d[0]==0) return;
	int n=x[k1].m+x[k2].m,ma=0;
	static int A[NL*2],d[NL*2];
	for (int i=0;i<=x[k1].m;++i){
		A[i]=x[k1].A[i]; d[i]=x[k1].d[i]; ma=max(ma,A[i]);
	}
	for (int i=1;i<=x[k2].m;++i){
		A[i+x[k1].m]=x[k2].A[i];
		if (A[i+x[k1].m]) A[i+x[k1].m]+=ma;
		d[i+x[k1].m]=x[k2].d[i];
	}
	A[n+1]=x[k2].A[0]+ma; d[n+1]=x[k2].d[0];
	if (d[n+1]==1){
		if (link(A,d,0,n+1,n+1)==0) return;
	}
	assert(d[n+1]==2);
	trylink(x[k1].m+1,x[k1].m,n,A,d,k1,k2);
}
int g[NS],de[N];
void dfs1(int k1){
	size[k1]=1;
	for (int i=0;i<go[k1].size();++i){
		int j=go[k1][i]; de[j]=de[k1]+1;
		dfs1(j); size[k1]+=size[j];
	}
}
inline void update(int &k1,long long k2){
	k1=(k1+k2)%mo;
}
int getansway(int now,int mid,int n,int* A,int *d){
	int preA[NL*2],pred[NL*2];
	for (int i=0;i<=n;i++) preA[i]=A[i],pred[i]=d[i];
	if (now>n){
		return 0;
	}
	for (int i=1;i<=n;i++){
		int num=2-d[i];
		for (int j=1;j<=n&&num;j++)
			if (abs(i-j)<=K||n-abs(i-j)<=K&&d[j]<2){
				if (i<=mid&&j<=mid&&abs(i-j)<=K) continue;
				if (i>mid&&j>mid&&abs(i-j)<=K) continue;
				num--;
			}
		if (num) return 0;
	}
	int b[10],len=0,ans=0,tot=0;
	for (int i=1;i<=n;i++)
		if ((abs(now-i)<=K||n-abs(now-i)<=K)&&d[i]<2){
			if (now<=mid&&i<=mid&&abs(now-i)<=K) continue;
			if (now>mid&&i>mid&&abs(now-i)<=K) continue;
			if (i<now) b[++len]=i; else tot++;
		}
	if (d[now]+tot>=2) ans+=getansway(now+1,mid,n,A,d);
	if (d[now]+tot+1>=2&&d[now]<=1){
		for (int i=1;i<=len;i++){
			int tag=link2(A,d,b[i],now,n);
			if (tag==2) ans++;
			else if (tag==1) ans+=getansway(now+1,mid,n,A,d);
			for (int k=0;k<=n;k++) A[k]=preA[k],d[k]=pred[k]; 
		}
	}
	if (d[now]==0){
		for (int i=1;i<=len;i++)
			for (int j=i+1;j<=len;j++){
				if (link2(A,d,b[i],now,n)){
					int tag=link2(A,d,b[j],now,n);
					if (tag==2) ans++;
					else if (tag) ans+=getansway(now+1,mid,n,A,d);
				}
				for (int k=0;k<=n;k++) A[k]=preA[k],d[k]=pred[k]; 
			}
	}
	return ans;
}
int mergeleaf(int k1){
	//cout<<k1<<endl;
	static int A[NL];
	static int d[NL];
	int m=x[k1].m;
	int now=min(K,x[k1].m);
	int ma=0; sign++;
	for (int i=0;i<=x[k1].m;++i)
		if (x[k1].d[i]!=2) ma=max(ma,x[k1].A[i]);
	vector<int>b;
	if (x[k1].d[0]==0) return 0;
	int n=x[k1].m;
	memcpy(A,x[k1].A,sizeof A);
	memcpy(d,x[k1].d,sizeof d);
	A[n+1]=ma+1; d[n+1]=0;
	if (x[k1].d[0]==1){
		if (link(A,d,0,n+1,n+1)==0) return 0;
	}
	int ans=getansway(1,x[k1].m,n+1,A,d);
	return ans;
}
int mergestate(int k1,int k2){
	sign++;
	if (x[k2].d[0]==0||x[k1].d[0]!=x[k2].d[0]||(x[k1].totd!=x[k2].totd&&x[k2].m>=K&&x[k1].m>=K)) return 0;
	int n=x[k1].m+x[k2].m,ma=0;
	static int A[NL*2],d[NL*2];
	for (int i=0;i<=x[k1].m;++i){
		A[i]=x[k1].A[i]; d[i]=x[k1].d[i]; ma=max(ma,A[i]);
	}
	for (int i=1;i<=x[k2].m;++i){
		A[i+x[k1].m]=x[k2].A[i];
		if (A[i+x[k1].m]) A[i+x[k1].m]+=ma;
		d[i+x[k1].m]=x[k2].d[i];
	}
	A[n+1]=x[k2].A[0]+ma; d[n+1]=x[k2].d[0];
	if (d[n+1]==1){
		if (link2(A,d,0,n+1,n+1)==0) return 0;
	}
	if (d[0]!=2) return 0;
	assert(d[n+1]==2);
	int ans=getansway(1,x[k1].m,n,A,d);
	return ans;
}
void getansleaf(){
	int ans=0;
	for (int i=1;i<=len;i++)
		if (f[1][i]){
			ans=(ans+1ll*f[1][i]*mergeleaf(i))%mo;
		}
	printf("%d\n",ans);
}
void getans(int k1){
	int ans=0;
	for (int i=1;i<=len;i++)
		if (f[1][i])
			for (int j=1;j<=len;j++)
				if (f[k1][j]){
					ans=(ans+1ll*f[1][i]*f[k1][j]%mo*mergestate(i,j))%mo;
				}
	printf("%d\n",ans);
}
void treedp(int k1){
	f[k1][1]=1;
	for (int i=0;i<go[k1].size();++i){
		int j=go[k1][i];
		if (k1==1&&i==go[k1].size()-1){
			if (size[j]==1){
				getansleaf();
			} else {
				treedp(j);
				getans(j);
			}
		} else if (size[j]==1){
			memcpy(g,f[k1],sizeof g);
			memset(f[k1],0x00,sizeof f[k1]);
			for (int a=1;a<=len;a++)
				if (g[a]){
					for (int k=0;k<addf[a].size();++k)
						update(f[k1][addf[a][k].fi],1ll*g[a]*addf[a][k].se);
				}
		} else {
			treedp(j);
			memcpy(g,f[k1],sizeof g);
			memset(f[k1],0x00,sizeof f[k1]);
			for (int a=0;a<allP.size();a++){
				int loc1=allP[a].first,loc2=allP[a].second;
				int now=1ll*g[loc1]*f[j][loc2]%mo;
				if (now){
					for (int b=0;b<gof[loc1][loc2].size();++b){
						update(f[k1][gof[loc1][loc2][b].fi],1ll*now*gof[loc1][loc2][b].se);
					}
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&K);
	len=1; x[1].m=0; x[1].A[0]=1; x[1].d[0]=0; M[x[1].gethash()]=1;
	int now=0,pre=0;
	while (1){
		pre=now; now=len;
		for (int i=1;i<=pre;i++)
			for (int j=pre+1;j<=now;j++)
				getgo(i,j);
		for (int i=pre+1;i<=now;i++)
			for (int j=1;j<=now;j++)
				getgo(i,j);
		for (int i=pre+1;i<=now;i++) getaddf(i);
		if (len==now) break;
	}
	//printf("_%d %d\n",len,gtw);
	int tot=0;
	for (int i=1;i<=len;i++)
		for (int j=1;j<=len;j++){
			if (gof[i][j].size()) allP.push_back(mp(i,j)),tot+=gof[i][j].size();
		}
	for (int i=2;i<=n;i++){
		int k1=(i-2)/3+1;//scanf("%d",&k1);
		go[k1].push_back(i);
	}
	for (int i=1;i<=len;i++) x[i].gettotd();
	dfs1(1);
	treedp(1);
}
