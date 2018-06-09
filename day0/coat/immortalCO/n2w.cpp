#include <bits/stdc++.h>
using namespace std;

const int mod = 64123;
const long long mod2 = 1ll * mod * mod;

int n, w, K, v, a[2777], f[2777][2777];
vector<int> e[2777];
bool vis[2777];
int ans, tmp[2777];

int dfs(int i) {
	vis[i] = 1;
	int cnt = 1;
	memset(f[i], 0, (n + 1) << 2);
	f[i][a[i] >= v] = 1;
	for(int k : e[i]) if(!vis[k]) {
		int tnc = dfs(k);
		(++f[k][0]) %= mod;
		static long long tmp[2777];
		memset(tmp, 0, (cnt + tnc + 1) << 3);
		int *f_i = f[i], *f_k = f[k];
		long long f_i_a;
		for(int a = 0; a <= cnt; ++a) if((f_i_a = f_i[a]))
			for(int b = 0; b <= tnc; ++b) {
				(tmp[a + b] += f_i_a * f[k][b]) >= mod2 ? tmp[a + b] -= mod2 : 0;
			}
		cnt += tnc;
		for(int a = 0; a <= cnt; ++a) f_i[a] = tmp[a] % mod;
	}
	for(int a = K; a <= cnt; ++a) (ans += f[i][a]) %= mod;
	for(int a = 0; a <= cnt; ++a) (tmp[a] += f[i][a]) %= mod; 
///*bgg*/printf("f[%d] = ", i); for(int k=0;k<=cnt;++k) printf("%d ",f[i][k]);puts("");
	vis[i] = 0;
	return cnt;
}



int main() {
	cin >> n >> K >> w; 
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i < n; ++i) {
		int x, y; cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(v = 1; v <= w; ++v) {
		dfs(1);
	}
	cout << ans << endl;
///*lgg*/printf("ans = ");for(int i=0;i<=n;++i) printf("%d ",tmp[i]);puts("");
}

#if 0
10 2 3
2 1 1 3 1 2 3 3 1 3
1 2
2 3
2 4
2 5
2 6
5 7
1 8
8 9
1 10
#endif
