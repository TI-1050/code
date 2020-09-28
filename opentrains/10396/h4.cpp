#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while(0)
void err() { cout << "\033[39;0m" << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); } 
using ll = long long;
const int N = 2e5 + 10;
int n, m, k, d, a[N], c[N], vis[N];
map<int, int> mp;
set <int> se;

int main() {
	while (scanf("%d%d%d%d", &n, &m, &k, &d) != EOF) {
		for (int i = 1; i <= m; ++i) scanf("%d", c + i);
		for (int i = 1; i <= k; ++i) scanf("%d", a + i);
		sort(c + 1, c + 1 + m);
		sort(a + 1, a + 1 + k);
		mp.clear(); se.clear(); 
		for (int i = 1; i <= k; ++i) mp[a[i]] = i, se.insert(a[i]);
		int way = 0;
		memset(vis, 0, sizeof vis);
		vector <int> vec;
		for (int i = 1; i <= k; ++i) {
			if (vis[i]) continue;
			if (a[i] - 1 > d) continue; 
			int it = a[i]; 
			vec.clear();
			vec.push_back(i);
			se.erase(it);  
			while (it + d < n && !se.empty()) { 
				auto pos = se.upper_bound(it + d); 
			    if (pos == se.begin()) break;
				--pos;
				if (*pos > it) {
					vec.push_back(mp[*pos]);
					it = *pos;
					se.erase(*pos);
				} else break;
				if (it + d >= n) break; 
			}
			if (it + d >= n) {
				++way;
				for (auto &it : vec) {
					vis[it] = 1;
				}
			} else {
				for (auto &it : vec) if (it != i)
					se.insert(a[it]);
			}
		}
		if (d >= n - 1) way = m; 
		ll res = 0;
		if (way > 0) {
			res = 0;
			int need = m - way;
			for (int i = 1; i <= need; ++i) res += c[i]; 
		} else {
			int need = 0; 
			a[0] = 1; a[k + 1] = n;
			for (int i = 1; i <= k + 1; ++i) {
				if (a[i - 1] + d < a[i]) {
					++need;
				}
			}	
			res = 1ll * c[1] * need;
			for (int i = 2; i <= m; ++i) res += c[i]; 	
		}
		printf("%lld\n", res);
	}
	return 0;
}

