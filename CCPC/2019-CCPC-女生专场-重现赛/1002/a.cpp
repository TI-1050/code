#include <bits/stdc++.h>
using namespace std;

#define ll long long 
ll n;

ll f(ll n) {
	return n * (n + 1) / 2;
}

int main() {
	while (scanf("%lld", &n) != EOF) {
		ll F = f(n);
		for (ll i = 2; ; ++i) {
			if (F % i == 0) {
				printf("%lld\n", F / i);
				break;
			}
		}
	}
	return 0;
}
