#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=1000005;
int a[N],n,ans,ansx;
bool b[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int mx=0,mx2=0,rmn=1,nx=0;
	for(int i=1;i<=n;i++){
		for(;rmn<=n&&b[rmn];rmn++);
		if(rmn<mx2)break;
		for(nx=max(nx,max(a[i],mx)+1);nx<=n&&b[nx];nx++);
		if(nx<=n){
			ans=i;
			ansx=nx;
		}
		if(a[i]<mx2)break;
		b[a[i]]=1;
		if(a[i]>mx){
			mx=a[i];
		}else{
			mx2=max(mx2,a[i]);
		}
	}
	if(!ans)printf("No Solution\n");
	else{
		memset(b,0,sizeof(b));
		for(int i=1;i<ans;i++)b[a[i]]=1;
		a[ans]=ansx;
		b[ansx]=1;int now=ans+1;
		for(int i=1;i<=n;i++)if(!b[i])a[now++]=i;
		for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");
	}
	return 0;
}
