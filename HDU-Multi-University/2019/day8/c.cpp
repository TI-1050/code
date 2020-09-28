#include <bits/stdc++.h>
using namespace std;

#define ll long long 
ll f[100];

int main() {
	memset(f, 0, sizeof f);
//	for (int i = 1; i <= 100000000; ++i) {
//		int t = i;
//		while (t) {
//			++f[t % 10]; 
//			t /= 10;
//		}
//		for (int j = 1; j <= 9; ++j) {
//			if (i == f[j]) {
//				printf("%d %d\n", i, j);
//			}
//			//	printf("%lld%c", f[j], " \n"[j == 9]);
//		}
//	}
	f[1] = 1;
	ll base = 1;
	for (int i = 2; i <= 18; ++i) {
		base *= 10;
		f[i] = f[i - 1] * 9 + base;
		printf("%d %lld\n", i, f[i]);
	}
	return 0;
}
