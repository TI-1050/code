#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <functional>
using namespace std;
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
inline int pow2(int b) {
    if (b < 23) return 1 << b;
    else return 0;
}

int exgcd(int a, int b, int & x, int & y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    int res = exgcd(b, a%b, y, x);
    y -= (a/b)*x;
    return res;
}

void exgcd1(int a, int b, int & x, int & y) {
    if(!b) {
        x = 1;
        y = 0;
        return;
    }
    exgcd1(b, a%b, y, x);
    y -= (a/b)*x;
}
int reverse2(int a) {
    int x, y;
    exgcd1(a, 1<<23, x, y);
    return x;
}

int CC[2][1000][1000];
inline long long C(long long n, long long m, long long p) {
    return CC[p == 17][n][m];
}
inline int Lucas(int n, int m, int p) {//预处理部分组合数，带模意义下，最终值小于n
    if (!m) return 1;
    int v = 1, x, y;
    while (n >= 1000) {
        x = n / p, y = m / p;
        v *= C(n - p*x, m - p * y, p);
        n = x, m = y;
    }
    return CC[p == 17][n][m] * v;
}

inline int myLucas(int n, int m, int p) {//模小质数下，不会大于n，最后取模来加速 （这里为7,19）
    if (!m) return 1;
    int x = n / p, y = m / p;
    return Lucas(x, y, p)*C(n - x * p, m - y * p, p) % p;
}
int tmp = 1;
int ans1[200];
int g[10000000];
#define help 8388607
int help1[10000000];
int cal(int n) {
    int v = 1;
    while (n >= (1<<23)) {
        v *= ans1[n>>23] * g[n & help];
        n >>= 1;
    }
    return help1[n] * v;
}
int multiLucas(int n, int m) {//针对模2^23加速
    int i, s = 0;
    for(i = n; i; i >>= 4) s += (i >> 1) + (i >> 2) + (i >>3) + (i >> 4);
    for(i = m; i; i >>= 4) s -= (i >> 1) + (i >> 2) + (i >>3) + (i >> 4);
    for(i = n - m; i; i >>= 4) s -= (i >> 1) + (i >> 2) + (i >>3) + (i >> 4);

    if (s >= 23) return 0;
    return (((cal(n)*reverse2((cal(m) * cal(n-m) ) & help)) << s) & help);//逆元不用预处理，这样更快
}
long long exLucas_n_m_w(int n, int m, int w, int t1, int t2, int t3) {//求Cn,m * Cn-m,w * t1^x * t2^y mod 998244352
    static int i, d, c, t, x, y, q[100], a[100], e;
    q[1] = 8388608;
    if (!t1) a[1] = 0;
    else
        a[1] = (multiLucas(n, m) * multiLucas(n - m, w) * t1) & help;
    q[2] = 7;
    if (!t2) a[2] = 0;
    else
        a[2] = myLucas(n, m, 7) * myLucas(n - m, w, 7) * t2 % 7;
    q[3] = 17;
    if (!t3) a[3] = 0;else
        a[3] = myLucas(n, m, 17) * myLucas(n - m, w, 17) * t3 % 17;
    for(i = 2; i <= 3; i++) {
        exgcd1(q[1], q[i], x, y);
        c = a[i]-a[1];
        t = q[i];
        x = (c*x%t+t)%t;
        a[1] = q[1]*x+a[1];
        q[1] = q[1]*q[i];
    }
    return a[1];
}
long long calc(long long x ,long long y, long long mod){
    if (!(mod &1)) {
        if (!(x & 1) && y >= 23) return 0;
        y &=(help >> 1);
        int z = 1;
        while (y) {
            if (y & 1) z *= x;
            x *= x, y >>=1;
        }
        return z & help;
    } else
    if (mod == 998244353) {
        long long z = 1;
        while (y) {
            if (y & 1) (z *= x) %= mod;
            (x *= x) %= mod, y >>=1;
        }
        return z;
    }
    long long z = 1;
    while (y) {
        if (y & 1) z *= x;
        x *= x, y >>=1;
        if (z >= 1e9) z %= mod;
        if (x >= 1e9) x %= mod;
    }
    return z % mod;
}
int t1, t2, p, q, N, M;
const int mod = 998244353;
inline int read(){
    int x=0,f=1; char ch=getchar();
    while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
    while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
    return x*f;
}
int main(){
    // freopen("input", "r", stdin);
    CC[0][0][0] = 1;
    CC[1][0][0] = 1;
    for (int i = 1; i < 1000; i ++) {
        CC[0][i][0] = 1;
        CC[1][i][0] = 1;
        for (int j = 1; j<= i; j ++)
            (CC[0][i][j] = CC[0][i - 1][j] + CC[0][i - 1][j - 1]) >= 7? CC[0][i][j] -= 7:NULL, (CC[1][i][j] = (CC[1][i - 1][j] + CC[1][i - 1][j - 1]))>=17?CC[1][i][j] -= 17:NULL;
    }
    g[0] = g[1] =1;
    help1[0] = 1, help1[1] = 1;
    for (int i = 3; i <= (1 << 23) + 1; i += 2)
        g[i - 1] = g[i - 2], g[i] = g[i - 2] * i, help1[i - 1] = g[i - 1] * help1[i >> 1], help1[i] = g[i] * help1[i >> 1];
    tmp = g[(1<<23)];
    ans1[0] = 1;
    for (int i = 1; i < 200; i ++)
        ans1[i] =ans1[i - 1] * tmp;
    while (scanf("%d %d %d %d %d", &t1, &t2, &p, &q, &N) != EOF) {
        long long v = 1;
        M = read();
        int x, y, a;
        while (M --) {
            x = read(), y = read(), a = read();
            if (x % p || y % q) continue;
            x /= p, y /= q;
            if (N >= x + y) {
                v = v * calc(a, exLucas_n_m_w(N, x, y, calc(t1, x, 1<<23) * calc(t2, y, 1<<23) & help,
                                              calc(t1 % 7, x % 6, 7) * calc(t2 % 7, y % 6, 7) % 7,
                                              calc(t1 % 17, x & 15, 17) * calc(t2 % 17, y &15, 17) % 17), mod) % mod;
            }
        }
        printf("%lld\n", v);
    }
    return 0;
}
