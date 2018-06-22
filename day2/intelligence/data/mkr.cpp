#include <bits/stdc++.h>
using namespace std;
namespace banban {
	const int MAX_N = 100010;
	const int MAX_M = 100010;
	typedef long long ll;
	int N, M; string S;

	pair<pair<int, int>, ll> q[MAX_M];
	ll qlca[MAX_M];

	union Convert {void* p; size_t v;};

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
		return 	q[a].second + dis(q[a].first.first, q[a].first.second, qlca[a])
		>		q[b].second + dis(q[b].first.first, q[b].first.second, qlca[b]);
	}

	void __main__() {
		cin >> N >> M >> S;
		srand(N + M + Convert{&S[0]}.v + time(0));
		stringstream tmp;
		tmp << "mkrtmp_";
		for(int i = 0; i < 20; ++i) tmp << rand() % 9;
		string raw = tmp.str();
		tmp.str("");
		tmp << "echo " << N << " " << M << " " << S << " | pypy treemkr.py > " << (raw + ".in");
		if(system(tmp.str().c_str())) {
			puts("treemkr error!");
			exit(-1);
		}
		assert(freopen((raw + ".in").c_str(), "r", stdin));
		int useless;
		cin >> useless;
		cin >> useless;
		printf("%d\n", N);
		for(int i = 1; i < N; ++i) {
			int x, y; ll v;
			cin >> x >> y >> v;
			assert(y == i + 1 and x < y);
			fa[y] = x;
			fval[y] = v;
			dep[y] = dep[x] + 1;
			sum[y] = sum[x] + v;
			printf("%d %d %lld\n", x, y, v);
			srand(rand() + x + y + v);
		}
		for(int i = N; i > 1; --i) {
			cnt[fa[i]] += ++cnt[i];
			if(cnt[cho[fa[i]]] < cnt[i]) cho[fa[i]] = i;
		}
		for(int i = 1; i <= N; ++i) top[i] = (i == cho[fa[i]]) ? top[fa[i]] : i;

		cin >> useless;
		#define randll() ((((long long) rand()) << 31) | rand())
		for(int i = 1; i <= M; ++i) {
			int x, y; ll v; 
			cin >> x >> y >> v;
			v += randll() % (3 * dis(x, y) + 1);
			q[i] = {{x, y}, v};
			qlca[i] = lca(x, y);
			srand(rand() + x + y + v);
			// printf("newval %lld\n",v);
		}
		ll ans = -1e18;
		// Find Answer
		for(int i = 1; i <= M; ++i) {
			fprintf(stderr, "Step 1/4 %d/%d\n", i, M);
			ans = max(ans, work(i).first);
			// printf("i = %d ans = %lld\n", i, ans);
		}
		// assert(ans >= -1e16);
		if(ans >= -1e16) {
			// Iteration
			for(int __t = 1; __t <= M / 10; ++__t) {
				fprintf(stderr, "Step 2/4 %d/%d\n", __t, M/10);
				int C = rand() % M + 1;
				for(int __ = 10; __--; ) {
					auto p = work(C);
					if(p.first != ans)
						q[C].second -= (ans - p.first - rand() % 1000000000);
					C = p.second;
				}
			}
			static int perm[MAX_N];
			// Greedy
			for(int i = 1; i <= M; ++i) perm[i] = i;
			sort(perm + 1, perm + M + 1, cmp);
			for(int i = 1; i <= M / 10; ++i) {
				fprintf(stderr, "Step 3/4 %d/%d\n", i, M/10);
				int C = perm[i];
				for(int __ = 10; __--; ) {
					auto p = work(C);
					if(p.first != ans)
						q[C].second -= (ans - p.first - rand() % 1000000);
					C = p.second;
				}
			}
			// Random
			random_shuffle(perm + 1, perm + M + 1);
			for(int i = 1; i <= M; ++i) {
				fprintf(stderr, "Step 4/4 %d/%d\n", i, M);
				int C = perm[i];
				auto p = work(C);
				if(p.first != ans)
					q[C].second -= (ans - p.first - rand() % 1000);
			}
			// for(int i = 1; i <= M; ++i) fprintf(stderr, "%lld\n", ans - work(i).first);
		}
		printf("%d\n", M);
		for(int i = 1; i <= M; ++i) printf("%d %d %lld\n", q[i].first.first, q[i].first.second, max(0ll, q[i].second));
		fprintf(stderr, "Done ans = %lld\n", ans);

		tmp.str("");
		tmp << "rm -rf " << raw << ".*";
		assert(!system(tmp.str().c_str()));

	}
}
int main() {
	banban::__main__();
}