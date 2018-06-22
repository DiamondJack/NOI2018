#include <bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
#define PER(i,x,y) for(int i=(int)x;i>=(int)y;i--)
#define FOR(i,x,y) for(int i=(int)x;i< (int)y;i++)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
using namespace std;
typedef double db;
typedef long long ll;
const	int N=1000005;
const 	int mo=998244353;

int n,perm[N],ans,fac[N*2],ifac[N*2],lask=0;

int Pow(int x,int y,int p){
	int ans=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) ans=(ll)ans*x%p;
	return ans;
}

int C(int x,int y){
	if(x<0||x<y) return 0;
	return (ll)fac[x]*ifac[y]%mo*ifac[x-y]%mo;
}

int seq[N],tot,fir=1,app[N],mex=1;

int main(){
	scanf("%d",&n);
	*fac=*ifac=1;
	REP(i,1,n*2) fac[i]=(ll)fac[i-1]*i%mo;
	ifac[n*2]=Pow(fac[n*2],mo-2,mo);
	PER(i,n*2-1,1) ifac[i]=(ll)ifac[i+1]*(i+1)%mo;
//	REP(i,1,n) printf("%d ",ifac[i]);
	REP(i,1,n) scanf("%d",perm+i);
	int mx=0,cur=0,gg=0;
	REP(pre,1,n){
		gg=pre;
		int i=pre;
		if(cur&&max(perm[i]+1,lask+1)<=mx-1){
			while(fir<=tot&&seq[fir]<=perm[pre])++fir;
			int cld=0;
			if(mex>perm[i]) cld=1;
			ans=(ans+(ll)cld*(0ll+C(2*n-mx-pre,cur-1)-C(2*n-mx-pre,cur)+mo))%mo;
		}
		if(max(mx+1,perm[i]+1)<=n){
			int cc=max(mx+1,perm[i]+1);
			ans=(ans+C(2*n-cc-pre+1,n-pre+1)+mo-C(2*n-cc-pre+1,n-pre+2))%mo;
		}
		while(mex<=n&&app[mex])++mex;
		if(perm[pre]<=mx){
			if(perm[pre]!=mex) break;
			cur--;
			while(fir<=tot&&seq[fir]<=perm[pre])++fir;
			lask=perm[pre];
		}else{
			cur+=perm[pre]-mx;
			cur--;
			seq[++tot]=perm[pre];
			mx=perm[pre];
		}
		app[perm[pre]]=1;
		if(cur<0) break;
	}
	cerr<<gg<<endl;
	printf("%d\n",ans);
	return 0;
}
