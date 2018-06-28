#include <bits/stdc++.h>
using namespace std;
namespace banban {
	const int MAX_N = 100010;
	const int MAX_M = 200010;
	typedef long long ll;
	int N, M;

	pair<pair<int, int>, ll> q[MAX_M];
	ll qlca[MAX_M];

	int fa[MAX_N], dep[MAX_N], cnt[MAX_N], cho[MAX_N], top[MAX_N];
	ll sum[MAX_N], fval[MAX_N];
	int lca(int x, int y) {
		while(top[x] != top[y])
			dep[top[x]] > dep[top[y]]
				? x = fa[top[x]] : y = fa[top[y]];
		return dep[x] < dep[y] ? x : y;
	}

	int qcnt[MAX_N]; ll qsum[MAX_N];
	ll dis(int x, int y, int z = 0) {
		if(!z) z = lca(x, y);
		return sum[x] + sum[y] - 2 * sum[lca(x, y)];
	}
	ll qval(int x, int y, int z = 0) {
		if(!z) z = lca(x, y);
		if(qcnt[x] + qcnt[y] - 2 * qcnt[z] == 0) return 1e18;
		return qsum[x] + qsum[y] - 2 * qsum[z];
	}
	pair<ll, int> work(int C) {
		memset(qcnt + 1, 0, N << 2);
		memset(qsum + 1, 0, N << 3);
		int x = q[C].first.first, y = q[C].first.second;
		while(x != y) {
			if(dep[x] < dep[y]) swap(x, y);
			qcnt[x] = 1; qsum[x] = fval[x]; x = fa[x];
		}
		for(int i = 1; i <= N; ++i) {
			qcnt[i] += qcnt[fa[i]];
			qsum[i] += qsum[fa[i]];
		}
		pair<ll, int> ans = {(ll) -1e16, -1};
		ll mov = -q[C].second + dis(q[C].first.first, q[C].first.second, qlca[C]);
		for(int i = 1; i <= M; ++i) if(i != C) {
			ll tmp = mov + -q[i].second + dis(q[i].first.first, q[i].first.second, qlca[i])
				- qval(q[i].first.first, q[i].first.second, qlca[i]);
			ans = max(ans, {tmp, i});
		}
		return ans;
	}
	
	bool cmp(int a, int b) {
		return 	-q[a].second + dis(q[a].first.first, q[a].first.second, qlca[a])
		>		-q[b].second + dis(q[b].first.first, q[b].first.second, qlca[b]);
	}

	void __main__() {
		int T;
		assert(std::cin >> T);
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout.tie(0);
		bool type1 = 1, type2 = 1;
		int sumN = 0, sumM = 0, maxN = 0, maxM = 0;
		while(T--) {
			std::cin >> N;
			assert(1 <= N);
			sumN += N;
			maxN = max(maxN, N);
			memset(cnt + 1, 0, N << 2);
			for(int i = 1; i < N; ++i) {
				int x, y; ll v;
				assert(cin >> x >> y >> v);
				assert(1 <= x && x <= N);
				assert(1 <= y && y <= N);
				assert(y == i + 1);
				assert(x <= i);
				assert(v <= 1000000000);
				fa[y] = x;
				fval[y] = v;
				dep[y] = dep[x] + 1;
				sum[y] = sum[x] + v;
				srand(rand() + x + y + v);
			}
			for(int i = N; i > 1; --i) {
				cnt[fa[i]] += ++cnt[i];
				if(cnt[cho[fa[i]]] < cnt[i]) cho[fa[i]] = i;
			}
			for(int i = 1; i <= N; ++i) top[i] = (i == cho[fa[i]]) ? top[fa[i]] : i;
			cin >> M;
			assert(1 <= M);
			sumM += M;
			maxM = max(maxM, M);
			set<int> fuck;
			for(int i = 1; i <= M; ++i) {
				int x, y; ll v; 
				assert(cin >> x >> y >> v);
				assert(1 <= x && x <= N);
				assert(1 <= y && y <= N);
				assert(v <= 10000000000ll * N);
				q[i] = {{x, y}, v};
				qlca[i] = lca(x, y);
				srand(rand() + x + y + v);
				fuck.insert(lca(x, y));
			}
			type1 = type1 && ((int) fuck.size() == M);
			type2 = type2 && ((int) fuck.size() == 1 && *fuck.begin() == 1);
		}
		printf("OK %d %d %d %d %d %d\n", maxN, maxM, sumN, sumM, type1, type2);
	}
}
int main() {
	banban::__main__();
}
