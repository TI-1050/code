//author Forsaken
#define Hello the_cruel_world!
#pragma GCC optimize(2)
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<utility>
#include<cmath>
#define FRIN freopen("C:\\Users\\Administrator.MACHENI-KA32LTP\\Desktop\\std.in", "r", stdin)
#define FROUT freopen("C:\\Users\\Administrator.MACHENI-KA32LTP\\Desktop\\std.out", "w", stdout)
#define outd(x) printf("%d\n", x)
#define outld(x) printf("%lld\n", x)
#define outu(x) printf("%u\n", x)
#define memset0(arr) memset(arr, 0, sizeof(arr))
#define il inline
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef unsigned int ui;
const int maxn = 1e5;
const int maxv = 1e7;
const int maxm = 4e3;
il int read_int() {
    char c;
    int ret = 0, sgn = 1;
    do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') sgn = -1; else ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    return sgn * ret;
}
il ll read_ll() {
    char c;
    ll ret = 0, sgn = 1;
    do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
    if (c == '-') sgn = -1; else ret = c - '0';
    while ((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    return sgn * ret;
}
il ll quick_pow(ll base, ll index, ll p) {
    ll res = 1;
    while (index) {
        if (index & 1)res = res * base % p;
        base = base * base % p;
        index >>= 1;
    }
    return res;
}
//莫队
int block;
struct query {
    bool operator < (const query& rhs)const {
        return l / block == rhs.l / block ? ((l / block) & 1 ? r < rhs.r : r > rhs.r) : l / block < rhs.l / block;
    }
    int l, r, id;
}q[maxn + 5];
//线性筛
bool is_prime[maxm + 5];
int prime[maxm + 5], cnt;
void init(int n) {
    for (int i = 2; i <= n; ++i)is_prime[i] = true;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i])prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0)break;
        }
    }
}
//质因子分解和处理因子部分
vector<int> prime_factor[maxn + 5], factor[maxn + 5];
il void get_prime(int x, int id) {
    for (int i = 1; i <= cnt && prime[i] * prime[i] <= x; ++i) {
        if (x % prime[i] == 0) {
            prime_factor[id].push_back(prime[i]);
            while (x % prime[i] == 0)x /= prime[i];
        }
    }
    if (x != 1)prime_factor[id].push_back(x);
}
il void get_factor(int id) {
    ui sz = prime_factor[id].size();
    int S = 1 << sz;
    for (int i = 0; i < S; ++i) {
        int val = 1, cnt_prime = 0;
        for (int j = 0; j < sz; ++j) {
            if (i & (1 << j)) {
                val *= prime_factor[id][j];
                ++cnt_prime;
            }
        }
        if (cnt_prime & 1)factor[id].push_back(-val);
        else factor[id].push_back(val);
    }
}
ui sum[maxv + 5], ans, res[maxn + 5];
int T, n, m, arr[maxn + 5];
il void add(int x) {
    for (int i = 0; i < factor[x].size(); ++i) {
        int d = factor[x][i];
        ui ad = abs(factor[x][i]), t = arr[x] / ad;
        ans += (2 * sum[ad] + t) * t * d;
        sum[ad] += t;
    }
}
il void del(int x) {
    for (int i = 0; i < factor[x].size(); ++i) {
        int d = factor[x][i];
        ui ad = abs(factor[x][i]), t = arr[x] / ad;
        ans += (-2 * sum[ad] + t) * t * d;
        sum[ad] -= t;
    }
}
int main()
{
    init(maxm);
    T = read_int();
    while (T--) {
        n = read_int(), m = read_int();
        ans = 0;
        for (int i = 1; i <= n; ++i)factor[i].clear(), prime_factor[i].clear();
        block = sqrt(n);
        for (int i = 1; i <= n; ++i) {
            arr[i] = read_int();
            get_prime(arr[i], i);
            get_factor(i);
        }
        for (int i = 1; i <= m; ++i)q[i].l = read_int(), q[i].r = read_int(), q[i].id = i;
        sort(q + 1, q + 1 + m);
        int l = 1, r = 0;
        for (int i = 1; i <= m; ++i) {
            while (r < q[i].r)add(++r);
            while (l > q[i].l)add(--l);
            while (r > q[i].r)del(r--);
            while (l < q[i].l)del(l++);
            res[q[i].id] = ans;
        }
        for (int i = 1; i <= m; ++i)outu(res[i]);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < factor[i].size(); ++j) {
                int d = abs(factor[i][j]);
                sum[d] = 0;
            }
        }
    }
    //system("pause");
    return 0;
}
