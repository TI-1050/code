#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll k; string s;

bool ok() {
	ll x = 0;
	for (auto c : s)
		x = x * 2 + c - '0';
	return x <= k;
}

int main() {
	while (cin >> k >> s) {
		int res = 0;
		int one = 0;
		for (auto c : s) one += c == '1';
		while (1) {
			if (ok()) break;
			++res;
			if (one > 1) {
				string t = "";
				t += s[0];
				for (int i = 1, len = s.size(); i < len; ++i) {
					if (s[i] == '1') {
						for (int j = i + 1; j < len; ++j)
							t += s[j];
						break;
					} else t += s[i];
				}
				--one;
				s = t;
			} else s.pop_back();
		}
		cout << res << "\n";
	}
	return 0;
}
