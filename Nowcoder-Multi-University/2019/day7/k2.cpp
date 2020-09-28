#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll mod = 1e18 + 7;
const int N = 1e5 + 5;
ll w[N], id1[N], id2[N];
int tot, n;
ll g[N], spg[50005], gg[N], spgg[50005];
bool vis[N];
int prime[50005];
 
ll Pow(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
 
void getp(int n)
{
    int nn = (int)sqrt(n * 1.0);
    tot = 0;
    spg[0] = spgg[0] = 0;
    for (int i = 2; i <= nn; i++)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            if (i % 4  == 1)
            {
                spg[tot] = (spg[tot - 1] + 4) % mod;
                spgg[tot] = (spgg[tot - 1] + 1) % mod;
            }
            else
            {
                spg[tot] = (spg[tot - 1] + 1) % mod;
                if (i % 4 == 3)
                    spgg[tot] = (spgg[tot - 1] + 4) % mod;
                else
                    spgg[tot] = (spgg[tot - 1] + 1) % mod;
            }
        }
        for (int j = 1; j <= tot && prime[j] * i <= nn; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
 
ll squ;
 
ll S(ll x, int y)
{
    if (x <= 1 || x < prime[y])
        return 0;
    int k = (x <= squ)? id1[x] : id2[n / x];
    ll ret = (g[k] - spg[y - 1] + mod) % mod;
    for (int i = y; i <= tot && 1ll * prime[i] * prime[i] <= x; i++)
    {
        ll sgn = (prime[i] % 4 == 1)? 3 : 0;
        ll t1 = prime[i], t2 = prime[i] * prime[i];
        for (int e = 1; t2 <= x; e++, t1 = t2, t2 *= prime[i])
        {
            ret = (ret + S(x / t1, i + 1) * (e * sgn + 1) % mod + (e + 1) * sgn + 1) % mod;
        }
    }
    return ret;
}
 
ll tmp[N];
stack<int> st;
void solve(int n)
{
    getp(n);
    squ = int(sqrt(n * 1.0));
    // cout << squ <<endl;
    int m = 0;
    while (!st.empty())
        st.pop();
    ll inv2 = (mod + 1) / 2;
    for (int i = 1, j; i <= n; i = j + 1)
    {
        j = n / (n / i), w[++m] = n / i;
        if (w[m] <= squ)
            id1[w[m]] = m;
        else
            id2[n / w[m]] = m;
        g[m] = ((w[m] - 1) / 4 * 3 + w[m] - 1) % mod;
        gg[m] = ((w[m] + 1) / 4 * 3 + w[m] - 1) % mod;
        // printf("%d %lld %lld g m\n", n / i, g[m], gg[m]);
    }
    for (int j = 1; j <= tot; j++)
    {
        for (int i = 1; i <= m && prime[j] * prime[j] <= w[i]; i++)
        {
            int k = (w[i] / prime[j] <= squ)? id1[w[i] / prime[j]] : id2[n / (w[i] / prime[j])];
            if (prime[j] % 4 == 1)
            {
                gg[i] = (gg[i] - (gg[k] - spgg[j - 1]) % mod + mod) % mod;
                g[i] = (g[i] - (g[k] - spg[j - 1]) % mod + mod) % mod;
            }
            if (prime[j] % 4 == 3)
            {
                tmp[i] = (g[i] - (gg[k] - spgg[j - 1]) % mod + mod) % mod;
                st.push(i);
                gg[i] = (gg[i] - (g[k] - spg[j - 1]) % mod + mod) % mod;
            }
            if (prime[j] == 2)
            {
                gg[i] = (gg[i] - w[i] / prime[j] + 1 + mod) % mod;
                g[i] = (g[i] - w[i] / prime[j] + 1 + mod) % mod;
            }
            // printf("for %d %lld %lld %lld\n", prime[j], w[i], g[i], gg[i]);
            // g[i] = (g[i] - (g[k] - spg[j - 1]) % mod * prime[j] % mod + 2 * mod) % mod;
        }
        while (!st.empty())
        {
            int t = st.top();
            st.pop();
            g[t] = tmp[t];
        }
    }
 
    printf("%lld\n", (S(n, 1) + 1) % mod);
}
 
template<class T>
void read(T& ret)
{
    ret = 0;
    char c;
    while ((c = getchar()) > '9' || c < '0');
    while (c >= '0' && c <= '9')
    {
        ret = ret * 10 + c - '0';
        c = getchar();
    }
}
 
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        read(n);
        solve(n);
    }
    return 0;
}
