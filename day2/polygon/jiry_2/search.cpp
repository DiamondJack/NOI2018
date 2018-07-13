#include <bits/stdc++.h>
using namespace std;
const int N=40;
int n,K,b[N][N],d[N];
vector<int>go[N];
void ade(int k1,int k2){
	go[k1].push_back(k2);
}
void add(int k1,int k2){
	ade(k1,k2); ade(k2,k1);
}
vector<int>A;
void dfs1(int k1,int k2){
	int flag=0;
	for (int j:go[k1]){
		if (j!=k2){
			dfs1(j,k1); flag=1;
		}
	}
	if (flag==0) A.push_back(k1);
}
int ans=0;
void dfs(int k1,int k2){
	if (k2==(1<<n)-1){
		if (b[k1][1]) ans++;
		return;
	}
	int where=0,num=0;
	if (k1>1)
		for (int j:go[k1]){
			d[j]--;
			if ((k2&(1<<j-1))==0&&d[j]==1) where=j,num++;
		}
	if (d[1]&&num<=1){
		if (num==1) dfs(where,k2|(1<<where-1));
		else for (int j:go[k1]) if ((k2&(1<<j-1))==0) dfs(j,k2|(1<<j-1));
	}
	if (k1>1) for (int j:go[k1]) d[j]++;
}
int main(){
	scanf("%d%d",&n,&K);
	for (int i=2;i<=n;i++){
		int k1=1; scanf("%d",&k1);
		b[k1][i]=b[i][k1]=1;
		add(i,k1);
	}
	dfs1(1,0);
	for (int i=0;i<A.size();i++)
		for (int j=1;j<=K;j++){
			int aim=(i+j)%A.size();
			b[A[i]][A[aim]]=b[A[aim]][A[i]]=1;
		}
	for (int i=1;i<=n;i++) go[i].clear();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) if (b[i][j]) go[i].push_back(j);
	for (int i=1;i<=n;i++) d[i]=go[i].size();
	/*for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++) cout<<b[i][j]; cout<<endl;
	}*/
	dfs(1,1);
	assert(ans%2==0);
	printf("%d\n",ans/2);
}






