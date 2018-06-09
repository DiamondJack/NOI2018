#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define bin(x) (1 << (x))
#define fi first
#define se second
#define mp(x, y) {x, y}
#define pb(x) push_back(x)
#define SZ(x) int((x).size())
//#define LX_JUDGE

using namespace std;
using ll = unsigned;
using Vi = vector<int>;
struct pii{int fi, se;};

template<typename T> inline bool upmax(T &x, T y) { return x < y ? x = y, 1 : 0; }
template<typename T> inline void upmin(T &x, T y) { return x > y ? x = y, 1 : 0; }

namespace MATH_CAL {
     const int mod = 64123;
     constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
     constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
     constexpr int mul(int a, int b) { return (ll) a * b % mod; }
     inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
     inline int mod_inv(int x) { return qpow(x, mod - 2); }
} using namespace MATH_CAL;

const int MAX_S = 2e8; // FIX ME !!!
const int MAX_N = 3e3 + 10, MAX_M = 5e5 + 10; // FIX ME !!!

vector<int> adj[MAX_N];
void addEdge(int x, int y) { adj[x].pb(y); adj[y].pb(x); }

int N, K;

int __mem_pool[MAX_S], *__mem_pt = __mem_pool;
int *__del_pool[MAX_M], **__del_pt = __del_pool;

inline int* new_int_arr() {
	int *u;
	if (__del_pt == __del_pool) {
		u = __mem_pt; __mem_pt += N;
	} else {
		u = *(--__del_pt);
	}
	return u;
}

struct Poly {
	int *a;
	inline int& operator [](const int x) { return a[x]; }
	inline void create(int f = 0) { 
		a = new_int_arr(); 
		if (f > 0) rep (i, 0, N) a[i] = f;
		if (f == 0) memset(a, 0, N << 2);
		if (f < 0) rep (i, 0, N) a[i] = i;
	}
	inline void create(Poly &b) {
		a = new_int_arr();
		memcpy(a, b.a, N << 2);
	}
	inline bool real() { return a != NULL; }
	inline void del() { *(__del_pt++) = a; a = NULL; }
};

Poly E, Z;

struct node {
	bool marked;
	node *ls, *rs;
	Poly tr[2][3];
	inline void clear() {
		rep (i, 0, 2) rep (j, 0, 3) {
			if (tr[i][j].real()) {
				if (i == j) memcpy(tr[i][j].a, E.a, N << 2);
				else tr[i][j].del();
			}
		}
		marked = 0;
	}
	inline void remove() {
		rep (i, 0, 2) rep (j, 0, 3) {
			if (tr[i][j].real()) {
				tr[i][j].del();
			}
		}
	}
	inline bool end() {	return ls == NULL; }
};

node __mem_node[MAX_M], *__mem_nd = __mem_node;
inline node* newnode() { 
	node *o = __mem_nd++;
	o->tr[0][0].create(1); o->tr[1][1].create(1);
	return o;
}

Poly tp[2][3];
bool tflag[2][3];

void test_and_set(int i, int j) {
	if (tflag[i][j] == false) {
		tflag[i][j] = true;
		memset(tp[i][j].a, 0, N << 2);
	}
}

inline void add(Poly &a, Poly &b) {
	if (!a.real()) a.create();
	if (!b.real()) return ;
	rep (i, 0, N) a[i] = add(a[i], b[i]); 
}

inline void mul(Poly &a, Poly &b) {
	if (!a.real()) a.create();
	if (!b.real()) { memset(a.a, 0, N << 2); return ; }
	rep (i, 0, N) a[i] = mul(a[i], b[i]); 
}

inline void add_prod(Poly &w, Poly &u, Poly &v) { 
	if (!w.real()) w.create();
	if (!u.real() or !v.real()) return ;
	rep (i, 0, N) w[i] = add(w[i], mul(u[i], v[i])); 
}

void mul_matrix(node *a, node *b) {
	memset(tflag, 0, sizeof tflag);
	rep (k, 0, 3) {
		rep (i, 0, 2) if (b->tr[i][k].real()) rep (j, 0, 3) {
			if (k == 2) {
				if (j == 2) {
					test_and_set(i, j);
					add(tp[i][j], b->tr[i][k]);
				}
			} else if (a->tr[k][j].real()) {
				test_and_set(i, j);
				add_prod(tp[i][j], b->tr[i][k], a->tr[k][j]);
			}
		}
	}
	rep (i, 0, 2) rep (j, 0, 3) {
		if (tflag[i][j]) {
			if (a->tr[i][j].real()) {
				memcpy(a->tr[i][j].a, tp[i][j].a, N << 2);
			} else {
				a->tr[i][j].create(tp[i][j]);
			}
		} else if (a->tr[i][j].real()) {
			a->tr[i][j].del();
		}
	}
}

