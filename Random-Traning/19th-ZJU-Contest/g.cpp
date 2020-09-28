#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, k, Max;
vector <int> vec[2];
ll f(vector <int> &v) {
	if (v.empty()) {
		return 0;
	}
	sort(v.begin(), v.end());
	ll tot = 0;
	while (!v.empty()) {
		tot += 2 * v.back();
		int t = k;
		while (t-- && !v.empty()) {
			v.pop_back();
		}
	}
	return tot;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		vec[0].clear(); vec[1].clear(); Max = 0;
		scanf("%d%d", &n, &k);
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x == 0) {
				continue;
			} else if (x < 0) {
				vec[0].push_back(-x); 
				Max = max(Max, -x);
			} else {
				vec[1].push_back(x);
				Max = max(Max, x);
			}
		}
		ll res = f(vec[0]) + f(vec[1]) - Max;
		printf("%lld\n", res);
	}
	return 0;
}
