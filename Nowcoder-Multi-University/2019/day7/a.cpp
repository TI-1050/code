#include <bits/stdc++.h>
using namespace std;

#define N 210
int n;
string s;
vector <string> res;

int minRep(string s) {
	int len = s.size();
	int i = 0, j = 1, k = 0;
	while (i < len && j < len && k < len) {
		int t = s[(i + k) % len] - s[(j + k) % len];
		if (!t) ++k;
		else {
			if (t > 0) i += k + 1;
			else if (t < 0) j += k + 1;
			if (i == j) j = i + 1;
			k = 0;
		}
	//	printf("%d %d %d\n", i, j, k);
	}
	return min(i, j);
}

int ok(string s) {
	string t = s;
	s += t;
	if (minRep(s) == 0) return 1;
	return 0;
}

void solve(string s) {
	int len = s.size();	
	string t = "";
	for (int i = len; i >= 1; --i) {
		if (ok(s)) {
			res.push_back(s);
			reverse(t.begin(), t.end());
			solve(t);
			return;
		} else {
			t += s[i - 1];
			s.pop_back();
		}
	}
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--) {
		cin >> s;
		res.clear();
		solve(s); 
		for (int i = 0, sze = (int)res.size(); i < sze; ++i) {
			cout << res[i] << " \n"[i == sze - 1];
		}
	}
	return 0;
}
