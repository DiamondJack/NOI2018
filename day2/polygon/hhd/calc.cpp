#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
typedef double db;
int f[10][10];
int c[10][10];
int dp[10];
int main(){
	f[1][1]=1;
	rep(i,1,7)rep(j,1,7)f[i+1][j]+=f[i][j]*j,f[i+1][j+1]+=f[i][j];
	rep(i,1,7)rep(j,1,7)dp[i]+=f[i][j];
	rep(i,0,7){
		c[i][0]=c[i][i]=1;
		rep(j,1,i-1)c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
	int ans=0;
	rep(i,0,7){
		ans+=(c[7][i]*(1<<(7-i)))*dp[i];
		printf("%d ",(c[7][i]*(1<<(7-i)))*dp[i]);
	}
	puts("");
	printf("%d\n",ans);
	return 0;
}






