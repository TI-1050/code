#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
int n, m, t[N], a[N]; ll f[N]; 
int que[N], head, tail;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d%d", t + i, a + i);
		reverse(a + 1, a + 1 + n);
		reverse(t + 1, t + 1 + n);
		m = 1;
		for (int i = 2; i <= n; ++i) {
			if (a[i] > a[m]) {
				++m;
				a[m] = a[i];
				t[m] = t[i];  
			}
		}
		reverse(a + 1, a + 1 + m);
		reverse(t + 1, t + 1 + m);
		n = m; 
		head = 1, tail = 0;
		ll Min = a[1] * 2; 
		int bored = 0; a[n + 1] = 0;
		for (int i = 1; i <= n; ++i) {
			while (bored < i - 1 && f[bored + 1] <= t[i]) { 
				++bored;
				Min = min(Min, 2ll * a[bored + 1]); 
			}
			while (head <= tail && que[head] <= bored) ++head;
			f[i] = Min + t[i];
			if (head <= tail) f[i] = min(f[i], f[que[head]] + 2ll * a[que[head] + 1]);
			if (i == n) break;
			while (head <= tail && f[i] + 2ll * a[i + 1] <= f[que[tail]] + 2ll * a[que[tail] + 1]) --tail;
			que[++tail] = i;
		}
		printf("%lld\n", f[n]);
	}
	return 0;
} 
