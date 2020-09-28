#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define LL __int128
#define N 10000010
const ll p = 998244353; 
int prime[N / 10], tot;
ll phi[N], F[N], G[N]; 
bool check[N];    

template <class T>
void read(T &x) {
	static char ch;static bool neg;
	for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
	for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
	x=neg?-x:x;
}

template <class T1, class T2>
void add(T1 &x, T2 y) {
	x += y;
	if (x >= p) x -= p;
}

void init() {
	memset(check, 0, sizeof check);
	tot = 0;
	phi[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			prime[++tot] = i;
			phi[i] = i - 1;
		} 
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1; 
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int j = 1; j <= tot; ++j) {
		G[1] = 0;
	    G[prime[j]] = prime[j];	
		if (1ll * prime[j] * prime[j] < N) {
			for (int k = prime[j] * prime[j]; ; k *= prime[j]) {
				G[k] = (G[k / prime[j]] * prime[j] % p + (k - k / prime[j]) % p) % p;
				if (1ll * k * prime[j] >= N) break;
			}	
		}
		for (int k = prime[j]; ; k *= prime[j]) {
			F[k] = (G[k] + phi[k]) % p;
			if (1ll * k * prime[j] >= N) break;
		}
	}
	G[1] = 1;
	F[1] = 1;
	for (int i = 2; i < N; ++i) {
		for (int j = 1; j <= tot; ++j) {
			if (prime[j] > i || 1ll * i * prime[j] >= N) break;
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				int now = i * prime[j];
				G[now] = G[i] * prime[j];
				if (G[now] != now) {
					F[now] = F[i / G[i]] * F[G[now]] % p;	
				}
				break;
			} else {
				F[i * prime[j]] = F[i] * F[prime[j]] % p;
				G[i * prime[j]] = prime[j]; 
			}
		}
	}
	for (int i = 2; i < N; ++i) {
		phi[i] = (phi[i - 1] + phi[i]) % p;
	}
}

ll g(int n, int m) {
	if (n == 0 || m == 0) return 0; 
	ll res = 0;
	if (n > m) swap(n, m);
	for (int i = 1, j; i <= n; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		res += (n / i) * (m / i) % p * ((phi[j] - phi[i - 1] + p) % p) % p;
		res %= p;
	}
	return res;
}

ll f(int n, int m) {
	return (g(n, m) - g(n - 1, m) + p) % p; 
}

ll Mod(LL x, LL p) {
	return (x - 1) % p + 1;
}

int main() {
	init();
	int T; scanf("%d", &T);
//	while (T--) {
//		LL n; read(n);
//		int D = 1e7;
//		ll res = 0;
//		for (int i = 1; i <= D; ++i) {
//			ll tmp = 0;
//			LL L = i, R = (i + 1);
//			L = L * L * L, R = R * R * R; R -= 1;
//			if (L > n) break;
//			if (R <= n) {
//				if (i == 1) add(tmp, (R - L + 1) % p);
//				else {
//					ll Loop = ((R - L) / i) % p;
//					add(tmp, Loop % p * F[i] % p);
//					add(tmp, i);  
//				}
//			} else {
//				R = n;
//				LL L2 = (L / i + (L % i != 0)) * i;  
//				if (L2 >= R) {
//					add(tmp, (f(i, Mod(R, i)) - f(i, Mod(L - 1, i)) + p) % p);
//				} else {
//					add(tmp, (f(i, Mod(L2, i)) - f(i, Mod(L - 1, i)) + p) % p);
//					LL R2 = (R / i) * i;
//					ll Loop = ((R2 - L2) / i) % p;
//					add(tmp, Loop % p * F[i] % p);  
//					if (R > R2) {
//						add(tmp, f(i, Mod(R, i)));
//					}
//				}
//			}
//			add(res, tmp);
//		}
//		printf("%lld\n", res);
//	}
	return 0;
}
