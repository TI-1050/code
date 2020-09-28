#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 10;

long long n, p, t, ans, inc;
long long a[N], cnt[N];

int main() {
	scanf("%lld", &n);
	for (int i = 0; i < n; ++i)
		scanf("%lld", &a[i]);
	sort(a, a + n, [&](int x, int y){ return x > y; });
	t = 1, cnt[0] = 1, ans = 0, p = 0, inc = 0;
	for (int i = 1; i <= 20; ++i)
		cnt[i] = cnt[i - 1] * 2;
	while (t < n && a[t] == a[t + 1]) ++t;
	while (t >= cnt[p]) p++;
	p--;
	while (1) {
		if (t < n - 1) {
			if ((a[t] - a[t + 1]) * p > a[0] - a[1] - inc) {
				ans += (a[0] - a[1] - inc) / p * (p + 1) + (a[0] - a[1] - inc) % p;
				break;
			}
			else {
				inc += (a[t] - a[t + 1]) * p;
				ans += (a[t] - a[t + 1]) * (p + 1);
				//printf("%lld %lld %lld\n", ans, t, inc);
				++t;
				if (t > cnt[p]) ++p;
			}
		}
		else {
			ans += (a[0] - a[1] - inc) / p * (p + 1) + (a[0] - a[1] - inc) % p;
			break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
