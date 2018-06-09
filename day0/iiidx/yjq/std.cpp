#include <bits/stdc++.h>

using namespace std ;

int n ;

double k ; 

const int MAXN = 500010 ; 

int a[MAXN] ; 

int sf[MAXN] ; 

int fa[MAXN] ; 

int siz[MAXN] ; 
int now[MAXN] ; 

int ans[MAXN] ; 

int L[MAXN << 2], R[MAXN << 2], val[MAXN << 2], tag[MAXN << 2] ; 

void Build(int x, int l, int r) { 
		L[x] = l, R[x] = r; 
		if (l == r) {
				val[x] = l ; 
				tag[x] = 0 ;
				return ; 
		}
		int mid = (l + r) >> 1 ; 
		Build(x << 1, l, mid), Build(x << 1 | 1, mid + 1, r) ; 
		val[x] = l ; 
}

void pushdown(int x) { 
		if (!tag[x]) return ; 
		int tg = tag[x] ; tag[x] = 0 ; 
		tag[x << 1] += tg, val[x << 1] += tg, tag[x << 1 | 1] += tg, val[x << 1 | 1] += tg;  
}

void Modify(int x, int l, int r, int v) {
		if (L[x] == l && R[x] == r) {
				tag[x] += v, val[x] += v ;
				return ; 
		}
		pushdown(x) ; 
		int mid = (L[x] + R[x]) >> 1; 
		if (r <= mid) Modify(x << 1, l, r, v) ; 
		else if (l > mid) Modify(x << 1 | 1, l, r, v) ; 
		else Modify(x << 1, l, mid, v), Modify(x << 1 | 1, mid + 1, r, v) ; 
		val[x] = min(val[x << 1], val[x << 1 | 1]) ; 
}

int Get(int x, int goal) { 
		if (L[x] == R[x]) {
				return val[x] >= goal ? L[x] : -1 ;
		}	
		pushdown(x) ; 
		if (val[x << 1 | 1] < goal) return Get(x << 1 | 1, goal) ;
		else {
				int g = Get(x << 1, goal) ;
				if (g == -1) g = (L[x] + R[x]) / 2 + 1 ; 
				return g ; 
		}
}
int main() {
		scanf("%d%lf", &n, &k) ; 

		for (int i = 1; i <= n; i ++) { 
				scanf("%d", &a[i]) ; 
		}
		sort(a + 1, a + n + 1) ;
	    reverse(a + 1, a + n + 1) ; 	
		sf[n] = n ; 
		for (int i = n - 1; i; i --) { 
				sf[i] = a[i] == a[i + 1] ? sf[i + 1] : i ; 
		}
		for (int i = 1; i <= n; i ++) {
				fa[i] = (int) 1.0 * i / k ;
			   now[i] = i ; 	
		}
		for (int i = n; i; i --) { 
				siz[i] ++ ; 
				siz[fa[i]] += siz[i] ;
		}
		Build(1, 1, n) ;
		for (int i = 1; i <= n; i ++) { 
				if (fa[i]) Modify(1, ans[fa[i]], n, siz[i]) ;
				ans[i] = Get(1, siz[i]) ; 
				int suf = sf[ans[i]] ; 
				ans[i] = now[suf], now[suf] -- ; 
				Modify(1, ans[i], n, -siz[i]) ; 
		}
		for (int i = 1; i <= n; i ++) { 
				printf("%d%c", a[ans[i]], i == n ? 10 : ' ') ; 
		}
}

