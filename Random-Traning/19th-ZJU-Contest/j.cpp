#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	int T; cin >> T;
	while (T--) {
		ll n; scanf("%lld", &n);
		if (n & 1) {
			printf("9 %lld\n", n + 9);
		} else {
			printf("4 %lld\n", n + 4);
		}
	}
	return 0;
}
