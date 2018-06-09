#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define cmax(a, b) ((a) < (b) ? (a) = (b) : 0)
#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define dow(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define bin(x) (1 << (x))

namespace __board_lovable__ {

	using ll = unsigned;
	const int MAX_N = 1677;
	const int POL_N = 1 << (32 - __builtin_clz(MAX_N));
	const int mod = 64123;
	const ll mod2 = (ll) mod * mod;	
	
	constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	constexpr int mul(int a, int b) { return (ll) a * b % mod; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
	
	int T, W, val[MAX_N];
	vector<int> adj[MAX_N];
	
	using Poly = int[MAX_N];	
	Poly pre_1, pre_x;
	
	inline void eval(Poly p) {
		static Poly q;
		int n = T;
		while(n && !p[n - 1]) --n;
		for(int x = 0; x < T; ++x) {
			ll y = 0, v = 1;
			for(int k = 0; k < n; ++k) {
				(y += v * p[k]) >= mod2 ? y -= mod2 : 0;
				v = v * x % mod;
			}
			q[x] = y % mod;
		}
		memcpy(p, q, T << 2);
	}
	
	const int *ival; long long ipol[MAX_N];
	struct PolyStruct {
		Poly p; int n;
		void mul(const PolyStruct &_1, const PolyStruct &_2) {
			if(_1.n > _2.n) return mul(_2, _1);
			static long long tmp[MAX_N];
			n = _1.n + _2.n - 1;
			memset(tmp, 0, n << 3);
			const int *a = _1.p, *b = _2.p; ll a_i; long long *tmp_i;
			for(int i = 0; i < _1.n; ++i) if((a_i = a[i])) {
				tmp_i = tmp + i;
				for(int j = 0, _ = _2.n; j < _; ++j) {
					(tmp_i[j] += a_i * b[j]) >= mod2
						? tmp_i[j] -= mod2 : 0;
				}
			}
			for(int i = 0; i < n; ++i) p[i] = tmp[i] % mod;
		}
		inline int operator() (int x) const {
			long long y = 0; ll v = 1;
			for(int k = 0; k < n; ++k) {
				(y += v * p[k]) >= mod2 ? y -= mod2 : 0;
				v = v * x % mod;
			}
			return y % mod;
		}
	}	pro[POL_N << 1], poly_one;
	
	void prepare(int i, int l, int r) {
		if(l == r) {
			pro[i].n = 2;
			pro[i].p[0] = sub(0, l);
			pro[i].p[1] = 1;
			return;
		}
		int m = (l + r) >> 1;
		prepare(i << 1, l, m);
		prepare(i << 1 | 1, m + 1, r);
		pro[i].mul(pro[i << 1], pro[i << 1 | 1]);
	}
	void divide(int i, int l, int r, PolyStruct p) {
		if(l == r) {
			ll tmp = mul(ival[l], mod_inv(p(l)));
			for(int i = 0; i < T; ++i)
				(ipol[i] += tmp * p.p[i]) >= mod2 
					? ipol[i] -= mod2 : 0;
			return;
		}
		int m = (l + r) >> 1;
		PolyStruct q;
		q.mul(p, pro[i << 1 | 1]); divide(i << 1, l, m, q);
		q.mul(p, pro[i << 1]); divide(i << 1 | 1, m + 1, r, q);
	}
	inline void inter(Poly p) {
		memset(ipol, 0, T << 3);
		ival = p;
		poly_one.p[0] = poly_one.n = 1;
		prepare(1, 0, T - 1);
		divide(1, 0, T - 1, poly_one);
		for(int i = 0; i < T; ++i) p[i] = ipol[i] % mod;
	}
	
	struct Node {
		Poly a, b, c, d, e;
		inline void operator += (const Node& m) {
			int _a, _b, _c, _d, _e;
			for(int i = 0; i < T; ++i) {
				_a = ((ll) a[i] * m.a[i]) % mod;
				_b = ((ll) b[i] * m.a[i] + m.b[i]) % mod;
				_c = ((ll) a[i] * m.c[i] + (ll) c[i] * m.d[i]) % mod;
				_d = ((ll) d[i] * m.d[i]) % mod;
				_e = ((ll) b[i] * m.c[i] + (ll) e[i] * m.d[i] + m.e[i]) % mod;
				a[i] = _a; b[i] = _b; c[i] = _c; d[i] = _d; e[i] = _e;
			}
		}
		inline void down();
		Node *l, *r;
	}	init, plus_1, mul_x, sum_up;
	int ql, qr;

	inline void Node::down() {
		if(l) *l += *this; else { l = new Node(*this); l->l = l->r = 0; }
		if(r) *r += *this; else { r = new Node(*this); r->l = r->r = 0; }
		Node *_l = l, *_r = r; *this = init; l = _l; r = _r;
	}
	void merge(Node *&p, Node *q) {
///*bgg*/printf("merge %p(%p, %p) %p(%p, %p)\n", p,p->l,p->r,q,q->l,q->r);
		if(!q) return; if(!p) return void(p = q);
		if(!p->l && !p->r) std::swap(p, q);
		if(!q->l && !q->r) {
///*bgg*/printf("merge\n");
///*bgg*/printf("p = \n"); p->print(); printf("q = \n"); q->print();
			for(int i = 0; i < T; ++i) {
				p->a[i] = mul(p->a[i], q->b[i]);
				p->b[i] = mul(p->b[i], q->b[i]);
				p->e[i] = add(p->e[i], q->e[i]);
			}
			delete q;
			return;
		}
		p->down(); q->down();
		merge(p->l, q->l);
		merge(p->r, q->r);
		delete q;
	}
	void modify(Node* &p, int l, int r) {
		if(ql <= l && r <= qr) {
			if(p) *p += mul_x;
			else p = new Node(mul_x);
			return;
		}
		if(p) p->down();
		else p = new Node(init);
		int m = (l + r) >> 1;
		if(ql <= m) modify(p->l, l, m);
		if(m <  qr) modify(p->r, m + 1, r);
	}
	
	int cnt[MAX_N];
	bool vis[MAX_N];
	inline bool cmp(int a, int b) { return cnt[a] < cnt[b]; }
	void pre(int p) {
		cnt[p] = 1;
		vis[p] = 1;
		for(int k : adj[p]) if(!vis[k]) { pre(k); cnt[p] += cnt[k]; }
		sort(&*adj[p].begin(), &*adj[p].end(), cmp);
		vis[p] = 0;
	}
	
	Node* dfs(int p) {
		Node *T = new Node(plus_1);
		vis[p] = 1;
		for(int k : adj[p]) if(!vis[k]) {
			Node *P = dfs(k);
///*bgg*/printf("%d -> %d\n", p, k);
			*P += plus_1;
			merge(T, P);
		}
		ql = 1; qr = val[p];
		modify(T, 1, W);
		*T += sum_up;
		vis[p] = 0;
///*bgg*/printf("dfs done p = %d\n", p); print(T,1,W);
		return T;
	}
	
	int ans[MAX_N];
	
	void solve(Node *p, int l, int r) {
		if(!p) return;
		if(l == r) {
			for(int i = 0; i < T; ++i) ans[i] = add(ans[i], p->e[i]);
			return;
		}
		p->down();
		int m = (l + r) >> 1;
		solve(p->l, l, m);
		solve(p->r, m + 1, r);
	}

	void __main__() {
		ios::sync_with_stdio(0);
		cin.tie(0); cout.tie(0);
		
		int n, k; cin >> n >> k >> W;
		for(int i = 1; i <= n; ++i) cin >> val[i]; 
		for(int i = 1; i < n; ++i) {
			int x, y; cin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		T = n + 1;
		pre_1[0] = 1; pre_x[1] = 1; eval(pre_1); eval(pre_x);
		
		memcpy(init.a, pre_1, T << 2);
		memcpy(init.d, pre_1, T << 2);
		memcpy(plus_1.a, pre_1, T << 2);
		memcpy(plus_1.b, pre_1, T << 2);
		memcpy(plus_1.d, pre_1, T << 2);
		memcpy(mul_x.a, pre_x, T << 2);
		memcpy(mul_x.d, pre_1, T << 2);
		memcpy(sum_up.a, pre_1, T << 2);
		memcpy(sum_up.c, pre_1, T << 2);
		memcpy(sum_up.d, pre_1, T << 2);
		
		pre(1);
///*bgg*/puts("init done");
		solve(dfs(1), 1, W);
		inter(ans);
		int o = 0;
		for(int i = k; i <= n; ++i) o = add(o, ans[i]);
		cout << o << endl;
///*bgg*/printf("ans = ");for(int i = 0; i <= n; ++i) printf("%d ",ans[i]);puts("");
	}
}

int main() {
	__board_lovable__::__main__();
}
