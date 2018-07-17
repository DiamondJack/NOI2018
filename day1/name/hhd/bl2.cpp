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
const int N=1005;
char S[N];
int go[N*N][26];
int tag[N*N],tot=1;
int cho;
void build(char *str){
	int n=strlen(str+1);
	rep(i,1,n){
		int now=1;
		rep(j,i,n){
			if(!go[now][str[j]-'a']){
				go[now][str[j]-'a']=++tot;
			}
			now=go[now][str[j]-'a'];
		}
	}
}
namespace core{
	int go[N*N][26];
	int tot;
	int calc(char *s){
		rep(i,1,tot)memset(go[i],0,sizeof go[i]);
		tot=1;
		int n=strlen(s+1);
		rep(i,1,n){
			int now=1;
			rep(j,i,n){
				if(!go[now][s[j]-'a'])go[now][s[j]-'a']=++tot;
				now=go[now][s[j]-'a'];
			}
		}
		return tot-1;
	}
};
char t[N];
int main(){
	scanf("%s",S+1);
	build(S);
	int Q;scanf("%d",&Q);
	while(Q--){
		int l,r;
		scanf("%s%d%d",t+1,&l,&r);
		assert(l==1&&r==strlen(S+1));
		int ans=core::calc(t);
		++cho;
		int n=strlen(t+1);
		rep(i,1,n){
			int now=1;
			rep(j,i,n){
				if(!go[now][t[j]-'a'])break;
				now=go[now][t[j]-'a'];
				if(tag[now]!=cho){
					tag[now]=cho;
					--ans;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}