inline void push_down(node *o) { 
	if (!o->marked) return ;
//	puts("PD");
	node *&l = o->ls, *&r = o->rs;
	if (!l) {
		l = newnode();
		r = newnode();
	}
	mul_matrix(l, o); l->marked = 1;
	mul_matrix(r, o); r->marked = 1;
	o->clear();
}

int val[MAX_N], vp[MAX_N];

node *root[MAX_N];

node* make_tree(int l, int r, int v) {
	node *o = newnode();
	if (l > v) {
		o->marked = 1;
		o->tr[0][2].create(1);
	} else if (r <= v) {
		o->marked = 1;
		o->tr[0][2].create(-1);
	} else {
		int m = (l + r) / 2;
		o->ls = make_tree(l, m, v);
		o->rs = make_tree(m + 1, r, v);
	}
	return o;
}

node* merge_tree(int l, int r, node *u, node *v) {
	if (u->end()) swap(u, v);
	if (v->end()) {
		rep (i, 0, 3) mul(u->tr[0][i], v->tr[0][2]);
		add(u->tr[1][2], v->tr[1][2]);
		u->marked = 1;
		v->remove();
	} else {
		push_down(u);
		push_down(v);
		int m = (l + r) / 2;
		u->ls = merge_tree(l, m, u->ls, v->ls);
		u->rs = merge_tree(m + 1, r, u->rs, v->rs);
		v->remove();
	}
	return u;
}

inline void Print(int a[]) { rep (i, 0, N) printf("%d%c", a[i], " \n"[i == N - 1]); }

void dfs(int x, int fa) {
//	printf("%d in\n", x);
	root[x] = make_tree(1, K, val[x]);
	for (int y : adj[x]) {
		if (y == fa) continue ;
		dfs(y, x); 
		root[x] = merge_tree(1, K, root[x], root[y]);
	}
	rep (i, 0, 3) add(root[x]->tr[1][i], root[x]->tr[0][i]);
	add(root[x]->tr[0][2], E);
	root[x]->marked = 1;
//	printf("%d out\n", x);
}

void init() {
	E.create(1); Z.create(-1);
	rep (i, 0, 2) rep (j, 0, 3) tp[i][j].create();
}

int ans[MAX_N]; 
void travel(node *o, int l, int r) {
//	printf("%d %d\n", l, r);
	if (l == r) {
		int *u = o->tr[1][2].a, v = vp[l] - vp[l - 1];
		if (u != NULL) {
			rep (i, 0, N) ans[i] = add(ans[i], mul(u[i], v));
		}
		return ;
	}
	push_down(o);
	int m = (l + r) / 2;
	travel(o->ls, l, m);
	travel(o->rs, m + 1, r);
}

int fac[MAX_N];
int pre[MAX_N][MAX_N], suf[MAX_N][MAX_N];

inline int interpolation(int r[], int k) {
	static bool inited = false;
	int res = 0;
	if (!inited) {
		inited = true;
		fac[0] = 1;
		rep (i, 1, N) fac[i] = mul(fac[i - 1], i);
		pre[0][0] = 1;
		rep (i, 1, N) {
			pre[i][0] = mul(pre[i - 1][0], mod - i + 1);
			rep (j, 1, i + 1) {
				pre[i][j] = sub(pre[i - 1][j - 1], mul(pre[i - 1][j], i - 1));
			}
		}
		rep (i, 0, N) down (j, i, 0) pre[i][j] = add(pre[i][j + 1], pre[i][j]);
		suf[N][0] = 1;
		down (i, N, 1) {
			suf[i][0] = mul(suf[i + 1][0], mod - i);
			rep (j, 1, N - i + 1) {
				suf[i][j] = sub(suf[i + 1][j - 1], mul(suf[i + 1][j], i));
			}
		}
	}
	rep (i, 0, N) {
		int t = 0;
		rep (j, 0, N - i) t = add(t, mul(pre[i][max(k - j, 0)], suf[i + 1][j]));
		t = mul(t, mod_inv(mul(fac[i], fac[N - i - 1])));
		(N - i - 1) & 1 ? (t = mod - t) : 0;
		res = add(res, mul(t, ans[i]));
	}
	return res;
}

int main() {
#ifdef LX_JUDGE
     freopen(".in", "r", stdin);
#endif
     ios::sync_with_stdio(false);
	 int P, w;
	 cin >> N >> P >> w;
	 rep (i, 1, N + 1) { cin >> val[i]; vp[i] = val[i]; }
	 sort(vp + 1, vp + N + 1);
	 K = unique(vp + 1, vp + N + 1) - vp - 1;
	 rep (i, 1, N + 1) val[i] = lower_bound(vp + 1, vp + K + 1, val[i]) - vp;
	 rep (i, 1, N) {
		 int x, y;
		 cin >> x >> y;
		 addEdge(x, y);
	 }
	 N += 1; init();
	 dfs(1, 0);
	 travel(root[1], 1, K);
	 int res = interpolation(ans, P);
	 cout << res << endl;
     return 0;
}
