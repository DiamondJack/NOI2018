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
const int N=1005;
const int P=998244353;
const int M=5000;
map<LL,int>id;
int n,DD;
struct atom{
	int col[10];
	int rest[10];
	int m;
	LL hash;
	void prt(){
		printf("num:%d\n",m);
		rep(i,1,m)printf("%d ",col[i]);puts("");
		rep(i,1,m)printf("%d ",rest[i]);puts("");
	}
	void init(){
		m=0;
		hash=0;
		memset(col,0,sizeof col);
		memset(rest,0,sizeof rest);
	}
	LL gethash(){
		per(i,9,1)hash=hash*10ll+col[i];
		per(i,9,1)hash=hash*3ll+rest[i];
		hash=hash*20ll+m;
		return hash;
	}
	inline atom(LL ha=0){
		hash=ha;
		m=hash%20;
		hash/=20;
		rep(i,1,9)rest[i]=hash%3,hash/=3;
		rep(i,1,9)col[i]=hash%10,hash/=10;
		hash=ha;
	}
	void check(){
		assert(1<=m&&m<=2*DD+1);
		int all=0;
		rep(i,1,m)all+=rest[i];
		assert(all%2==0);
		rep(i,1,m)if(rest[i]==0||rest[i]==2)assert(col[i]==0);
		int dt=0;
		rep(i,1,m)dt=max(dt,col[i]);
		int num[33];
		memset(num,0,sizeof num);
		rep(i,1,m)num[col[i]]++;
		rep(i,1,dt)assert(num[i]==2);
	}
};
void recol(int *A,int m){
	static int B[25];int t=0;
	memset(B,0,sizeof B);
	rep(i,1,m)if(A[i]){
		if(!B[A[i]])B[A[i]]=++t;
		A[i]=B[A[i]];
	}
}
atom state[M];
int now=1;
int col[20];
int rest[20];
bool bel[N];
int need[20];
int m;
int way=0;
vector<pii> edge;
int gtw=0;
vector<pii>zy[M][M];
vector<pii>byfa[M];
int NX,NY;

