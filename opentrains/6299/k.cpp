#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

int n;
int vis[N];
ll res;

void gao(int now, int cur) {
	if (cur == 0) {
		res++;
	} else {
		for (int i = now + 1; i < n; ++i) {
			if (vis[i]) continue;
			if (vis[(i + n - 1) % n] || vis[(i + 1) % n]) continue;
		   	if (n % 2 == 0 && vis[(i + n / 2) % n]) continue;
			vis[i] = 1;
			gao(i + 1, cur - 1);
			vis[i] = 0;
		}
	}
} 

int main() {
	scanf("%d", &n);	
	memset(vis, 0, sizeof vis);
	res = 0;
	vis[1] = 1;
	gao(1, 7);
	res = res * n;
	for (int i = 1; i <= 7; ++i) res = res * i;
	printf("%lld\n", res);
	return 0;
}
