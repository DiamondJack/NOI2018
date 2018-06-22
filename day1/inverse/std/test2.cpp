#include <bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
#define PER(i,x,y) for(int i=(int)x;i>=(int)y;i--)
#define FOR(i,x,y) for(int i=(int)x;i< (int)y;i++)
using namespace std;
const int N=1000005;
const int mo=998244353;

int n,perm[N],dp[1<<20][22][2];

int main(){
	scanf("%d",&n);
	REP(i,1,n) scanf("%d",perm+i);

	dp[0][0][0]=1;	
	
	for(int i=0;i<(1<<n)-1;i++)
	for(int c=0;c<2;c++){
		int mx=-1,num=0;
		for(int j=0;j<n;j++) if((i>>j)&1) mx=j,num++;
		int lim=c?0:perm[num+1]-1;
		for(int j=0;j<=n;j++) if(dp[i][j][c]){
			for(int k=max(lim,j);k<num;k++) if(!((i>>k)&1)){
				int nc=c|(k>lim);
				dp[i|(1<<k)][k+1][nc]=(dp[i|(1<<k)][k+1][nc]+dp[i][j][c])%mo;
			}
			for(int k=max(num,max(lim,mx+1));k<n;k++) if(!((i>>k)&1)){
				int nc=c|(k>lim);
				dp[i|(1<<k)][j][nc]=(dp[i|(1<<k)][j][nc]+dp[i][j][c])%mo;				
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++) ans=(ans+dp[(1<<n)-1][i][1])%mo;
	printf("%d\n",ans);
	return 0;
}
