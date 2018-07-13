#include <bits/stdc++.h>

namespace __main__ {

	using ll = long long;
	const ll inf = 1000000000000000000ll;
	const ll mov = 10000000000000000ll;
	const int MAX_N = 100010;
	template<class T> constexpr T dmax(T a, T b) {return a > b ? a : b;}
	template<class T> constexpr T dmin(T a, T b) {return a < b ? a : b;}
	template<class T> inline bool cmax(T& a, T b) {return a < b ? a = b, 1 : 0;}
	template<class T> inline bool cmin(T& a, T b) {return a > b ? a = b, 1 : 0;}

	int N;
	struct Edge{int to, len;};
	std::vector<Edge> adj[MAX_N];

	template<class T> void reinit(T& t) {t.~T(); new(&t) T;}
	ll ans, dis[MAX_N];

	inline void cans(ll v) {
		cmax(ans, v);
///*bgg*/printf("cans %lld\n", v); assert(v<=46);
	}

	namespace Tree {
		int fa[MAX_N], dep[MAX_N], top[MAX_N];
		int dfs_init(int i, int f) {
			fa[i] = f; top[i] = i;
			dep[i] = dep[f] + 1; 
			int cnt = 1, cho = 0, cho_cnt = 0;
			for(auto k : adj[i]) if(k.to != f) {
				dis[k.to] = dis[i] + k.len;
				int tmp = dfs_init(k.to, i);
				cnt += tmp;
				if(cmax(cho_cnt, tmp)) cho = k.to;
			}
			top[cho] = i;
			return cnt;
		}
		void dfs_make(int i, int f) {
			top[i] = top[top[i]];
			for(auto k : adj[i]) if(k.to != f)
				dfs_make(k.to, i);
		}
		inline void __init__() {dfs_init(1, 0); dfs_make(1, 0);}
	}
	int lca(int x, int y) {
		using namespace Tree;
		while(top[x] != top[y])
			dep[top[x]] > dep[top[y]]
				? x = fa[top[x]] : y = fa[top[y]];
		return dep[x] < dep[y] ? x : y;
	}

	struct Node
	{
		Node *l, *r;
		ll max0, max1;	
	}	mem[MAX_N * 44], *null, *tot, *P[MAX_N];

	int arg_p; ll arg_max0, arg_max1, arg_mov;
	Node* build(int l, int r) {
		Node *p = ++tot;
		p->max0 = arg_max0; p->max1 = arg_max1;
		if(l != r) {
			int m = (l + r) >> 1;
			if(arg_p <= m) {p->l = build(l, m); p->r = null;}
			else {p->l = null; p->r = build(m + 1, r);}
		}
		return p;
	}
	void merge(Node* &a, Node *b, int l, int r, ll lmax0, ll rmax1) {
		if(b == null) return;
		if(l == r || a == null) {
			if(a == null) a = b;
			else {cmax(a->max0, b->max0); cmax(a->max1, b->max1);}
///*bgg*/printf("merge [%d, %d] max = %lld %lld b = %lld %lld\n", l,r,lmax0,rmax1,b->max0,b->max1);
			cans(lmax0 + b->max1 - arg_mov);
			cans(b->max0 + rmax1 - arg_mov);
			return;
		}
		int m = (l + r) >> 1; ll m0 = a->l->max0, m1 = a->r->max1; 
		merge(a->l, b->l, l, m + 0, lmax0, dmax(rmax1, m1));
		merge(a->r, b->r, m + 1, r, dmax(lmax0, m0), rmax1);
		a->max0 = dmax(a->l->max0, a->r->max0);
		a->max1 = dmax(a->l->max1, a->r->max1);
///*bgg*/printf("pushup [%d, %d] max = %lld %lld\n",l,r,a->max0,a->max1 );
	}
	void remove(Node*& p, int l, int r) {
		if(p == null) return;
		if(l == r) p = null;
		else {
			int m = (l + r) >> 1;
			if(arg_p <= m) remove(p->l, l, m);
			else remove(p->r, m + 1, r);
			p->max0 = dmax(p->l->max0, p->r->max0);
			p->max1 = dmax(p->l->max1, p->r->max1);
		}
	}

	struct Info {
		ll ext; int pos;
		inline ll operator + (const Info& inf) const {
			return ext + inf.ext - (dis[lca(pos, inf.pos)] << 1);
		}
	}	pinf[MAX_N << 1];

