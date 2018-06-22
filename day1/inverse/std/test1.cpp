#include <bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
#define PER(i,x,y) for(int i=(int)y;i>=(int)x;i--)
using namespace std;
const int N=16;
const int mo=998244353;

int dp[1<<N][2][N*N*2];
int n,perm[N],num;

int main(){
	scanf("%d",&n);
	REP(i,1,n) scanf("%d",perm+i);
	int S=n*n;
	dp[0][0][S]=1;
	for(int i=0;i<(1<<n)-1;i++)
	for(int cur=0;cur<2;cur++){
		num=0;
		for(int j=0;j<n;j++) if((i>>j)&1) num++;
		int lim=cur?1:perm[num+1];
		for(int j=lim-1;j<n;j++) if(!((i>>j)&1)){
			int ccur=cur||(j>lim-1);
			int nst=i|(1<<j),sum=abs(j-num);
			for(int k=j+1;k<n;k++) if((i>>k)&1) sum-=2;
			for(int v=-S;v<=S;v++)if(v+sum>=-S&&v+sum<=S){
				dp[nst][ccur][v+sum+S]=(dp[nst][ccur][v+sum+S]+dp[i][cur][v+S])%mo;
			}
		}
	}
	printf("%d\n",dp[(1<<n)-1][1][S]);
	return 0;
}
