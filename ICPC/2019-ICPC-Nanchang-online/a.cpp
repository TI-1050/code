#include <bits/stdc++.h>
using namespace std;

#define ll long long
bool ok(ll x) {
	int tot = 0;
	for (int i = 1; 1ll * i * i <= x; ++i) {
		if (x % i == 0) { 
			if (1ll * i * i == x) {
				tot += i;
			} else {
				tot += i;
				if (i != 1) {
					tot += x / i;
				}
			}
		}	
	}
	return tot == x;
}

int main() {
	int a[] = {
		6, 28, 496, 8128, 33550336
	};
	for (int i = 0; i < 5; ++i) {
		printf("%d\n", a[i]);
	}
	return 0;
}
