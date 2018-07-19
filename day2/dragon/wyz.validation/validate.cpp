#include <bits/stdc++.h>
#include "testlib.h"
#define ll long long
#define pb push_back
#define mp make_pair

using namespace std;

namespace MillerRabin{

const int times=20;

ll Random(ll n){
	#ifdef _TESTLIB_H_
	return ((double)rnd.next()/RAND_MAX*n+0.5);
	#endif
	#ifndef _TESTLIB_H_
	return ((double)rand()/RAND_MAX*n+0.5);
	#endif
}

ll fast_mul(ll x,ll y,ll P){
	ll ret=0;
	while (y){
		if (y&1) ret=(ret+x)%P;
		x=(x+x)%P;
		y>>=1;
	}
	return ret;
}

ll fast_pow(ll x,ll y,ll P){
	ll ret=1;
	while (y){
		if (y&1) ret=fast_mul(ret,x,P);
		x=fast_mul(x,x,P);
		y>>=1;
	}
	return ret;
}

bool witness(ll a,ll n)
{
	ll tem=n-1;
	int j=0;
	while (tem%2==0){
		tem/=2;
		j++;
	}
	ll x=fast_pow(a,tem,n);
	if(x==1||x==n-1) return 1;
	while (j--){
		x=fast_mul(x,x,n);
		if(x==n-1) return 1;
	}
	return 0;
}

bool miller_rabin(ll n){
	if(n==2) return 1;
	if(n<2||n%2==0) return 0;
	for(int t=1;t<=times;++t){
		ll a=Random(n-2)+1;
		if(!witness(a,n)) return 0;
	}
	return 1;
}

inline bool isPrime(ll x){return miller_rabin(x);}

};


void readEOLN(){
	char ch=inf.readChar();
	if (ch=='\n') return;
	ensuref(ch=='\r',"Expected EOLN!!!");
	inf.readEoln();
}

vector<ll> a,p;
vector<int> att;
int n,m;

inline bool inRange(int x,int l,int r){
	return l<=x&&x<=r;
}

inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll lcm(const vector<ll>& a){
	ll ret=0;
	for (auto ele:a){
		ret=gcd(ret,ele);
	}
	return ret;
}

int main(int argc,char** argv){
	registerValidation();
	
	int index=0;
	if (argc>=2){
		freopen(argv[1],"r",stdin);
		printf("Validating testdata \"%s\"...",argv[1]);
	}
	if (argc>=3){
		index=atoi(argv[2]);
	}
	const int maxT(5);
	const int maxAtt(inRange(index,1,2)?(1):(inRange(index,3,7)?(1e5):(1e6)));
	const ll maxLcm(inRange(index,5,7)?(1e6):(1e12));
	const int maxN(inRange(index,5,7)?(1e3):(inRange(index,8,13)?(1):(1e5)));
	const int maxM(inRange(index,5,7)?(1e3):(inRange(index,1,4)||inRange(index,8,13)?(1):(1e5)));
	const ll maxP(inRange(index,5,7)?(1e5):(inRange(index,8,13)?(1e8):(inRange(index,1,4)||inRange(index,14,15)?(1):(1e12))));
	const ll maxA(inRange(index,1,7)?(1e5):(inRange(index,8,15)?(1e8):(1e12)));
	
	int T=inf.readInt(1,maxT,"n");
	readEOLN();

	for (int t=1;t<=T;++t){
		a.clear();
		p.clear();
		att.clear();
		
		n=inf.readInt(1,maxN,format("n[%d]",t));inf.readSpace();
		m=inf.readInt(1,maxM,format("m[%d]",t));
		readEOLN();
		
		for (int i=1;i<=n;++i){
			a.pb(inf.readLong(1,maxA,format("a[%d][%d]",t,i)));
			if (i==n) readEOLN();
			else inf.readSpace();
		}
		for (int i=1;i<=n;++i){
			p.pb(inf.readLong(1,maxP,format("p[%d][%d]",t,i)));
			if (i==n) readEOLN();
			else inf.readSpace();
		}
		for (int i=1;i<=n;++i){
			att.pb(inf.readInt(1,maxAtt,format("att[%d][%d]",t,i)));
			if (i==n) readEOLN();
			else inf.readSpace();
		}
		for (int i=1;i<=m;++i){
			att.pb(inf.readInt(1,maxAtt,format("att[%d][%d]",t,i)));
			if (i==m) readEOLN();
			else inf.readSpace();
		}
		
		ensuref(lcm(p)<=maxLcm,"testcase#%d  lcm too large.",t);
		
		if (inRange(index,14,15)){
			ensuref(n==maxN,"testcase#%d  n!=1e5",t);
			ensuref(m==maxM,"testcase#%d  m!=1e5",t);
		}
		if (inRange(index,16,17)){
			for (int i=0;i<p.size();++i)
				ensuref(MillerRabin::isPrime(p[i]),"testcase#%d  p[%d] is not prime.",t,i);
		}
		if (inRange(index,5,13)||inRange(index,16,20)){
			for (int i=0;i<n;++i)
				ensuref(a[i]<=p[i],"testcase#%d  i=%d   a[i]>p[i]",t,i);
		}
	}
	inf.readEof();
	
	puts("  OK!!");

	return 0;
}
