#include <bits/stdc++.h>
using namespace std;
namespace banban {
	const int MAX_N = 100010;
	const int MAX_M = 200010;
	typedef long long ll;
	int N, M;

	struct Chain {
		int x, y; ll v, w;
		bool operator < (const Chain& C) const {
			if(w != C.w) return w > C.w;
			return make_pair(x, y) < make_pair(C.x, C.y);
		}
	};

	int fa[MAX_N], dep[MAX_N], cnt[MAX_N], cho[MAX_N], top[MAX_N];
	ll sum[MAX_N], fval[MAX_N];
	int lca(int x, int y) {
		while(top[x] != top[y])
			dep[top[x]] > dep[top[y]]
				? x = fa[top[x]] : y = fa[top[y]];
		return dep[x] < dep[y] ? x : y;
	}
	ll dis(int x, int y) {return sum[x] + sum[y] - 2 * sum[lca(x, y)];}

	vector<Chain> add[MAX_N], del[MAX_N];
	multiset<Chain> T[MAX_N];
	void merge(multiset<Chain>& a, multiset<Chain>& b) {
		if(a.size() < b.size()) a.swap(b);
		for(auto x : b) a.insert(x);
	}

	void __main__() {
		int X;
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout.tie(0);
		std::cin >> X;
		while(X--) {
			std::cin >> N;
			memset(cnt + 1, 0, N << 2);
			for(int i = 1; i < N; ++i) {
				int x, y; ll v;
				cin >> x >> y >> v;
				fa[y] = x;
				fval[y] = v;
				dep[y] = dep[x] + 1;
				sum[y] = sum[x] + v;
			}
			for(int i = N; i > 1; --i) {
				cnt[fa[i]] += ++cnt[i];
				if(cnt[cho[fa[i]]] < cnt[i]) cho[fa[i]] = i;
			}
			for(int i = 1; i <= N; ++i) top[i] = (i == cho[fa[i]]) ? top[fa[i]] : i;
			cin >> M;
			for(int i = 1; i <= M; ++i) {
				int x, y; ll v; 
				cin >> x >> y >> v;
				int z = lca(x, y);
				Chain C = {x, y, 2 * -v + dis(x, y), -v + dis(x, y)};
				add[x].push_back(C);
				add[y].push_back(C);
				del[z].push_back(C);
				del[z].push_back(C);
			}
			ll ans = -1e18;
			for(int i = N; i >= 1; --i) {
				for(auto x : add[i]) T[i].insert(x);
				for(auto x : del[i]) T[i].erase(T[i].lower_bound(x));
				static const int Lim = 15;
				static Chain C[Lim];
				int G = 0;
				for(auto x : T[i]) {
					C[G++] = x;
					if(G >= Lim) break;
				}
				for(int a = 0; a < G; ++a) for(int b = a + 1; b < G; ++b) 
					ans = max(ans, C[a].v + C[b].v + 
						min(dis(C[a].x, C[b].x) + dis(C[a].y, C[b].y),
							dis(C[a].x, C[b].y) + dis(C[a].y, C[b].x)));
				merge(T[fa[i]], T[i]);
				add[i].clear();
				del[i].clear();
				T[i].clear();
			}
			ans /= 2;
			if(ans >= -1e17) std::cout << ans << '\n';
			else std::cout << "F\n";
			
		}
	}
}
int main() {
	banban::__main__();
}
