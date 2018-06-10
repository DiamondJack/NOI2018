#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize("-O2")
#include <bits/stdc++.h>

using namespace std;
inline int read(){
	int x;scanf("%d",&x);return x;
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while ('0'<=ch&&ch<='9'){
		ret=ret*10-48+ch;
		ch=getchar();
	}
	return ret;
}

const int P=998244353;

inline int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=1LL*ret*x%P;
		x=1LL*x*x%P;
		y>>=1;
	}
	return ret;
}

inline int inv(int x){
	return fast_pow(x,P-2);
}

const int N=205;


int m[N];
int f[N][N];

void attack(){
	int id=read();
	int u=read(),v=read(),p=1LL*u*inv(v)%P;
	for (int j=0;j<=m[id];++j)
		f[id][j]=(1LL*f[id][j+1]*p+1LL*f[id][j]*(j>0?1-p+P:1))%P;
}

int n;
int id[N];
int dp[N];

void trans(int k,int p){
	// printf("[debug] %d\n",p);
	for (int j=0;j<=k;++j)
		dp[j]=(1LL*dp[j+1]*p+1LL*dp[j]*(1-p+P))%P;
}

void invTrans(int k,int p){
	int q=inv(1-p+P);
	for (int j=k;j>=0;--j)
		dp[j]=((dp[j]-1LL*dp[j+1]*p)%P+P)*q%P;
}

int _inv[N];

void pick(){
	int k=read();
	memset(dp,0,sizeof(dp));
	dp[k]=1;
	for (int i=1;i<=k;++i)
		trans(k,f[id[i]=read()][0]);
	for (int i=1;i<=k;putchar((++i>k)?'\n':' '))if (f[id[i]][0]!=1){
		invTrans(k,f[id[i]][0]);
		
		int ans=0;
		for (int j=1;j<=k;++j)
			ans=(ans+1LL*dp[j]*_inv[j])%P;
		#ifdef DEBUG
		putchar('[');
		for (int j=0;j<=k;++j) printf("%d ",dp[j]);
		putchar(']');
		#endif
		ans=1LL*ans*(1-f[id[i]][0]+P)%P;
		
		printf("%d",ans);
		
		trans(k,f[id[i]][0]);
	}
	else printf("%d",0);
}


int main(){
#ifdef FILE_IO
	freopen("faceless.in","r",stdin);
	freopen("faceless.out","w",stdout);
#endif
	n=read();
	for (int i=1;i<=n;++i) _inv[i]=inv(i);
	for (int i=1;i<=n;++i) m[i]=read();
	memset(f,0,sizeof(f));
	for (int i=1;i<=n;++i) f[i][m[i]]=1;
	for (int Q=read();Q;Q--){
		int op=read();
		if (op==0) attack();
		else pick();
	}
	for (int i=1;i<=n;++i){
		int ans=0;
		for (int j=m[i];j>=0;--j)
			ans=(ans+1LL*f[i][j]*j)%P;
		#ifdef DEBUG
		putchar('[');for (int j=m[i];j>=0;--j) printf("%d ",f[i][j]);putchar(']');
		#endif
		printf("%d",ans);
		if (i==n) puts("");
		else putchar(' ');
	}
	return 0;
}
