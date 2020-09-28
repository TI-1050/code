#include <bits/stdc++.h>
using namespace std;

using uint = uint32_t;
using ll = long long;

const int N = 1e7 + 10;

int n, q;
uint x0, a, x1, b, c;

uint nxt() {
	uint t = x0 * a + x1 * b + c;
	x0 = x1;
	x1 = t;
	return x0 >> 2;
}

uint arr[N];

int main() {
	while (scanf("%d %d %u %u %u %u %u", &n, &q, &x0, &x1, &a, &b, &c) != EOF) {
		uint i = nxt() % n, x = nxt();
		uint limit = -1;
		for (int i = 0; i < n; ++i) {
			arr[i] = limit;
		}
		arr[i] = x;
		uint Min = x;
		uint res = Min * 10099, base = 10099;
		for (int cas = 2; cas <= q; ++cas) {
			base = base * 10099;
			i = nxt() % n, x = nxt();
			if (arr[i] == Min && x > Min) {
				arr[i] = x;
				Min = x;
				for (int i = 0; i < n; ++i) Min = min(Min, arr[i]);
			} else {
				arr[i] = x;
			}
			Min = min(Min, x);
			res = res + base * Min;
		}
		printf("%u\n", res);
	}
	return 0;
}
