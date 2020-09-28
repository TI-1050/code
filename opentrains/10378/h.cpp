#include <bits/stdc++.h>
using namespace std;

using uint = unsigned int;
using pUI = pair <uint, int>;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 1e3 + 10;
uint H[30]; 
mt19937 rnd(time(0));
int n, m; pII ans[N];
vector <vector<pUI>> vec;
vector <unordered_map<uint, int>> mp;
inline uint getHash(const string &s) {
	uint Hs = 0;
	for (auto &c : s) Hs ^= H[c - 'a']; 
	return Hs; 
}

inline void gets() {
	string s; cin >> s;
	int len = s.size();
	for (int i = 1; i < (1 << len); ++i) {
		string t = "";
		for (int j = 0; j < len; ++j) {
			if ((i >> j) & 1)
				t += s[j];
		}
		mp[t.size()][getHash(t)] = 1; 
	}
}

int main() {
	for (int i = 0; i < 26; ++i) H[i] = rnd(); 
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		vec.clear(); vec.resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			int num; cin >> num;
			vec[i].resize(num);
			for (auto &it : vec[i]) {
				string s; cin >> s;
				it = pUI(getHash(s), s.size());
			}
		}
		memset(ans, -1, sizeof ans);
		cin >> m;
		for (int i = 1; i <= m; ++i) {
			mp.clear(); mp.resize(7);
			int num; cin >> num;
			while (num--) gets(); 
			for (int j = 1; j <= n; ++j) {
				int now = 0;
				for (auto &it : vec[j]) {
					if (mp[it.se].count(it.fi))
						++now;
				}
				if (now > ans[j].fi) {
					ans[j] = pII(now, i);
				}
			}
		}
		for (int i = 1; i <= n; ++i) 
			cout << ans[i].se << "\n";
	}
	return 0;
}
