#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 2e6 + 10;

int n, m;
ll a[N], res[N];
multiset<ll> s, s1;
vector<ll> vec;

inline void RUN() {
	s.clear();
	s1.clear();
	for (int i = 1; i <= m; ++i) {
		s.insert(a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (s.empty()) {
			puts("NO");
			return ;
		}
		ll v = *s.begin();
		vec.clear();
		for (auto &it : s1) {
			vec.push_back(v + it);
		}
		vec.push_back(v);
		for (auto &it : vec) {
			if (s.find(it) == s.end()) {
				puts("NO");
				return ;
			} else {
				s.erase(s.lower_bound(it));
			}
			s1.insert(it);
		}
		res[i] = v;
	}
	for (int i = 1; i <= n; ++i) {
		printf("%lld%c", res[i], " \n"[i == n]);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		m = (1 << n) - 1;
		for (int i = 1; i <= m; ++i) {
			scanf("%lld", a + i);
		}
		RUN();
	}	
	return 0;
}
