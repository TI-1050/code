#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
#define INF 0x3f3f3f3f
int n, a[N];
ll sum[N];
int Sta[N], top;
int f[N], g[N];

ll work1() {
	a[0] = a[n + 1] = -INF;
	top = 0;
	Sta[++top] = 0;
	for (int i = 1; i <= n; ++i) {
		while (a[i] < a[Sta[top]]) {
	//		cout << a[i] << " " << a[Sta[top]] << endl;
			--top;
		}
		f[i] = Sta[top];
		Sta[++top] = i;
	}

	top = 0;
	Sta[++top] = n + 1;
	for (int i = n; i >= 1; --i) {
		while (a[i] < a[Sta[top]]) {
			--top;
		}
		g[i] = Sta[top];
		Sta[++top] = i;
	}

	ll res = 0;
	for (int i = 1; i <= n; ++i) {
//		printf("%d %d %d %lld\n", i, f[i], g[i], (sum[g[i] - 1] - sum[f[i]]) * a[i]);
		res = max(res, (sum[g[i] - 1] - sum[f[i]]) * a[i]);
	}
	return res;
}

ll work2() {
	a[0] = a[n + 1] = INF;
	for (int i = 1; i <= n; ++i) {
		a[i] = -a[i];
	}
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + a[i];
	}
	top = 0;
	Sta[++top] = 0;
	for (int i = 1; i <= n; ++i) {
		while (a[i] > a[Sta[top]]) {
			--top;
		}
		f[i] = Sta[top];
		Sta[++top] = i;
	}

	top = 0;
	Sta[++top] = n + 1;
	for (int i = n; i >= 1; --i) {
		while (a[i] > a[Sta[top]]) {
			--top;
		}
		g[i] = Sta[top];
		Sta[++top] = i;
	}

	ll res = 0;
	for (int i = 1; i <= n; ++i) {
	//	printf("%d %d %d %lld\n", i, f[i], g[i], (sum[g[i] - 1] - sum[f[i]]) * a[i]);
		res = max(res, (sum[g[i] - 1] - sum[f[i]]) * a[i]);
	}
	return res;

}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + a[i];
		}
		ll res = work1();
		res = max(res, work2());
		printf("%lld\n", res);
	}
	return 0;
}