int temp[M];
int cg=0;
void checkit(){
	rep(i,1,m)if(rest[i]||col[i])return;
	way++;
}
bool canuse(int x,int y,int *col,int *rest,int lst){
	if(rest[x]==0||rest[y]==0)return 0;
	if((col[x]==col[y]&&col[x]>0)&&lst==0)return 0;
	if(lst)assert(col[x]==col[y]&&col[x]>0);
	rest[x]--;
	rest[y]--;
	if(col[x]==0&&col[y]==0){
		col[x]=col[y]=19;
		recol(col,m);
	}
	else if(col[x]==0){
		col[x]=col[y];
		recol(col,m);
	}
	else if(col[y]==0){
		col[y]=col[x];
		recol(col,m);
	}
	else{
		int sx=col[x];
		int sy=col[y];
		rep(i,1,m)if(col[i]==sx)col[i]=sy;
		recol(col,m);
	}
	if(rest[x]==0)col[x]=0;
	if(rest[y]==0)col[y]=0;
	recol(col,m);
	return 1;
}
void finalsearch(int x,int *col,int *rest,int rd){
	if(x==edge.size()||rd==0){
		checkit();
		return;
	}
	int dcol[20],drest[20];
	rep(i,1,m)dcol[i]=col[i],drest[i]=rest[i];
	finalsearch(x+1,col,rest,rd);
	rep(i,1,m)col[i]=dcol[i],rest[i]=drest[i];
	int u=edge[x].fi;
	int v=edge[x].se;
	if(canuse(u,v,col,rest,rd==2)){
		finalsearch(x+1,col,rest,rd-2);
		rep(i,1,m)col[i]=dcol[i],rest[i]=drest[i];
	}
}
int calc(atom A){
	m=A.m;
	rep(i,1,m)col[i]=A.col[i];
	rep(i,1,m)rest[i]=A.rest[i];
	int sum=0;
	rep(i,1,m)sum+=rest[i];
	way=0;
	finalsearch(0,col,rest,sum);
	return way;
}
void trygen(int *col,int *rest){
	rep(i,1,m)if(rest[i]&&need[i])return;
	atom gt;gt.init();
	rep(i,1,m)if(!need[i]){
		++gt.m;
		gt.col[gt.m]=col[i];
		gt.rest[gt.m]=rest[i];
	}
	gt.gethash();
	if(!id[gt.hash]){
		id[gt.hash]=++now;
		state[now]=gt;
	}
	int ww=id[gt.hash];
	if(NY==-1){
		byfa[NX].pb(pii(ww,1));
		return;


		if(temp[ww]){
			byfa[NX][temp[ww]-1].se+=1;
		}
		else{
			++gtw;
			byfa[NX].pb(pii(ww,1));
			temp[ww]=byfa[NX].size();
		}
	}
	else{
		zy[NX][NY].pb(pii(ww,1));
		return;


		if(temp[ww]){
			zy[NX][NY][temp[ww]-1].se+=1;
		}
		else{
			++gtw;
			zy[NX][NY].pb(pii(ww,1));
			temp[ww]=zy[NX][NY].size();
		}
	}
}
bool useit(int x,int y,int *col,int *rest){
	if(rest[x]==0||rest[y]==0)return 0;
	if(col[x]==col[y]&&col[x]>0)return 0;
	rest[x]--;
	rest[y]--;
	if(col[x]==0&&col[y]==0){
		col[x]=col[y]=19;
		recol(col,m);
	}
	else if(col[x]==0){
		col[x]=col[y];
		recol(col,m);
	}
	else if(col[y]==0){
		col[y]=col[x];
		recol(col,m);
	}
	else{
		int sx=col[x];
		int sy=col[y];
		rep(i,1,m)if(col[i]==sx)col[i]=sy;
		recol(col,m);
	}
	if(rest[x]==0)col[x]=0;
	if(rest[y]==0)col[y]=0;
	recol(col,m);
	return 1;
}
int DJ;
int PP,QQ;
void before_search(){
	vector<pii> c=edge;edge.clear();
	PP=QQ=0;
	for(auto x:c){
		if(need[x.fi]||need[x.se])edge.pb(x);
		if(need[x.fi])++PP;
		if(need[x.se])++PP;
	}
	rep(i,1,m)if(need[i])QQ+=rest[i];
	DJ=edge.size();
	for(auto x:c){
		if(need[x.fi]||need[x.se]){}
			else edge.pb(x);
	}
}
void search(int x,int *col,int *rest,int tp=0,int tq=0){
	if(x==0){
		before_search();
		tp=PP;
		tq=QQ;
	}
	if(tp<tq)return;
	if(x==edge.size()){
		trygen(col,rest);
		return;
	}
	if(x==DJ){
		rep(i,1,m)if(need[i]&&rest[i])return;
	}
	int dcol[20];
	int drest[20];

	tp-=need[edge[x].fi]+need[edge[x].se];
	rep(i,1,m)dcol[i]=col[i],drest[i]=rest[i];
	search(x+1,col,rest,tp,tq);
	rep(i,1,m)col[i]=dcol[i],rest[i]=drest[i];

	if(useit(edge[x].fi,edge[x].se,col,rest)){
		if(need[edge[x].fi])--tq;
		if(need[edge[x].se])--tq;
		search(x+1,col,rest,tp,tq);
		rep(i,1,m)col[i]=dcol[i],rest[i]=drest[i];
	}
}
void clr(){
	cg=0;
	if(NY==-1){
		rep(i,0,byfa[NX].size()-1)temp[byfa[NX][i].fi]=0;
	}
	else{
		rep(i,0,zy[NX][NY].size()-1)temp[zy[NX][NY][i].fi]=0;
	}
}
void gen(int du,int dv){
	atom A=state[du];
	atom B=state[dv];
	if(A.m==1)return;
	NX=du;NY=dv;
	m=0;
	edge.clear();
	memset(col,0,sizeof col);
	memset(rest,0,sizeof rest);
	memset(need,0,sizeof need);
	if(B.m==1){
		rep(i,1,A.m){
			++m;rest[m]=A.rest[i];col[m]=A.col[i];
		}
		++m;rest[m]=B.rest[1];col[m]=(B.col[1]>0)*(B.col[1]+10);
		rep(i,2,A.m)if(A.m-i+1<=DD)edge.pb(pii(i,m));
		edge.pb(pii(1,m));
		rep(i,2,m)if(i-1<=DD||m-i+1<=DD){}else need[i]=1;
		recol(col,m);
		search(0,col,rest);
		clr();
		return;
	}
	m=1;col[1]=A.col[1];rest[1]=A.rest[1];
	m=2;col[2]=(B.col[1]>0)*(B.col[1]+10);rest[2]=B.rest[1];need[2]=1;
	edge.pb(pii(1,2));
	rep(i,2,A.m){
		++m;col[m]=A.col[i];rest[m]=A.rest[i];
	}
	int dj=m;
	rep(i,2,B.m){
		++m;col[m]=(B.col[i]>0)*(B.col[i]+10);rest[m]=B.rest[i];
	}
	rep(i,3,dj)rep(j,dj+1,m)if(j-i<=DD){
		//printf("__(%d,%d),%d %d\n",du,dv,i,j);
		edge.pb(pii(i,j));
	}
	rep(i,3,m)if(i-2<=DD||m-i+1<=DD){}else need[i]=1;
	recol(col,m);
	/*
	if(du==4&&dv==3){
		printf("here: %d\n",dj);
		rep(i,1,m)printf("%d ",col[i]);puts("");
		rep(i,1,m)printf("%d ",rest[i]);puts("");
		for(auto x:edge)printf("(%d,%d),",x.fi,x.se);puts("");
	}
	*/
	search(0,col,rest);
	clr();
	return;
}
void genfa(int du){
	NX=du;NY=-1;
	atom A=state[du];
	m=0;
	edge.clear();
	memset(col,0,sizeof col);
	memset(rest,0,sizeof rest);
	memset(need,0,sizeof need);
	if(A.m==1){
		m=2;
		col[1]=0;rest[1]=2;
		col[2]=A.col[1];rest[2]=A.rest[1];
		edge.pb(pii(1,2));
		search(0,col,rest);
		clr();
		return;
	}
	m=1;col[1]=0;rest[1]=2;
	rep(i,1,A.m){
		++m;col[m]=A.col[i];rest[m]=A.rest[i];
	}
	need[2]=1;edge.pb(pii(1,2));
	search(0,col,rest);
	clr();
}
int dp[N][M];
vector<int>go[N];
vector<int>A;
int tmp[M];
int LM,RM;
bool checkdisL(int u,int v){
	//printf("MM__%d %d\n",LM,RM);
	if(LM>=2*DD){
		if(u>DD)u+=LM-2*DD;
		if(v>DD)v+=LM-2*DD;
		if(v-u<=DD)return 0;
		if(u-1+LM-v+1+RM<=DD)return 1;
		else return 0;
	}
	if(v-u<=DD)return 0;
	if(u-1+LM-v+1+RM<=DD)return 1;
	assert(0);
}
bool checkdisR(int u,int v){
	//printf("MM__%d %d\n",LM,RM);
	if(RM>=2*DD){
		if(u>DD)u+=RM-2*DD;
		if(v>DD)v+=RM-2*DD;
		if(v-u<=DD)return 0;
		if(u-1+RM-v+1+LM<=DD){
			return 1;
		}else return 0;
	}
	if(v-u<=DD)return 0;
	if(u-1+RM-v+1+LM<=DD)return 1;
	assert(0);
}
int getans(int du,int dv){
	atom A=state[du];
	atom B=state[dv];
	m=0;
	memset(col,0,sizeof col);
	memset(rest,0,sizeof rest);
	edge.clear();
	if(B.m==1){
		rep(i,1,A.m){
			++m;rest[m]=A.rest[i];col[m]=A.col[i];
		}
		++m;rest[m]=B.rest[1];col[m]=(B.col[1]>0)*(B.col[1]+10);
		recol(col,m);
		edge.pb(pii(1,m));
		rep(i,2,A.m)if(A.m-i+1<=DD||i-1<=DD)edge.pb(pii(i,m));
		rep(i,2,A.m)rep(j,i+1,A.m)if(checkdisL(i-1,j-1))
		edge.pb(pii(i,j));
		int rd=0;
		rep(i,1,m)rd+=rest[i];
		way=0;
		//rep(i,0,edge.size()-1)printf("(%d,%d),",edge[i].fi,edge[i].se);puts("");
		finalsearch(0,col,rest,rd);
		//printf("new: %d %d\n",way,du);A.prt();B.prt();
		return way;
	}
	++m;rest[m]=A.rest[1];col[m]=A.col[1];
	++m;rest[m]=B.rest[1];col[m]=(B.col[1]>0)*(B.col[1]+10);
	edge.pb(pii(1,2));
	rep(i,2,A.m){
		++m;rest[m]=A.rest[i];col[m]=A.col[i];
	}
	int dj=m;
	rep(i,2,B.m){
		++m;rest[m]=B.rest[i];col[m]=(B.col[i]>0)*(B.col[i]+10);
	}
	rep(i,3,dj)rep(j,dj+1,m)if(j-i<=DD||m-j+i-3+1<=DD)edge.pb(pii(i,j));
	rep(i,2,A.m)rep(j,i+1,A.m)if(checkdisL(i-1,j-1))edge.pb(pii(i+1,j+1));
	rep(i,2,B.m)rep(j,i+1,B.m)if(checkdisR(i-1,j-1))edge.pb(pii(dj+i-1,dj+j-1));
	recol(col,m);
	int rd=0;
	rep(i,1,m)rd+=rest[i];
	way=0;
	finalsearch(0,col,rest,rd);
	return way;
}
void dfs(int x);
void calcans(){
	//state[3].prt();
	//state[4].prt();
	//state[6].prt();
	if(go[1].size()==1){
		printf("0\n");
		return;
	}
	for(int x:go[1])dfs(x);
	LM=A.size()-RM;
	int u=go[1][0];
	rep(i,1,now)if(dp[u][i]){
		for(auto y:byfa[i])dp[1][y.fi]=(dp[1][y.fi]+y.se*1ll*dp[u][i])%P;
	}
	rep(si,1,go[1].size()-2){
		int y=go[1][si];
		rep(i,1,now)tmp[i]=0;
		vector<int>ta,tb;ta.clear();tb.clear();
		rep(i,1,now)if(dp[1][i])ta.pb(i);
		rep(i,1,now)if(dp[y][i])tb.pb(i);
		for(int i:ta)for(int j:tb)
			for(auto w:zy[i][j]){
				if(si==2&&w.fi==7){
					//printf(">> %d %d %d %d %d\n",dp[1][i],dp[y][j],w.se,i,j);
				}
				tmp[w.fi]=(tmp[w.fi]+w.se*1ll*(dp[1][i]*1ll*dp[y][j]%P))%P;
			}
		rep(i,1,now)dp[1][i]=tmp[i];
	}
	u=go[1][go[1].size()-1];
	int ans=0;
	rep(i,1,now)if(dp[1][i]){
		rep(j,1,now)if(dp[u][j]){
			//printf("_out:%d %d\n",dp[1][i],dp[u][j]);
			ans=(ans+(getans(i,j)*1ll*dp[1][i]%P)*1ll*dp[u][j])%P;
		}
	}
	printf("%d\n",ans);
}
void dfs(int x){
	if(x==1){
		calcans();
		return;
	}
	if(!go[x].size()){
		dp[x][1]=1;
		A.pb(x);
		return;
	}
	for(int y:go[x])dfs(y);
	int u=go[x][0];
	rep(i,1,now)if(dp[u][i]){
		for(auto y:byfa[i])dp[x][y.fi]=(dp[x][y.fi]+y.se*1ll*dp[u][i])%P;
	}
	rep(si,1,go[x].size()-1){
		int y=go[x][si];
		rep(i,1,now)tmp[i]=0;
		vector<int>ta,tb;ta.clear();tb.clear();
		rep(i,1,now)if(dp[x][i])ta.pb(i);
		rep(i,1,now)if(dp[y][i])tb.pb(i);
		for(int i:ta)for(int j:tb)
			for(auto w:zy[i][j]){
				tmp[w.fi]=(tmp[w.fi]+w.se*1ll*(dp[x][i]*1ll*dp[y][j]%P))%P;
			}
		rep(i,1,now)dp[x][i]=tmp[i];
	}
}
void ddit(int x,int tag){
	bel[x]=tag;
	if(!go[x].size()){
		RM++;
	}
	for(int y:go[x]){
		ddit(y,tag);
	}
}
int main(){
	scanf("%d%d",&n,&DD);
	state[1].m=1;
	state[1].col[1]=0;
	state[1].rest[1]=2;
	state[1].gethash();
	id[state[1].hash]=1;
	int pre=0;
	while(1){
		int t=now;
		rep(i,1,pre)rep(j,pre+1,t){
			gen(i,j);
			gen(j,i);
		}
		rep(i,pre+1,t)rep(j,i+1,t){
			gen(i,j);
			gen(j,i);
		}
		rep(i,pre+1,t)gen(i,i);
		rep(i,pre+1,t)genfa(i);
		//printf("_%d\n",now);
		if(t==now)break;
		pre=t;
	}
	rep(i,1,now)state[i].check();
	//printf("%d %d\n",now,gtw);
	//return 0;
	rep(i,2,n){
		int x;x=(i-2)/3+1;
		scanf("%d",&x);
		go[x].pb(i);
	}

	ddit(go[1][go[1].size()-1],1);
	dfs(1);
	return 0;
}



