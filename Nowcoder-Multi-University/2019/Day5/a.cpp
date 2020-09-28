#include <bits/stdc++.h>
using namespace std;

#define ll long long
int f(ll x) {
	int res = 0;
	while (x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

int main() {
	for (int i = 1; i <= 100; ++i) {
		for (ll j = i; ; ++j) {
			if (j % i == 0 && f(j) % i == 0) {
				cout << i << " " << j << endl;
				break;
			}
		}
	}
	return 0;
}
