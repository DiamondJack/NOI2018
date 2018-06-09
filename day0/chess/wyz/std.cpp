#include <bits/stdc++.h>
#define ll long long
#define N 13
#define mp make_pair

using namespace std;



map<ll,int> dp;


int a[2][N][N];
int r,c;

int hei[N];
#define val(x) ((ll)hei[x]<<((x)<<2))

const int inf(1e9);


int solve(ll mask,int side){
	map<ll,int>::iterator it=dp.find(mask);
	if (it!=dp.end()) return it->second;
	int ret=-inf;
	for (int i=1;i<=r;++i)if (hei[i]<hei[i-1]){
		mask^=val(i);
		++hei[i];
		mask^=val(i);
		ret=max(ret,a[side][i][hei[i]]-solve(mask,side^1));
		mask^=val(i);
		--hei[i];
		mask^=val(i);
	}
	if (ret==-inf) ret=0;
	dp.insert(mp(mask,ret));
	return ret;
}

int main(){
	// for (int i=0;i<=11;++i) hex[i]=1LL<<(i<<2);
	scanf("%d%d",&r,&c);
	for (int k=0;k<2;++k)
		for (int i=1;i<=r;++i)for (int j=1;j<=c;++j)
			scanf("%d",&a[k][i][j]);
	dp.clear();
	memset(hei,0,sizeof(hei));hei[0]=c;
	int ans=solve(0,0);
	printf("%d\n",ans);
	return 0;
}