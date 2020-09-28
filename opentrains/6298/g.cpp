#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
ll a[N], b[N];
mt19937 rnd(time(0));

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
	//	if (n > 4) {
	//		puts("-1");
	//		continue;
	//	} else {
	//		puts("1112");
	//		continue;
	//	}
		ll mod = 1ll << n;
		a[1] = 1;
		for (int i = 2; i < N; ++i) {
			a[i] = (a[i - 1] * 10) % mod;
		}
		int t = 1;
		b[1] = 2;
		ll now = 2 % mod;
		while (now) {
			if (t >= N - 1) {
				puts("-1");
				break;
			}
		//	int tmp = 2;
			int tmp = rnd() % 2 + 1;
			b[++t] = tmp;
			now = (now + a[t] * tmp % mod) % mod;
		}
		if (t == N - 1) continue;
		reverse(b + 1, b + 1 + t);
		for (int i = 1; i <= t; ++i)
			printf("%d", b[i]);
		puts("");
	}
	return 0;
}
