#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll a, vec[110]; int sze;

ll f(ll x, int p) {
	ll base = 1;
	while (x) {
		if (x % 2) {
			if (base % 3 == p) {
				return base; 
			}
		}
		x >>= 1;
		base <<= 1;
	}
	return -1;
}

void solve(ll x) {
	sze = 0;
	ll base = 1;
	ll t = x;
	while (x) {
		if (x % 2) {
			vec[sze++] = base;
		}
		x >>= 1;
		base <<= 1;
	}	
	ll A = vec[0] | vec[1] | vec[2];
	ll B = t ^ vec[0];
	if ((t % 3) != (vec[0] % 3)) {
		B ^= vec[1];
	}
	printf("2 %lld %lld\n", A, B);
}

bool same(ll x) {
	sze = 0;
	ll base = 1;
	while (x) {
		if (x % 2) {
			vec[sze++] = base;
		}
		base <<= 1;
		x >>= 1;
	}
	for (int i = 1; i < sze; ++i) {
		if ((vec[i] % 3) != (vec[i - 1] % 3)) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld", &a);
		if (a % 3 == 0) {
			printf("1 %lld\n", a);
		} else if (same(a)) {
			solve(a);
		} else if (a % 3 == 1) {
			ll x = f(a, 1);	
			if (x != -1) {
				ll y = a ^ x;
				x ^= f(a, 2);
				printf("2 %lld %lld\n", x, y);
			} 
		} else if (a % 3 == 2) {
			ll x = f(a, 2);
			if (x != -1) {
				ll y = a ^ x;
				x ^= f(a, 1);
				printf("2 %lld %lld\n", x, y);
			} 
		}
	}
	return 0;
}