	struct Data {
		int x, y; ll v;
		inline Data() : x(0), y(0), v(-inf) {}
		inline Data(const Data& D) : x(D.x), y(D.y), v(D.v) {}
		inline Data(int x, int y, ll v) : x(x), y(y), v(v) {}
		inline void operator += (const Data& D) {
			if(D.v < 0) return;
			if(v < 0) return void(*this = D);
///*bgg*/printf("merge %d~%d %d~%d\n",x,y,D.x,D.y);
			int X = x, Y = y; ll tmp;
			if(cmax(v, D.v)) {X = D.x; Y = D.y;}
			// tmp = pinf[x] + pinf[D.x]; cans((tmp - arg_mov) >> 1); if(cmax(v, tmp)) {X = x; Y = D.x;}
			// tmp = pinf[x] + pinf[D.y]; cans((tmp - arg_mov) >> 1); if(cmax(v, tmp)) {X = x; Y = D.y;}
			// tmp = pinf[y] + pinf[D.x]; cans((tmp - arg_mov) >> 1); if(cmax(v, tmp)) {X = y; Y = D.x;}
			// tmp = pinf[y] + pinf[D.y]; cans((tmp - arg_mov) >> 1); if(cmax(v, tmp)) {X = y; Y = D.y;}
			x = X; y = Y;
		}
	};

	std::unordered_map<int, Data> Q[MAX_N];

	void dfs_sol(int i, int fa) {
		for(auto k : adj[i]) if(k.to != fa) {
			dfs_sol(k.to, i);

///*bgg*/printf("mergesub %d <- %d\n",i,k.to);
			arg_p = Tree::dep[i];
			remove(P[k.to], 1, N);
			arg_mov = dis[i];
			merge(P[i], P[k.to], 1, N, -inf, -inf);

			//if(Q[k.to].size() > Q[i].size()) Q[i].swap(Q[k.to]);
			//arg_mov = dis[i] << 1;
			//for(auto c : Q[k.to]) Q[i][c.first] += c.second;
			//reinit(Q[k.to]);
			//Q[i].erase(i);
		}
///*bgg*/printf("dfs_sol ret i = %d\n", i);
	}

	void __main__() {
		int C; std::cin >> C; 
		null = mem;
		*null = {null, null, -inf, -inf};
		while(C--) {
			std::cin >> N;
			ans = -3 * inf;
			tot = mem;
			for(int i = 1; i <= N; ++i) {
				P[i] = null;
				reinit(adj[i]);
			}
			for(int i = 1; i < N; ++i) {
				int a, b, v;
				std::cin >> a >> b >> v;
				adj[a].push_back({b, v});
				adj[b].push_back({a, v});
			}
			Tree::__init__();
			int M; std::cin >> M;
			for(int i = 1; i <= M; ++i) {
				int x, y, z; ll v, w;
				std::cin >> x >> y >> v; 
				v = mov - v;
				w = v;
				z = lca(x, y);
				v += dis[x] + dis[y] - (dis[z] << 1);

///*bgg*/printf("chain[%d] %d ~ %d v = %lld\n", i, x, y, v);

				arg_p = Tree::dep[z];
				arg_max0 = v; arg_max1 = v + dis[z];
///*bgg*/printf("step1 arg_p = %d max = %lld %lld\n",arg_p,arg_max0,arg_max1);
				if(x != z) {arg_mov = dis[x]; merge(P[x], build(1, N), 1, N, -inf, -inf);}
				if(y != z) {arg_mov = dis[y]; merge(P[y], build(1, N), 1, N, -inf, -inf);}

				//v += w + dis[x] + dis[y];
///*bgg*/printf("step2 v = %lld\n",v);
				//int Px = i << 1, Py = i << 1 | 1;
				//pinf[Px] = {v, x}; pinf[Py] = {v, y};
				//if(x != z) {arg_mov = dis[x] << 1; Q[x][z] += Data(Py, Py, 0);}
				//if(y != z) {arg_mov = dis[y] << 1; Q[y][z] += Data(Px, Px, 0);}
///*bgg*/puts("");
			}
			dfs_sol(1, 0);
			reinit(Q[1]);
			if(ans <= -inf / 2) std::cout << "F" << std::endl;
			else std::cout << ans - mov * 2 << std::endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	__main__::__main__();
}