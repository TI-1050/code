#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define LL __int128
#define N 10000010
#define pLi pair <LL, int> 
#define fi first
#define se second
const int p = 998244353; 
int prime[N], tot;
int phi[N], F[N], G[N]; 
int check[N]; 
ll ans[20];

template <class T>
inline void read(T &x) {
	static char ch;static bool neg;
	for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
	for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
	x=neg?-x:x;
}

template <class T>
void out(T x) {
	if (x / 10) out(x / 10);
	putchar(x % 10 + '0');
}

template <class T1, class T2>
inline void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}
void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	phi[1] = 1;
	F[1] = 1; G[1] = 1;  
	for (int i = 2; i < 10000000; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
			phi[i] = i - 1;
			F[i] = i + phi[i]; 
			G[i] = i;
		} 
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] > 10000000) break;
			int now = i * prime[j];
			check[now] = 1; 
			if (i % prime[j] == 0) {
				phi[now] = phi[i] * prime[j];
				G[now] = F[now] = 0;
				if (G[i] > 0) {
					G[now] = (1ll * G[i] * prime[j] % p + (now - i)) % p;
					F[now] = (G[now] + phi[now]) % p;
				} else {
					G[now] = G[i] * prime[j] % p; 
					F[now] = F[i / -G[i]] * F[-G[now]] % p;
				}
				break;
			} else {
				phi[now] = phi[i] * (prime[j] - 1);
				F[now] = F[i] * F[prime[j]] % p;
				G[now] = -prime[j]; 
			}
		}
	}
	for (int i = 2; i < N; ++i) {
		add(phi[i], phi[i - 1]);
	}
}

int g(int n, int m) {
	if (n == 0 || m == 0) return 0; 
	int res = 0;
	if (n > m) swap(n, m);
	for (int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		add(res, 1ll * (n / i) * (m / i) % p * ((phi[j] - phi[i - 1] + p) % p) % p);
	}
	return res;
}

int f(int n, int m) {
	return (g(n, m) - g(n - 1, m) + p) % p; 
}

template <class T>
inline int Mod(T &x, int p) {
	return ((x - 1) % p + 1);
}

int main() {
	int D = 1e7;
	init();
	int T; scanf("%d", &T);
	vector <pLi> vec(T);
	for (int i = 0; i < T; ++i) {
		read(vec[i].fi);
		vec[i].se = i;
	}
	sort(vec.begin(), vec.end()); 
	int pos = 0;  
	while (pos < T && (vec[pos].fi <= 7)) {
		ans[vec[pos].se] = vec[pos].fi;
		++pos;
	}
	ll res = 7;
	LL L = 0, R = 7, R2;
	for (int i = 2; i <= D; ++i) {
		L = R + 1, R = (i + 1);
		R = R * R * R - 1; 
		while (pos < T && R > vec[pos].fi) {
			int it = vec[pos].se;
			ans[it] = res;
			R = vec[pos].fi;
			R2 = (R / i) * i;
			int Loop = ((R2 - L) / i) % p;
			add(ans[it], i);
			add(ans[it], 1ll * Loop * F[i] % p);
			if (R > R2) {
				add(ans[it], f(i, Mod(R, i)));
			}
			++pos;
		}
		R = i + 1;
		R = R * R * R - 1; 
		int Loop = ((R - L) / i) % p;
		add(res, 1ll * Loop * F[i] % p);
		add(res, i);  
		while (pos < T && vec[pos].fi == R) {
			ans[vec[pos].se] = res;
			++pos;
		}
		if (pos >= T) break;
	}
	for (int i = 0; i < T; ++i) printf("%lld\n", ans[i]);
	return 0;
}
