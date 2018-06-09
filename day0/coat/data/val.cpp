#include "testlib.h"

int f[333333], d[333333];
int g(int i) {return f[i] == i ? i : f[i] = g(f[i]);}

int main() {
	registerValidation();
	int N = inf.readInt(1, 1666); inf.readSpace();
	int K = inf.readInt(1, N); inf.readSpace();
	int W = inf.readInt(1, 1666); inf.readEoln();
	printf("%d %d %d, Is chain : ", N, K, W);
	for(int i = 1; i <= N; ++i) f[i] = i;
	for (int i = 1; i < N; ++i) {
		inf.readInt(1, W);
		inf.readSpace();
	}
	inf.readInt(1, W);
	inf.readEoln();
	for(int i = 1; i < N; ++i) {
		int x = inf.readInt(1, N); inf.readSpace();
		int y = inf.readInt(1, N); inf.readEoln();
		if(g(x) == g(y)) quitf(_fail, "Not a tree.");
		f[f[x]] = f[y];
		d[x]++, d[y]++;
	}
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= N; ++i) {
		if (d[i] == 1) c1++;
		else if (d[i] == 2) c2++;
	}
	if (c1 == 2 and c2 == N - 2) {
		printf("Yes\n");
	} else {
		printf("No\n");
	}
	inf.readEof();
}
