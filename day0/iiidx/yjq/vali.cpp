#include <bits/stdc++.h>

using namespace std ;

int N, D, type ; 
double lk, rk ; 

int n ; 
double k ; 

const int MAXN = 500010 ; 

int d[MAXN] ; 
int main(int argc, char * argv[]) {

		sscanf(argv[1], "%d", &N) ; 
		sscanf(argv[2], "%d", &D) ; 
		sscanf(argv[3], "%lf", &lk); 
		sscanf(argv[4], "%lf", &rk) ; 
		sscanf(argv[5], "%d", &type) ; 
		freopen(argv[6], "r", stdin) ; 
		
		printf("check %s", argv[6]) ; 
		putchar(10) ; 
		scanf("%d%lf", &n, &k) ; 

		assert(1 <= n && n <= N) ; 
		puts("n ok") ; 
		assert(lk <= k && k <= rk) ; 
		puts("k ok") ; 
		if (k == 1) { 
				puts("k = 1, fail") ; 
				return 1 ; 
		}
		for (int i = 1; i <= n; i ++) { 
				scanf("%d", &d[i]) ; 
				assert(1 <= d[i] && d[i] <= D) ; 
		}
		puts("d ok") ; 
		
		if (!type) {
				return 0 ; 
				puts("all ok") ; 
		}

		puts("check unique") ; 

		sort(d + 1, d + n + 1 ) ; 
		for (int i = 1; i < n; i ++) { 
				if (d[i] == d[i + 1]) { 
						puts("not unique") ;
					    printf("%d %d\n", d[i], d[i + 1]) ;	
						return 1 ; 
				}
		}

		puts("all ok") ; 
}
		

