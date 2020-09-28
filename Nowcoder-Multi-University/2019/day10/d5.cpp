#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define LL __int128
LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!a && !b) return -1;
    if (b == 0) { x = 1; y = 0; return a; }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
 
const int N = 210;
LL a[N], m[N];
int n; ll Mlimit;
void gao() {
    LL A = a[1], M = m[1], k, y, c, t;
    for (int i = 2; i <= n; ++i) {
        LL r = exgcd(M, m[i], k, y);
        c = a[i] - A; 
        if (c % r) {
            puts("he was definitely lying");
            return;
        }
		t = m[i] / r;
        k = (c / r * k % t + t) % t; 
        A += k * M; M = M * m[i] / r;
		if (A < 0) A = A + M;
    }
    if (A > Mlimit) {
        puts("he was probably lying");
        return;
    }
	ll res = A;
	printf("%lld\n", res);
}
 
int main() {
    while (scanf("%d%lld", &n, &Mlimit) != EOF) {
        for (int i = 1, x, y; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            m[i] = x; a[i] = y;
        }
        gao();
    }
    return 0;
}
