#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <cassert>
#include <ctime>
using namespace std;
const int N=510000,M=260;
const int key=10007,mo=20000003;
char ch[N],s[N];
struct atom{
	int l,r,len;
	char *ch;
	unsigned long long *H;
	void scan(){
		scanf("%s",s+1); len=strlen(s+1);
		ch=new char[len+10];
		H=new unsigned long long[len+10];
		for (int i=1;i<=len;i++) ch[i]=s[i],H[i]=0;
		scanf("%d%d",&l,&r);
	}
	void updatehash(int l){
		for (int i=1;i<=len-l+1;i++)
			H[i]=H[i]*key+ch[i+l-1];
	}
}q[N+10];
long long ans[N+10];
int n,m;
vector<int>A;
unsigned long long H[N+10];
int fir[mo];
int ne[N],tot,f[N],pd[N],sign;
struct tree{
    int father,val,w,go[26],pd;
}t[N<<1];
int len,last;
int getnew(){
	len++;
	memset(t[len].go,0x00,sizeof t[len].go);
	t[len].father=t[len].val=t[len].w=t[len].pd=0;
	return len;
}
void insert(int k){
    int p=last,np=getnew(); t[np].val=t[p].val+1; t[p].w=1;
    for (;p&&t[p].go[k]==0;p=t[p].father) t[p].go[k]=np;
    if (p==0){
        t[np].father=1; last=np; return;
    }
    int q=t[p].go[k];
    if (t[q].val==t[p].val+1){
        t[np].father=q; last=np; return;
    }
    int nq=getnew(); t[nq].val=t[p].val+1; memcpy(t[nq].go,t[q].go,sizeof t[q].go);
    t[nq].father=t[q].father; t[np].father=nq; t[q].father=nq;
    for (;p&&t[p].go[k]==q;p=t[p].father) t[p].go[k]=nq;
    last=np; return;
}
void getsam(char *ch,int n){
	len=0; last=getnew(); t[1].val=1;
	for (int i=1;i<=n;i++) insert(ch[i]-'a');
}
int x[N<<1],c[N<<1];
void gettop(){
	for (int i=1;i<=len;i++) c[t[i].val]++;
    for (int i=1;i<=len;i++) c[i]+=c[i-1];
    for (int i=1;i<=len;i++){
        x[c[t[i].val]]=i; c[t[i].val]--;
    }
    for (int i=1;i<=len;i++) c[i]=0;
}
long long calc1(){
	long long ans=0;
	for (int i=2;i<=len;i++) ans+=t[i].val-t[t[i].father].val;
	return ans;
}
long long calc2(int l,int r){
	gettop(); int now=1,curlen=1; //cerr<<l<<" "<<r<<endl;
	for (int i=l;i<=r;i++){
		int k=ch[i]-'a';
		while (now&&t[now].go[k]==0) now=t[now].father,curlen=t[now].val;
		now=t[now].go[k]; curlen++; if (now==0) now=1,curlen=1;
		t[now].pd=max(t[now].pd,curlen); 
	}
	for (int i=len;i;i--) t[t[x[i]].father].pd=max(t[t[x[i]].father].pd,t[x[i]].pd);
	long long ans=0;
	for (int i=2;i<=len;i++)
		if (t[i].pd==0) ans+=t[i].val-t[t[i].father].val;
		else ans+=max(0,t[i].val-t[i].pd);
	return ans;
}
unsigned long long w[N];
int compare(int k1,int k2){
	return q[k1].r<q[k2].r;
}
void insert(unsigned long long k1,int where){
	int k=k1%mo;
	for (int i=fir[k];i;i=ne[i])
		if (w[i]==k1) {f[i]=where; return;}
	tot++; ne[tot]=fir[k]; fir[k]=tot; f[tot]=where; w[tot]=k1;
}
int find(unsigned long long k1,int lim){
	int k=k1%mo;
	for (int i=fir[k];i;i=ne[i])
		if (w[i]==k1){
			if (f[i]>=lim&&pd[i]!=sign){
				pd[i]=sign; return 1;
			}
			return 0;
		}
	return 0;
}
int calcHash(int where,int l){
	q[where].updatehash(l); int ans=0; sign++;
	for (int i=1;i<=q[where].len-l+1;i++)
		ans+=find(q[where].H[i],q[where].l);
	return ans;
}
int main(){
	scanf("%s",ch+1); n=strlen(ch+1);
	scanf("%d",&m); // cerr<<n<<" "<<m<<endl;
	memset(H,0x00,sizeof H);
	for (int i=1;i<=m;i++) q[i].scan();
	for (int i=1;i<=m;i++) if (q[i].len<=M) A.push_back(i);
	sort(A.begin(),A.end(),compare);
	for (int i=0;i<A.size();i++){
		getsam(q[A[i]].ch,q[A[i]].len);
		ans[A[i]]+=calc1();
		//cout<<A[i]<<" "<<ans[A[i]]<<endl;
	}
	int cur=A.size();
	for (int l=1;cur;l++){
		int pre=cur; cur=0;
		for (int i=0;i<pre;i++)
			if (q[A[i]].len>=l){
				A[cur]=A[i]; cur++;
			}
		if (cur==0) break;
		tot=0;
		for (int i=1;i<=n-l+1;i++)
			H[i]=H[i]*key+ch[i+l-1];
		int now=1;
		for (int i=0;i<cur;i++){
			while (now<=q[A[i]].r-l+1){
				insert(H[now],now); now++;
			}
			ans[A[i]]-=calcHash(A[i],l);
		}
		for (int i=1;i<now;i++) fir[H[i]%mo]=0;
	}
//	cerr<<(1.0*clock()-k)/CLOCKS_PER_SEC<<endl;
	for (int i=1;i<=m;i++) if (q[i].len>M){
		getsam(q[i].ch,q[i].len);// cerr<<len<<endl;
		ans[i]=calc2(q[i].l,q[i].r);
	}
	for (int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}




