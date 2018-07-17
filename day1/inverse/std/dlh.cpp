#include<bits/stdc++.h>
using namespace std;

const int N=1200005,M=998244353;
int n,a[N],v[N],fc[N],fi[N];
int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1ll*fc[x]*fi[y]%M*fi[x-y]%M;
}
int fexp(int x,int t){
	if(!t)return 1;
	int tmp=fexp(x,t>>1);tmp=1ll*tmp*tmp%M;
	return (t&1)?1ll*tmp*x%M:tmp;
}
void Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)v[i]=0;
	int mx=0,l=1;
	long long ans=0;
	for(int i=1;i<=n;i++){
		mx=max(a[i],mx);int t=2*n-mx-i,s=n-i+1;
		ans=(ans+C(t,s)-C(t,s+1)+M)%M;
		if(l>a[i])ans=(ans+C(t,s-1)-C(t,s)+M)%M;
		if(a[i]!=mx&&a[i]!=l)break;
		for(v[a[i]]=1;v[l];l++);
	}
	printf("%d\n",ans);
}
int main(){
	fc[0]=1;
	for(int i=1;i<N;i++)fc[i]=1ll*fc[i-1]*i%M;
	fi[N-1]=fexp(fc[N-1],M-2);
	for(int i=N-2;i>=0;i--)fi[i]=1ll*fi[i+1]*(i+1)%M;
	int T;scanf("%d",&T);
	while(T--)Main();
	return 0;
}
