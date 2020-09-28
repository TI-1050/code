#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	ll two = 1, three = 1;
	for (int i = 0; i < 64; ++i) {
		two *= 2;
		three = 1;
		for (int j = 0; j < 64; ++j) {
			if (two * three > 1e18) break;
			printf("%d %d %lld\n", i, j, two * three);
			three *= 3;
		}
	}
	return 0;
}
