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
struct node {
	LL A, B, C;
	node() {}
	node(LL A, LL B, LL C) : A(A), B(B), C(C) {}
	bool operator < (const node &other) const {
		if (A != other.A) return A < other.A;
		return B > other.B;  
	}
}arr[1000000];
int cnt;

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

void insert(int x, int y) {
	for (int i = 2; 1ll * i * i <= x; ++i) if (x % i == 0) {
		int num = 0;
		int now = 1;
		while (x % i == 0) {
			++num;
			x /= i;
			now *= i;
		}
		arr[++cnt] = node(i, num, y % now); 
	}
	if (x) {
		arr[++cnt] = node(x, 1, y % x);  
	}
}

LL qmod(LL base, LL n) {
	LL res = 1;
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;
	}
	return res;
}

void gao() {
	LL A = arr[1].C, M = arr[1].A, k, y;
	for (int i = 2; i <= cnt; ++i) {
		LL r = exgcd(M, LL(arr[i].A), k, y);
		c = LL(arr[i].C) - A; MOD = LL(arr[i].A) / r;
		if (c % r) {
			puts("he was definitely lying");
			return;
		}
		k = (k * (c / r) % MOD + MOD) % MOD;
		A += k * M; M = M * LL(arr[i].A) / r;
		A = (A + M) % M; 
		if (A > Mlimit) {
			puts("he was probably lying");
			return;
		}
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
		rd(Mlimit); cnt = 0;
		for (int i = 1, x, y; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			if (x == 1) continue;
			m[i] = x; a[i] = y;
			insert(x, y); 
		}
		sort(arr + 1, arr + 1 + cnt);
		for (int i = 1; i <= cnt; ++i) {
			arr[i].A = qmod(arr[i].A, arr[i].B);
		}
		bool F = 1;
		for (int i = 1; i <= cnt && F; ++i) {
			for (int j = i + 1; j <= cnt; ++j) {
				if (ok(arr[i].C, arr[i].A, arr[j].C, arr[j].A) == 0) { 
					F = 0;
					break;
				}
			}
		}
		if (!F) {
            puts("he was definitely lying");
			continue;
		} 
		gao();
	}
	return 0;
}
