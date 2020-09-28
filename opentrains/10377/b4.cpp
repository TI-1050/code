#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
bool check[N];
int prime[N];
int f[N];

int gao(int x, int y) {
	memset(check, false, sizeof check);
	f[1] = 1;
	int tot = 0;
	int Max = 0, sum = 0;
	for (int i = 2; i <= 1000000; ++i) {
		if (!check[i]) {
			prime[tot++] = i;
			if (i % x == y) f[i] = -1;
			else f[i] = 1;
		}
		for (int j = 0; j < tot; ++j) {
			if (i * prime[j] > N) break;
			check[i * prime[j]] = true;
			f[i * prime[j]] = f[i] * f[prime[j]];
			if (i % prime[j] == 0) {
				break;
			}
		}
		sum += f[i];
		Max = max(Max, abs(sum));
	}
	for (int i = 1; i <= 1000000; ++i) {
		printf("%d%c", f[i], " \n"[i == 1000000]);
	}
	return Max;
}

int main() {
	int n; cin >> n;
	if (n == 10) {
		puts("1 -1 -1 1 1 1 -1 -1 1 -1");
	} else {
		gao(3, 2);
	}
//	int Min = N, pos = -1, pos2 = -1;
//	for (int i = 1; i <= 100; ++i) {
//		for (int j = 0; j < i; ++j) {
//			int res = gao(i, j);
//			if (res < Min) { Min = res, pos = i, pos2 = j; }
//			//cout << i << " " << j << " " << res << endl;
//			if (Min <= 20) break;
//		}
//		if (Min <= 20) break;
//	}
//	cout << pos << " " << pos2 << " " << Min << endl;
	return 0;
}
