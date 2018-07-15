#include <bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
using namespace std;
const int N=1000005;

int n,res;
int perm[N];

int main(){
	freopen("inverse.in","r",stdin);
	freopen("inverse.out","w",stdout);
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		REP(i,1,n) scanf("%d",perm+i); res=0;
		while(next_permutation(perm+1,perm+n+1)){
			int ans=0;
			REP(i,1,n) ans+=abs(i-perm[i]); ans/=2;
			REP(i,1,n) REP(j,i+1,n) if(perm[i]>perm[j]) ans--;
			if(ans==0) res++;
		}
		printf("%d\n",res);
	}
}
