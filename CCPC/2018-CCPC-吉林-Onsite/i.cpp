#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		multiset <int> s; 
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			s.insert(x);
		}
		ll res = 0;
		while ((int)s.size() > 1) {
			int x = *s.rbegin();
			//cout << x << endl;
			s.erase(s.lower_bound(*s.rbegin()));
			vector <int> vec; 
			while (x && !s.empty()) {
				int y = *s.rbegin();
				if (y > 1) {
					vec.push_back(y - 1);
				}
				s.erase(s.lower_bound(y)); 
				--x;
			}
			for (auto it : vec) {
				s.insert(it);
			}
			res += x;
		}
		if (!s.empty()) {
			res += *s.begin();
		}
		printf("%lld\n", res); 
	}
	return 0;
}
