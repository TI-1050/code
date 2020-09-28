#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 110;

int n;
int a, b;
int m[N], t[N];
vector<ll> vec;
map<ll, int> mp;

int main() {
	while (scanf("%d %d %d", &n, &a, &b) != EOF) {
		vec.clear();
		mp.clear();
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", m + i, t + i);
			m[i] = b * m[i] - a * t[i];
		}
		int half = n >> 1, nhalf = n - half;
		for (int S = 1; S < (1 << half); ++S) {
			ll sum = 0;
			for (int i = 0; i < half; ++i) {
				if (S & (1 << i)) {
					sum += m[i];
				}
			}
			vec.push_back(sum); 
		}
		for (int S = 1; S < (1 << nhalf); ++S) {
			ll sum = 0;
			for (int i = 0; i < nhalf; ++i) {
				if (S & (1 << i)) {
					sum += m[i + half];
				}
			}
			mp[sum]++;
		}
		ll res = mp[0];
		for (auto &it : vec) {
			if (it == 0) ++res;
			if (mp.find(-it) != mp.end()) {
				res += mp[-it];
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
