#include<bits/stdc++.h>
using namespace std;

int n,a[1000005];
int main(){
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	fclose(stdin);
	bool f=0;
	for(int i=2;i<=n;i++)if(a[i]>a[i-1]){f=1;break;}
	if(f)next_permutation(a+1,a+1+n);
	else{
		n++;
		for(int i=1;i<=n;i++)a[i]=i;
	}
	freopen("1.in","w",stdout);
	printf("%d\n",n);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);printf("\n");
	return 0;
}
