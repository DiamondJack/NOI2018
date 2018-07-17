#include<stdio.h>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<iostream>
#include<assert.h>
#include<queue>
#include<string>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=110000;
namespace solver{
	int go[N*50][26];
	int tot;
	int idx[N*50];
	void init(){
		rep(i,1,tot){
			idx[i]=0;
			rep(j,0,25)go[i][j]=0;
		}
		tot=1;
	}	
	void insall(char *s,int tag){
		int n=strlen(s+1);
		rep(i,1,n){
			int now=1;
			rep(j,i,n){
				if(!go[now][s[j]-'a']){
					go[now][s[j]-'a']=++tot;
				}
				now=go[now][s[j]-'a'];
				idx[now]|=tag;
			}
		}
	}
	int solve(char *s,char *t){
		init();
		insall(s,1);
		insall(t,2);
		int ans=0;
		rep(i,2,tot)if(idx[i]==2)++ans;
		return ans;
	}
};
char s[N],t[N];
char gt[N];
int main(){
	//freopen("name.in","r",stdin);
	//freopen("name.out","w",stdout);
	scanf("%s",s+1);
	int Q;scanf("%d",&Q);
	while(Q--){
		scanf("%s",t+1);
		int l,r;scanf("%d%d",&l,&r);
		rep(i,l,r)gt[i-l+1]=s[i];gt[r-l+2]='\0';
		printf("%d\n",solver::solve(gt,t));
	}
	return 0;
}







