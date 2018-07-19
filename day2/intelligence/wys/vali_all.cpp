#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

void my_assert(bool e, const char *msg = "gugugu") {
	if (!e) {
		printf("%s\n", msg);
		throw 233;
	}
}

long long read_int(FILE *f, long long l, long long r) {
	long long ret = -1;
	my_assert(fscanf(f, "%lld", &ret) == 1, "gg, no int");
	my_assert(ret >= l && ret <= r, "int out of range");
	return ret;
}

const int g_max_n = 5 * 10000;
const int g_max_m = 100000;
const int g_max_ci = 1000000000;
const int g_max_sum_n = 1000233;
const int g_max_sum_m = 2000233;

const int g_max_T = g_max_sum_n;  // TODO range of T

const int MAXN = g_max_n + 10;
const int MAXM = g_max_m + 10;

const int T_CHAIN = 1 << 0;
const int T_ZERO_C = 1 << 1;
const int T_S1 = 1 << 2;
const int T_S2 = 1 << 3;
const int T_M_LEQ_N = 1 << 4;

int a[MAXN], b[MAXN];
int c[MAXN];
int x[MAXM], y[MAXM];
int lca[MAXM];
long long v[MAXM];

int fa[MAXN][16];
int dep[MAXN];

int getdep(int x) {
	return dep[x] ? dep[x] : dep[x] = getdep(fa[x][0]) + 1;
}

int jump(int x, int d) {
	for (int i = 15; i >= 0; i--) {
		if ((d >> i) & 1) {
			x = fa[x][i];
		}
	}
	return x;
}

int getlca(int a, int b) {
	int d1 = getdep(a), d2 = getdep(b);
	if (d1 < d2) {
		b = jump(b, d2 - d1);
	} else {
		a = jump(a, d1 - d2);
	}
	if (a == b) {
		return a;
	}
	for (int i = 15; i >= 0; i--) {
		if (fa[a][i] != fa[b][i]) {
			a = fa[a][i];
			b = fa[b][i];
		}
	}
	return fa[a][0];
}

void check(std::string filename, int max_n, int max_m, int max_T, int type) {
	FILE *f = fopen(filename.c_str(), "r");
	int T = read_int(f, 0, max_T);
	int sum_n = 0;
	int sum_m = 0;
	while (T--) {
		int n = read_int(f, 1, std::min(g_max_n, max_n));
		sum_n += n;
		my_assert(sum_n <= g_max_sum_n, "sum n too large");
		for (int i = 1; i < n; i++) {
			a[i] = read_int(f, 1, n);
			b[i] = read_int(f, 1, n);
			c[i] = read_int(f, 0, g_max_ci);
			my_assert(a[i] < b[i], "a[i] >= b[i]");
			if (type & T_CHAIN) {
				my_assert(a[i] == b[i] - 1, "not a chain");
			}
			if (type & T_ZERO_C) {
				my_assert(c[i] == 0, "c[i] is not zero");
			}
		}
		my_assert((int) std::set<int>(b + 1, b + n).size() == n - 1, "b[i] not distinct");
		
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 16; j++) {
				fa[i][j] = 0;
			}
		}
		for (int i = 1; i < n; i++) {
			fa[b[i]][0] = a[i];
		}
		for (int i = 1; i < 16; i++) {
			for (int j = 1; j <= n; j++) {
				fa[j][i] = fa[fa[j][i - 1]][i - 1];
			}
		}
		for (int i = 1; i <= n; i++) {
			dep[i] = 0;
		}
		dep[1] = 1;
		
		int m = read_int(f, 0, std::min(g_max_m, max_m));
		if (type & T_M_LEQ_N) {
			my_assert(m <= n, "m > n");
		}
		sum_m += m;
		my_assert(sum_m <= g_max_sum_m, "sum m too large");
		for (int i = 1; i <= m; i++) {
			x[i] = read_int(f, 1, n);
			y[i] = read_int(f, 1, n);
			v[i] = read_int(f, 0, 10000000000LL * n);
			lca[i] = getlca(x[i], y[i]);
			
			if (type & T_S2) {
				my_assert(lca[i] == 1, "lca is not 1");
			}
		}
		if (type & T_S1) {
			my_assert((int) std::set<int>(lca + 1, lca + m + 1).size() == m, "lca not distinct");
		}
	}
	fclose(f);
	printf("ok %s\n", filename.c_str());
}

int main() {
	check("../down/1.in", g_max_n, g_max_m, g_max_T, 0);
	check("../down/2.in", g_max_n, g_max_m, g_max_T, 0);
	check("../down/3.in", g_max_n, g_max_m, g_max_T, 0);
	check("../down/4.in", 100, 200, g_max_T, 0);
	
	check("../data/1.in", 2, 3, 50, 0);
	check("../data/2.in", 10, 30, 50, 0);
	check("../data/3.in", 200, 300, 50, 0);
	
	check("../data/4.in", 1000, 2000, 50, T_CHAIN);
	check("../data/5.in", 10000, 30000, 50, T_CHAIN);
	check("../data/6.in", 50000, 100000, 50, T_CHAIN);
	
	check("../data/7.in", 10000, 30000, 50, T_ZERO_C);
	check("../data/8.in", 50000, 100000, 50, T_ZERO_C);
	check("../data/9.in", 50000, 100000, 50, T_ZERO_C);
	
	check("../data/10.in", 10000, g_max_m, 50, T_S1 | T_M_LEQ_N);
	check("../data/11.in", 50000, g_max_m, g_max_T, T_S1 | T_M_LEQ_N);
	check("../data/12.in", 50000, g_max_m, g_max_T, T_S1 | T_M_LEQ_N);
	
	check("../data/13.in", 10000, 30000, 50, T_S2);
	check("../data/14.in", 10000, 30000, 50, T_S2);
	
	check("../data/15.in", 50000, 100000, g_max_T, T_S2);
	check("../data/16.in", 50000, 100000, g_max_T, T_S2);
	
	check("../data/17.in", 10000, 30000, 50, 0);
	
	check("../data/18.in", 50000, 100000, 50, 0);
	
	check("../data/19.in", 50000, 100000, g_max_T, 0);
	check("../data/20.in", 50000, 100000, g_max_T, 0);
}
