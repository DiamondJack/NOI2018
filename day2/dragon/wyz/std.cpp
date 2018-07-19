#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N=int(1e5)+5;

ll fast_mul(ll x,ll y,ll P){
	ll ret=0;
	assert(y>=0);
	// int sgn=y>=0?1:((y=-y),-1);
	while (y){
		if (y&1) ret=(ret+x)%P;
		x=(x+x)%P;
		y>>=1;
	}
	// ret*=sgn;
	return ret;
}

ll exgcd(ll a,ll b,ll &x,ll &y,ll P){
	if (!b){x=1;y=0;return a;}
	ll ret=exgcd(b,a%b,x,y,P);
	ll tmp=y;
	y=(-a/b*y+x)%P;
	x=tmp;
	return ret;
}

inline ll inv(ll num,ll p,ll b=1){
	ll x,y;
	// cerr<<num<<' '<<p<<' '<<b<<endl;
	ll d=exgcd(num,p,x,y,p);
	if (b%d!=0) return -1;
	if (x<0) x+=p;
	// cerr<<x<<endl;
	return fast_mul(b/d,x,p);
}

ll CRT(ll *a,ll *p,int n,ll P){
	ll ret=0;
	for(int i=1;i<=n;i++){
		// assert(p[i]!=0);
		ll M=P/p[i];
		assert(a[i]>=0);
		ret=(ret+fast_mul(fast_mul(M,inv(M%p[i],p[i]),P),a[i],P))%P;
	}
	assert(ret>=0);
	// if (ret<0) ret+=P;
	return ret;
}

int n;
ll b[N],p[N],a[N];
multiset<ll> att;

ll a0[N],p0[N];

inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

ll divisor[N],res[N][41];
int cnt[N],m;

bool setRes(int x,int y,ll val){
	// cerr<<x<<' '<<y<<' '<<val<<endl;
	if (res[x][y]==-1) res[x][y]=val;
	else{
		if (res[x][y]!=val){
			cerr<<x<<' '<<y<<' '<<res[x][y]<<' '<<val<<endl;
		}
		return res[x][y]==val;
	}
	return 1;
}

ll work(){
	// cerr<<"qvq"<<endl;
	ll ret=0,tmp;
	for (int i=1;i<=n;++i){
		auto it=att.upper_bound(b[i]);
		if (it!=att.begin()) --it;
		tmp=*it;
		att.erase(it);
		att.insert(a[i]);
		a[i]=tmp;
		if (b[i]>p[i])
			ret=max(ret,(b[i]-1)/a[i]+1);
		else{
			// cerr<<a[i]<<"x="<<b[i]<<"(mod "<<p[i]<<")"<<endl;
			
			// cerr<<b[i]<<endl;
		}
	}
	if (ret) return ret;
	
	ll P=1;
	for (int i=1;i<=n;++i)
		P=P/gcd(P,p[i])*p[i];
	
	tmp=P;
	m=0;
	for (ll d=2;tmp>1;++d)if (tmp%d==0||d*d>tmp){
		if (d*d>tmp) d=tmp;
		divisor[++m]=d;
		cnt[m]=0;
		p0[m]=1;
		for (cnt[m]=0;tmp%d==0;++cnt[m]) tmp/=d,p0[m]*=d;
	}
	// for (int j=1;j<=m;++j) cerr<<p0[j]<<' '<<a0[j]<<endl;
	// cerr<<'q'<<endl;
	
	memset(res,-1,sizeof(res));
	// cerr<<divisor[1]<<endl;
	for (int i=1;i<=n;++i){
		tmp=p[i];
		for (int j=1;j<=m;++j){
			ll _p=1,d=divisor[j];
			int k=0;
			for (;tmp%d==0;){
				_p*=d;
				tmp/=d;
				++k;
			}
			while (a[i]%d==0&&b[i]%d==0&&_p>1){
				a[i]/=d;
				b[i]/=d;
				_p/=d;
				--k;
			}
			if (!k) continue;
			// if (j==1&&k==3) cerr<<a[i]<<"x="<<b[i]<<"(mod "<<p[i]<<")"<<endl;
			if (a[i]%_p==0){
				if (b[i]%_p!=0) return -1;
				continue;
			}
			ll _inv=inv(a[i]%_p,_p,b[i]%_p);
			if (_inv==-1){
				// cerr<<a[i]<<"x="<<b[i]<<"(mod "<<p[i]<<")"<<endl;
				cerr<<"Inv does not exist!"<<endl;
				return -1;
			}
			if (!setRes(j,k,_inv)) return -1;
		}
	}
	// cerr<<"qwq"<<endl;
	for (int j=1;j<=m;++j){
		ll _p=p0[j];
		for (int k=cnt[j]-1;k>=0;--k){
			_p/=divisor[j];
			if (res[j][k+1]==-1) continue;
			if (!setRes(j,k,res[j][k+1]%_p)) return -1;
		}
		// cerr<<p0[j]<<' '<<a0[j]<<endl;
		while (res[j][cnt[j]]==-1&&p0[j]>1){
			--cnt[j];
			P/=divisor[j];
			p0[j]/=divisor[j];
		}
		if (cnt[j]==0) res[j][cnt[j]]=0;
		a0[j]=res[j][cnt[j]];
		// cerr<<p0[j]<<' '<<a0[j]<<endl;
	}
	// cerr<<"crt"<<endl;
	
	ret=CRT(a0,p0,m,P);
	
	ret%=P;
	if (ret<=0) ret+=P;
	return ret;
}

int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		int m;
		scanf("%d%d",&n,&m);
		att.clear();
		for (int i=1;i<=n;++i) scanf("%lld",&b[i]);
		for (int i=1;i<=n;++i) scanf("%lld",&p[i]);
		for (int i=1;i<=n;++i) scanf("%lld",&a[i]);
		while (m--){
			ll tmp;
			scanf("%lld",&tmp);
			att.insert(tmp);
		}
		printf("%lld\n",work());
	}
	return 0;
}
