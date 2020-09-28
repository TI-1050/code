#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll A, B, C, D, res;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll calc(int i, int j) {
	return max(0ll, min(B / i, D / j) - max((A - 1) / i, (C - 1) / j));
}

int main() {
	while (scanf("%lld%lld%lld%lld", &A, &B, &C, &D) != EOF) {
		res = 0;
		for (int i = 1; i <= 1000; ++i) {
			for (int j = 1; j <= 1000; ++j) {
				if (gcd(i, j) == 1 && (i + j) < 1000) {
					res += calc(i, j);
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
