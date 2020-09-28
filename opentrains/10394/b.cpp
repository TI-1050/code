#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pII = pair<int, int>;
#define fi first
#define se second
int f[110][110];
pII gao(ll x) {
	pII res = pII(0, 0);
	while (x) {
		++res.fi;
		res.se += x % 2;
		x /= 2;
	}
	return res;
}

int main() {
	memset(f, 0, sizeof f);
	for (int i = 1; i <= 1000000000; ++i) {
		ll x = 1ll * i * i;
		pII t = gao(x);
		++f[t.fi][t.se];
	}
	for (int i = 0; i <= 70; ++i) {
		printf("{");
		for (int j = 0; j <= 70; ++j) {
			printf("%d%c", f[i][j], ",}"[j == 70]);
		}
		printf(",\n");
	}
	return 0;
}
