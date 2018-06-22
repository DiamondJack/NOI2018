#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

typedef long long LL;
const int N = 200010;

LL gcd(LL a, LL b) { return a % b == 0 ? b : gcd(b, a % b); }

void e_gcd(LL a, LL b, LL& d, LL& x, LL& y) {
    if (!b) { d = a; x = 1; y = 0; } else {
        e_gcd(b, a%b, d, y, x); y -= x * (a / b);
    }
}

LL inverse(LL a, LL n) {  
    LL d,x,y;
    e_gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
} 

LL Product_Mod(LL a, LL b, LL mod) {
    LL sum = 0;
    int flag = b >= 0 ? 1 : -1;
    if(flag < 0) { b = -b; }
    while(b) {
        if(b & 1) sum = (sum + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return (sum * flag + mod) % mod;
}   // (a * b) % mod;

LL chineseRemain(int n, LL mod[], LL rem[]) {
    LL lcm = 1;
    for(int i = 0; i < n; ++i) {
        // K = x[i]*mod[i] + rem[i];
        // mod positive
        if(mod[i] < 0) {
            mod[i] = -mod[i];
        } 
        // r positive
        rem[i] = (rem[i] % mod[i] + mod[i]) % mod[i];
    } 
    // calculate lcm
    for(int i = 0; i < n; ++i) {
        LL g = gcd(lcm, mod[i]);
        lcm = lcm / g * mod[i];
    }

    LL A, B, C, X, Y, d;
    for(int i = 1; i < n; i++) {
        A = mod[0];
        B = -mod[i];
        C = rem[i] - rem[0];
        LL g = gcd(A, B);
        if( C % g ) {
            return -1;
        }
        A /= g, B /= g, C /= g;
        // make 'Ax + By = 1'
        if(A < 0) {
            // turn A and B to positive
            A = -A, B = -B, C = -C;
            B = ((B % A) + A) % A;
        }
        e_gcd(A, B, d, X, Y);
        Y = Product_Mod(Y, C, A);
        mod[0] = A * mod[i];
        rem[0] = (rem[i] +  Product_Mod(mod[i], Y, mod[0])) % mod[0];
    }
    return rem[0];
}   // return -1 if no solution

int n, m;
LL a[N], p[N], d[N], w[N], B[N], r[N];

int main() {

	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%lld", &a[i]);
		for(int i = 0; i < n; ++i)
			scanf("%lld", &p[i]);
		for(int i = 0; i < n; ++i)
			scanf("%lld", &d[i]);
		multimap<LL, int> mp;
		for(int i = 0; i < m; ++i) {
			scanf("%lld", &w[i]);
			mp.insert(make_pair(w[i], i));
		}
		for(int i = 0; i < n; ++i) {	// each dragon
			multimap<LL, int>::iterator it = mp.lower_bound(a[i]);
            if(it != mp.begin() && (*it).first != a[i]) { --it; }
			int id = (*it).second;
			B[i] = w[id];
			w[id] = d[i];
			mp.erase(it);
			mp.insert(make_pair(w[id], id));
		}
        bool flag = true;
        for(int i = 0; i < n; ++i) {
            LL tmp = inverse(B[i], p[i]);
            if(tmp == -1) {
                flag = false;
                printf("-1\n");
                break;
            }
            // B[i] * x = a[i] (mod p[i])
            r[i] = Product_Mod(tmp, a[i], p[i]);
        }
        if(flag == false) { continue; }
		printf("%lld\n", chineseRemain(n, p, r));
	}

	return 0;
}
