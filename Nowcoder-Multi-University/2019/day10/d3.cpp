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
LL c, MOD;
LL a[N], m[N];
int n; LL Mlimit;
 
template <class T>
void rd(T &x) {
    x = 0; char ch;
    while (!isdigit(ch = getchar()));
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
}
 
template <class T>
void out(T x) {
    if (x / 10) out(x / 10);
    putchar(x % 10 + '0');
}
 
void gao() {
    LL A = a[1], M = m[1], k, y;
    for (int i = 2; i <= n; ++i) {
        LL r = exgcd(M, m[i], k, y);
        c = a[i] - A; MOD = m[i] / r;
        if (c % r) {
            puts("he was definitely lying");
            return;
        }
        k = (k * (c / r) % MOD + MOD) % MOD;
        A += k * M; M = M * m[i] / r;
        A = (A + M) % M;
    }
    if (A > Mlimit) {
        puts("he was probably lying");
        return;
    }
    out(A); puts("");
}

bool ok(ll a1, ll m1, ll a2, ll m2) {
	LL A = a1, M = m1, k, y;
	LL r = exgcd(M, m2, k, y);
	c = a2 - A; MOD = m2 / r;
	if (c % r) return 0;
	return 1;
}
 
int main() {
    while (scanf("%d", &n) != EOF) {
        rd(Mlimit);
        for (int i = 1, x, y; i <= n; ++i) {
            scanf("%d%d", &x, &y);
            m[i] = x; a[i] = y;
        }
		bool F = 1;
		for (int i = 1; i <= n && F; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				if (ok(a[i], m[i], a[j], m[j]) == 0) {
					F = 0;
					break;
				}
			}
		}
		if (!F) {
            puts("he was definitely lying");
		} else {
        	gao();
		}
    }
    return 0;
}
