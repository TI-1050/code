#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 1e6 + 10, ALP = 26;
char s[N], t[N];
int n, m, f[N];  
vector <vector<int>> vec;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%s%s", s + 1, t + 1);
		n = strlen(s + 1), m = strlen(t + 1);
		vec.clear(); vec.resize(ALP + 1);
		for (int i = 1; i <= n; ++i) vec[s[i] - 'a'].push_back(i);
		memset(f, 0x3f, sizeof (f[0]) * (m + 10)); f[0] = 0;
		for (int i = 1; i <= m; ++i) {
			int ch = t[i] - 'a';
			for (int j = m - 1; j >= 0; --j) {
				if (f[j] > n) continue;
				auto pos = upper_bound(vec[ch].begin(), vec[ch].end(), f[j]);
				if (pos != vec[ch].end()) {
					f[j + 1] = min(f[j + 1], *pos);
				}
			}
		}
		int res = 0; 
		for (int i = m; i >= 1; --i) if (f[i] <= n) {
			res = i;
			break;
		}
		printf("%d\n", res);
	}
	return 0;
}
