#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 100010
#define INF 0x3f3f3f3f

int n, m;
int a[N], l[N], r[N], pre[N], nxt[N];
int need;

ll gao(int L, int R, int c) {
	if (L > R) {
		return 0ll;
	}
	if (L == R) {
		return 1ll;
	}
	if (need > m) {
		return 0ll;
	} 

	int colorL = a[L], colorR = a[R];
	if ((nxt[colorL] >= R && colorR == c)|| (pre[colorR] <= L && colorR == c)) {
		return 0ll;
	}
	ll res = 0;
	if (r[colorL] > R) {
		need = INF;
		return 0ll;
	}
	if (l[colorR] < L) {
		need = INF;
		return 0ll;
	}
	ll needL = r[colorL] - L + 1;
	ll needR = R - l[colorR] + 1;
	res += R - L + 1;
	if (needL < needR) {
		res += gao(L + 1, r[colorL] - 1, colorL) + gao(r[colorL] + 1, R, colorL);
	} else {
		res += gao(L, l[colorR] - 1, colorR) + gao(l[colorR] + 1, R - 1, colorR);
	}
	return res;
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			r[a[i]] = i;
			if (a[i] != a[i - 1]) {
				pre[i] = i - 1;
			} else {
				pre[i] = pre[i - 1];
			}
		}
		a[n + 1] = 0;
		for (int i = n; i >= 1; --i) {
			l[a[i]] = i;
			if (a[i] != a[i + 1]) {
				nxt[i] = i + 1;
			} else {
				nxt[i] = nxt[i + 1];
			}
		}
		need = 0;
		ll res = gao(1, n, 0);
		if (need > m) {
			res = 0;
		}
		printf("%lld\n", res);
	}
	return 0;
}
