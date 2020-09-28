#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll p = 998244353;
#define N 3010

ll qpow(ll x, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1) {
            res = res * x % p;
        }
        x = x * x % p;
        n >>= 1;
    }
    return res;
}

int main() {
    ll inv3 = qpow(3, p - 2);
    while (scanf("%d", &n) != EOF) {
        ll ans = qpow(n - 1, n);
        ans = ans * qpow(inv3, n - 1) % p;
        printf("%lld\n", ans);
    }
    return 0;
}
