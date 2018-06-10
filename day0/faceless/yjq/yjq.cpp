#include <bits/stdc++.h>

#define MOD 998244353

using namespace std ;

int n ; 

inline int qpow(int a, int b) { 
		int tmp = 1 ;
		for (; b; b >>= 1, a = 1LL * a * a % MOD) if (b & 1) tmp = 1LL * tmp * a % MOD ; 
		return tmp ;
}
const int MAXN = 210 ; 

int T[MAXN], dp[MAXN][MAXN] ;

vector<int> g ;

int f[MAXN], h[MAXN] ;

int Iv[MAXN] ; 
int main() { 
		scanf("%d", &n) ;  

		for (int i = 1; i <= n; i ++) scanf("%d", &T[i]) , dp[i][0] = 1 ; 

		int Q = 0 ; 
		
		scanf("%d", &Q) ; 
		for (int i = 1; i <= 200; i ++) Iv[i] = qpow(i, MOD - 2) ; 
		while ( Q --) { 
				int typ ; 
				scanf("%d", &typ) ; 
				if (typ == 0) { 
						int x, u, v  ;
						scanf("%d%d%d", &x, &u, &v) ; 
						int p = 1LL * u * qpow(v, MOD - 2) % MOD ; 

						for (int i = T[x] - 1; ~i; i --) {
							   dp[x][i + 1] += 1LL * dp[x][i] * p % MOD; 
							   if (dp[x][i + 1] >= MOD) dp[x][i + 1] -= MOD ; 
							   dp[x][i] = 1LL * dp[x][i] * (1 - p + MOD) % MOD ; 
						} 
				}
				else { 
					g.clear() ; 
					int k ; 
					scanf("%d", &k) ;
					for (int i = 0; i < k; i ++) {
							int x ; 
							scanf("%d", &x) ; 
							g.push_back(x) ; 			
					}
					memset(f, 0, sizeof f) ; 
					f[0] = 1 ; 
					for (int i = 0; i < k; i ++) { 
							int p = (1 - dp[g[i]][T[g[i]]] + MOD) % MOD ; 
							for (int j = i; ~j; j --) { 
									
									f[j + 1] += 1LL * f[j] * p % MOD ; 
									if (f[j + 1] >= MOD) f[j + 1] -= MOD; 
									f[j] = 1LL * f[j] * (1 - p + MOD) % MOD ; 
							}
					}

					for (int i = 0; i < k; i ++) { 
							// inv calc
							memset(h, 0, sizeof h) ; 
							int p = (1 - dp[g[i]][T[g[i]]] + MOD)% MOD, inv = qpow(p, MOD - 2), ans = 0 ; 
							if (p != 0) {
									for (int j = k - 1; ~j; j --) { 
											h[j] = 1LL * (1LL * f[j + 1] - 1LL * h[j + 1] * (1 - p + MOD) % MOD + MOD) * inv % MOD ; 
									}
									for (int j = 0; j < k; j ++) { 
											ans += 1LL * Iv[j + 1] * p % MOD * h[j] % MOD ;
										    if (ans >= MOD) ans -= MOD ; 
									}	
							}
							printf("%d%c", ans, ((i == k - 1) ? 10 : ' ')) ; 
					}
				}
		}
		for (int i = 1; i <= n; i ++) { 
				int ans = 0 ;
				for (int j = 0; j < T[i] ; j ++) { 
						ans += 1LL * dp[i][j] * (T[i] - j) % MOD ; 
						if (ans >= MOD) ans -= MOD ;
				}
				printf("%d%c", ans, (i == n ? 10 : ' ')) ; 
		}

}

						
		

