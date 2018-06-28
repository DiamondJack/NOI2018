#include <bits/stdc++.h>
const int MAX_N = 100010;
const long long mov = 10000000000000000ll;
const long long inf = 1000000000000000000ll;
std::vector<std::pair<int, int>> e[MAX_N], E[MAX_N];
std::pair<int, int> cha[MAX_N];
bool vis[MAX_N], vis_cur;
long long ans, cur, base, val[MAX_N];
bool fillpath(int p, int fa, int t) {
	if(p == t) return vis[p] = 1;
	for(auto &k : e[p]) if(k.first != fa && fillpath(k.first, p, t))
		{base += k.second; k.second = -1;  return vis[p] = 1;}
	return 0;
}
bool checkpath(int p, int fa, int t) {
	// printf("cp p = %d t = %d\n",p,t);
	if(p == t) return 1;
	for(auto k : e[p]) if(k.first != fa && checkpath(k.first, p, t)) 
		{cur += std::max(k.second, 0); vis_cur |= (k.second == -1); return 1;}
	return 0;
}
int main() {
	int T; std::cin >> T;
	while(T--) {
		int N, M; std::cin >> N;
		for(int i = 1; i <= N; ++i) E[i].clear();
		for(int i = 1; i < N; ++i) {
			int x, y, v; std::cin >> x >> y >> v;
			E[x].push_back({y, v});
			E[y].push_back({x, v});
		}
		std::cin >> M;
		ans = -inf;
		for(int i = 1; i <= M; ++i) {
			int x, y; std::cin >> x >> y >> val[i];
			val[i] = mov - val[i];
			cha[i] = {x, y};
			for(int j = 1; j <= N; ++j) {vis[j] = 0; e[j] = E[j];}
			fillpath(x, 0, y);
			base = 0;
			fillpath(y, 0, x);
			base += val[i];
			for(int j = 1; j < i; ++j) {
				cur = 0; vis_cur = 0;
				checkpath(cha[j].first, 0, cha[j].second);
			//printf("base = %lld\n", base);
				//printf("%d ~ %d %lld\n", i, j, cur + base + val[j] - 2 * mov);
				if(vis_cur) ans = std::max(ans, cur + base + val[j]);
			}
		}
		if(ans <= -inf) std::cout << "F" << std::endl;
		else std::cout << ans - mov * 2 << std::endl;
	}
}

#if 0
1
10
1 2 4
2 3 10
3 4 2
4 5 7
4 6 2
2 7 2
5 8 4
6 9 1
5 10 3
10
4 2 1
10 7 9
4 6 2
6 9 8
10 3 0
8 4 8
6 4 2
7 9 1
6 2 0
2 4 9

#endif