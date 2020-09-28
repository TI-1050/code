#include <bits/stdc++.h>

using namespace std;

const int N = 110;
const int INF = 0x3f3f3f3f;

struct node {
	string s;
	int v;

	node() {}

	node(string s, int v): s(s), v(v){}

	bool operator < (const node &other) const {
		return s < other.s;
	}
};

int n;
string str[N];
vector<node> vec[2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) {
			cin >> str[i];
		}
		for (int i = 1; i <= n; ++i) {
			int now = i & 1;
			int pre = now ^ 1;
			vec[now].clear();
			if (i == 1) {
				int len = str[i].length();
				int limit = 1 << len;
				for (int S = 1; S < limit; ++S) {
					string tmp = "";
					for (int j = 0; j < len; ++j) {
						if (S & (1 << j)) {
							tmp += str[i][j];
						}
					}
					vec[now].push_back(node(tmp, tmp.size()));
				}
				sort(vec[now].begin(), vec[now].end());
			} else {
				int len = str[i].length();
				int limit = 1 << len;
				for (int S = 1; S < limit; ++S) {
					string tmp = "";
					for (int j = 0; j < len; ++j) {
						if (S & (1 << j)) {
							tmp += str[i][j];
						}
					}
					vec[now].push_back(node(tmp, 0));
				}
				sort(vec[now].begin(), vec[now].end());
				int Max = -INF;
				int p = 0;
				int sze = vec[pre].size();
				for (int j = 0; j < limit; ++j) {
					while (p < sze && vec[pre][p].s < vec[now][j].s) {
						Max = max(Max, vec[pre][p].v);
						++p;
					}
					vec[now][j].v = Max + vec[now][j].s.length();
				}
			}
		}
		int res = -1;
		for (auto &it : vec[n & 1]) {
			res = max(res, it.v);
		}
		cout << res << "\n";
	}
	return 0;
}
