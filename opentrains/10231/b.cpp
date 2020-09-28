#include <bits/stdc++.h>
using namespace std;

#define N 30

int n, k;
string s[N];
int ans;

//B 1 W 0
int judge(string engin, vector<int> res) {
	for (int i = engin.size() - 1, j = res.size() - 1; i >= 0 && j >= 0; --i, --j) {
		if (engin[i] == 'B' && res[j] == 0) {
			return 1;
		}
		if (engin[i] == 'W' && res[j] == 1) {
			return 0;
		}
	}
	return 0;
}

void DFS(int cur, int pos, int cnt, vector<int> res) {
	if (cur >= k) {
		ans = max(ans, cnt);
		return ;
	}
	for (int i = 1; i + cur <= k && i <= 2; ++i) {
		string tmp = s[pos];
		vector<int> temp = res;
		int tmpcnt = cnt;
		for (int j = 1; j <= i; ++j) {
			int nxt = judge(s[pos], temp);
			temp.push_back(nxt);
			s[pos].push_back(nxt ? 'W' : 'B');
			if (nxt == 0) {
				tmpcnt++;
			}
		}
		DFS(cur + i, pos % n + 1, tmpcnt, temp);
		s[pos] = tmp;
	}
}

int main() {
	freopen("checkers.in", "r", stdin);
	freopen("checkers.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n >> k) {
		for (int i = 1; i <= n; ++i) {
			cin >> s[i];
		}
		ans = 0;
		vector<int> res;
		DFS(0, 1, 0, res);
		cout << ans <<"\n";
	}
	return 0;
}
