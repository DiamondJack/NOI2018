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

	const int MAX_N = 4096 + 1;
	const int mod = 998244353;
	const int G = 3;
	
	using ll = long long;
	
	constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	constexpr int mul(int a, int b) { return (ll) a * b % mod; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
	
	class BGG_NTT_WORKER {
	private :
		static const int MAX_N = __board_lovable__::MAX_N;
		int init_n;
		int w[2][2 * MAX_N];
		void fft(int a[], int n, int w[]) {
			init(n);
			for (int i = 0, j = 0; i < n; ++i) {
				if (i < j) std::swap(a[i], a[j]);
				for (int l = n / 2; (j ^= l) < l; l /= 2);
			}
			int *r = w + 1;
			for (int i = 2, m = 1; i <= n; r += m, m = i, i *= 2) {
				for (int j = 0; j < n; j += i) 
				{
					int *a_j_m = a + j + m, *a_j = a + j, t;
					for (int k = 0; k < m; ++k) {
						t 			= mul(a_j_m[k], r[k]);
						a_j_m[k] 	= sub(a_j[k], t);
						a_j[k] 		= add(a_j[k], t);
					}
				}
			}
		}
		void init(int n) {
			if(n <= init_n) return; init_n = n;
			int a = qpow(G, (mod - 1) / n), b = mod_inv(a), h = n >> 1;
			w[0][h] = 1; w[1][h] = 1;
			rep (i, h + 1, n) {
				w[0][i] = mul(w[0][i - 1], a);
				w[1][i] = mul(w[1][i - 1], b);
			}
			dow (i, h, 1) {
				w[0][i] = w[0][i << 1];
				w[1][i] = w[1][i << 1];
			}
		}
	public :
		void dft(int a[], int n) {
			fft(a, n, w[0]);
		}
		void idft(int a[], int n) {
			fft(a, n, w[1]);
			int r = mod_inv(n);
			rep (i, 0, n) a[i] = mul(a[i], r);
		}
	}	bgg;
	
	int T, W, val[MAX_N];
	vector<int> adj[MAX_N];

	using Poly = int[MAX_N];	
	#define pol(n) (1 << (32 - __builtin_clz(n)))
	Poly pre_1, pre_x;
	
	void print_poly(int *a, const char *s) {
		bgg.idft(a, T);
		printf("%s = ", s); for(int i = 0; i < T; ++i) printf("%d ", a[i]); puts("");
		bgg.dft(a, T);
	}
	
	struct Node {
		Poly a, b, c, d, e;
		inline void print() {
			// print_poly(a, "a");
			print_poly(b, "\tb");
			// print_poly(c, "c");
			// print_poly(d, "d");
			print_poly(e, "\te");
		}
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

	void print(const Node *p, int l, int r, Node data = init) {	
		if(p) { Node tmp = *p; tmp += data; data = tmp; }
		if(l == r) {
			printf("pos %d\n", l);
			data.print();
			return;
		}
		int m = (l + r) >> 1;
		print(p ? p->l : 0, l, m, data);
		print(p ? p->r : 0, m + 1, r, data);
	}

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
		T = pol(n + 1);
		pre_1[0] = 1; pre_x[1] = 1; bgg.dft(pre_1, T); bgg.dft(pre_x, T);
		
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
		bgg.idft(ans, T);
		int o = 0;
		for(int i = k; i <= n; ++i) o = add(o, ans[i]);
		cout << o << endl;
///*bgg*/printf("ans = ");for(int i = 0; i <= n; ++i) printf("%d ",ans[i]);puts("");
	}
}

int main() {
	__board_lovable__::__main__();
}
