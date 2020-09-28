#include <bits/stdc++.h>
using namespace std;

int n;
vector <string> vec, res;

void input(vector <string> &vec) {
	vec.clear();
	string s;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		vec.push_back(s);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

void get_permutation(vector <string> &res) {
	res.clear();
	string str = "";
	for (int i = 0; i < 10; ++i)
		str += i + '0';
	do {
		res.push_back(str);
	} while (next_permutation(str.begin(), str.end()));
}
int getwee2(int y, int m, int d) {
    int ans;
    if (m == 1 || m == 2) m += 12, y--;
    if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
    } else {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    }
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return ans + 1;
}

int getweek(int y, int m, int d) {
	if (m < 3) {
		y -= 1;
		m += 12;
	}
	int c = y / 100;
	y = y - 100 * c;
	return ((y + y / 4 + c / 4 - 2 * c + (13 * (m + 1)) / 5 + d - 1) % 7 + 7) % 7; 
}

bool isLeap(int y) {
	return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}

int mon[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

bool ok(string s, string mp) {
	int y = (mp[s[0] - 'A'] - '0') * 1000 + (mp[s[1] - 'A'] - '0') * 100 + (mp[s[2] - 'A'] - '0') * 10 + (mp[s[3] - 'A'] - '0');
	int m = (mp[s[5] - 'A'] - '0') * 10 + (mp[s[6] - 'A'] - '0');
	int d = (mp[s[8] - 'A'] - '0') * 10 + (mp[s[9] - 'A'] - '0');
	if (y < 1600) return 0;
	if (m <= 0 || m > 12) return 0;
	if (d <= 0 || d > mon[isLeap(y)][m]) return 0;
	if (getweek(y, m, d) != 5) return 0;
	return 1;
}

void check(string s, vector <string> &vec) {
	vector <string> tmp;
	for (auto it : vec) {
		if (ok(s, it)) {
			tmp.push_back(it);
		}	
	}
	vec = tmp;
}

void solve() {
	for (auto it : vec) {
		check(it, res);
		if (res.empty()) {
			cout << "Impossible\n";
			return;
		}
	}
	sort(res.begin(), res.end());
	cout << res[0] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);  
	int T; cin >> T;
	for (int kase = 1; kase <= T; ++kase) {
		cout << "Case #" << kase << ": ";
		cin >> n;
		input(vec);	
		get_permutation(res);
		solve();
	}
	return 0;
}
