#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
#define ll long long
const int K = 5;
int T, n, x; ll res;
map <int, ll> mp[K];
void gao(int o, int x, ll p) {
    if (o >= K) return;
    mp[o][x] += p;
    res += p;
    while (p) {
        map<int, ll>::iterator it = mp[o].lower_bound(x + 1);
        if (it == mp[o].end()) return;
        ll t = min(p, it->second);
        res -= t;
        p -= t;
        gao(o + 1, it->first, t);
        if (t == it->second) mp[o].erase(it);
        else it->second -= t;
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        res = 0;
        for (int i = 0; i < K; ++i) mp[i].clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x);
            gao(0, x, x);
            printf("%lld%c", res, " \n"[i == n]);
        }
    }
    return 0;
}
