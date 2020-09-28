#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f
#define N 5010
int n, m;
char s[N], t[N];
vector<vector<int>> work(char *s) {
	int len = strlen(s + 1);
	vector <vector<int>> f(len + 3);
	vector <int> nx(2, len + 1);
	f[len + 1] = nx; 
	f[len + 2] = nx;
	for (int i = len; i >= 0; --i) {  
		f[i] = nx;
		if (i) {
			nx[s[i] - '0'] = i;
		}
	}
	return f;
}

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		vector <vector<int>> f = work(s), g = work(t);
		n = strlen(s + 1), m = strlen(t + 1);
		vector <vector<int>> dp(n + 3, vector <int> (m + 3, INF));
		// dp[i][j] 表示匹配到i, j的最短长度 
		vector <vector<bool>> ok(n + 3, vector <bool> (m + 2, 0));     
		dp[0][0] = 0;
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= m + 1; ++j) {
				for (int k = 0; k <= 1; ++k) { 
					int _i = f[i][k];
					int _j = g[j][k];      
					dp[_i][_j] = min(dp[_i][_j], dp[i][j] + 1);
				}
			}
		}
		ok[n + 1][m + 1] = 1;
		for (int i = n + 1; i >= 0; --i) {
			for (int j = m + 1; j >= 0; --j) {
				for (int k = 0; k <= 1; ++k) {
					int _i = f[i][k];
					int _j = g[j][k];
					if (dp[_i][_j] == dp[i][j] + 1 && ok[_i][_j]) {
						ok[i][j] = 1;
					}
				}
			}
		}
		string res = "";
		int i = 0, j = 0;
		while (i < n + 1 || j < m + 1) {
			for (int k = 0; k < 2; ++k) {
				int _i = f[i][k];
				int _j = g[j][k];
				if (dp[_i][_j] == dp[i][j] + 1 && ok[_i][_j]) {
					res.push_back(k + '0');
					i = _i;
					j = _j;
					break;
				}
			}
		}
		cout << res << "\n";
	}
	return 0;
}
