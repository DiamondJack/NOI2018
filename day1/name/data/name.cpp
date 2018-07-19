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

#define For(i,x,y) for (int i=x;i<y;i++)
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define lf else if
#define Mid ((L+R)>>1)

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;

int IN(){
	int c,f,x;
	while (!isdigit(c=getchar())&&c!='-');c=='-'?(f=1,x=0):(f=0,x=c-'0');
	while (isdigit(c=getchar())) x=(x<<1)+(x<<3)+c-'0';return !f?x:-x;
}

const int N=4e6+19;
const int Top=15000000;

bool st;

struct seg *null;
struct seg{
	seg *L,*R;
	int sum;
} Sd[Top],*scur=Sd+1;

struct node{
	node *go[26],*par;
	int val,vis;
	seg *rt;
} Nd[N],*las,*rt,*cur=Nd,*Q[N];

char str[N],*s[N],*now;
int len[N],l[N],r[N],cnt[N];
int n,Ql,Qr,Time;
ll ans;

void Ins(seg *&x,int L,int R,int Qx){
	if (x==null){
		x=scur++;
		*x=*null;
	}
	if (L==R){
		x->sum=1;
		return;
	}
	if (Qx<=Mid){
		Ins(x->L,L,Mid,Qx);
	} else{
		Ins(x->R,Mid+1,R,Qx);
	}
	x->sum=x->L->sum+x->R->sum;
}
seg *Merge(seg *A,seg *B,int L,int R){
	if (A==null) return B;
	if (B==null) return A;
	if (L==R){
		return A->sum?A:B;
	}
	seg *x=scur++;
	*x=*null;
	x->L=Merge(A->L,B->L,L,Mid);
	x->R=Merge(A->R,B->R,Mid+1,R);
	x->sum=x->L->sum+x->R->sum;
	return x;
}
int qry2(seg *x,int L,int R){
	if (L==R){
		assert(x->sum);
		return L;
	}
	if (x->R->sum){
		return qry2(x->R,Mid+1,R);
	} else{
		return qry2(x->L,L,Mid);
	}
}
int qry(seg *x,int L,int R){
	if (Ql<=L&&R<=Qr){
		if (x->sum) return qry2(x,L,R);
		return -1;
	}
	int tmp;
	if (Qr>Mid&&~(tmp=qry(x->R,Mid+1,R))) return tmp;
	if (Ql<=Mid&&~(tmp=qry(x->L,L,Mid))) return tmp;
	return -1;
}

bool ed;

node *New(int val){
	cur->rt=null;
	cur->val=val;
	return cur++;
}
node *Extend(int x){
	node *p=las;
	if (p->go[x]){
		node *t=p->go[x];
		if (t->val==p->val+1) return t;
		node *nt=New(p->val+1);
		nt->par=t->par;
		t->par=nt;
		memcpy(nt->go,t->go,sizeof(t->go));
		for (;p&&p->go[x]==t;p=p->par) p->go[x]=nt;
		return nt;
	} else{
		node *np=New(p->val+1);
		for (;p&&!p->go[x];p=p->par) p->go[x]=np;
		if (!p){
			np->par=rt;
		} else{
			node *t=p->go[x];
			if (t->val==p->val+1){
				np->par=t;
			} else{
				node *nt=New(p->val+1);
				nt->par=t->par;
				t->par=np->par=nt;
				memcpy(nt->go,t->go,sizeof(t->go));
				for (;p&&p->go[x]==t;p=p->par) p->go[x]=nt;
			}
		}
		return np;
	}
}
void work(node *x){
	if (x==rt||x->vis==Time) return;
	x->vis=Time;
	int p=qry(x->rt,1,len[0]);
	if (p==-1){
		ans+=x->val-x->par->val;
	} else{
		//max(x->mn,p-Ql+2)..x->val
		ans+=max(x->val-max(x->par->val+1,p-Ql+2)+1,0);
	}
	work(x->par);
}
void Input(int w){
	las=rt;
	scanf("%s",now+1);
	s[w]=now;
	len[w]=strlen(now+1);
	now+=len[w];
	For(i,1,len[w]+1){
		las=Extend(s[w][i]-'a');
	}
}

int main(){
	//freopen("name.in","r",stdin);
	//freopen("name.out","w",stdout);
	dprintf("%d\n",(&ed-&st)/1000000);
	null=Sd;
	*null=(seg){null,null,0};
	rt=las=New(0);
	now=str;
	Input(0);
	n=IN();
	For(i,1,n+1){
		Input(i);
		l[i]=IN();
		r[i]=IN();
	}
	node *x=rt;
	For(i,1,len[0]+1){
		x=x->go[s[0][i]-'a'];
		Ins(x->rt,1,len[0],i);
	}
	for (node *i=Nd;i<cur;i++) cnt[i->val]++;
	For(i,1,N) cnt[i]+=cnt[i-1];
	for (node *i=Nd;i<cur;i++) Q[cnt[i->val]--]=i;
	for (int i=cur-Nd;i>1;i--){
		Q[i]->par->rt=Merge(Q[i]->par->rt,Q[i]->rt,1,len[0]);
	}
	For(i,1,n+1){
		ans=0;
		node *x=rt;
		Time++;
		Ql=l[i];
		Qr=r[i];
		For(j,1,len[i]+1){
			x=x->go[s[i][j]-'a'];
			work(x);
		}
		printf("%lld\n",ans);
	}
}
