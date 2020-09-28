#include <bits/stdc++.h>
using namespace std;

int y[2], m[2], d[2];
map <string, int> mp;
string ss[10], s;

int main() {
	mp["Monday"] = 1;
	mp["Tuesday"] = 2;
	mp["Wednesday"] = 3;
	mp["Thursday"] = 4;
	mp["Friday"] = 5;
	ss[1] = "Monday";
	ss[2] = "Tuesday";
	ss[3] = "Wednesday";
	ss[4] = "Thursday";
	ss[5] = "Friday";
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> y[0] >> m[0] >> d[0] >> s;
		cin >> y[1] >> m[1] >> d[1];
		int now = mp[s] - 1;
		int add = 0;
		if (d[1] >= d[0]) {
			add += d[1] - d[0];
		} else {
			add += 30 - d[0] + d[1];
		}
		now = (now + add) % 5;
		cout << ss[now + 1] << "\n";
	}
	return 0;
}
