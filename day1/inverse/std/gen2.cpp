#include<bits/stdc++.h>
#define REP(i,x,y) for(int i=(int)x;i<=(int)y;i++)
using namespace std;

int n,a[1000005],b[1000005],totb,c[1000005],totc,tot;
int main(int argc,char **argv){
	freopen("1.in","w",stdout);
	n=1000000;
	if(argc>1){
		n=atoi(argv[1]);
	}
	printf("%d\n",n);
	REP(i,1,n) if(rand()&1) b[++totb]=i; else c[++totc]=i;
	int u=1,v=1;
	while(u<=totb||v<=totc){
		if(u>totb){
			a[++tot]=c[v]; v++; continue;
		}else
		if(v>totc){
			a[++tot]=b[u]; u++; continue;
		}else{
			if(rand()%2==1){
				a[++tot]=c[v]; v++; continue;
			}else{
				a[++tot]=b[u]; u++; continue;
			}
		}
	}
	REP(i,1,n) printf("%d ",a[i]); puts("");
	return 0;
}
