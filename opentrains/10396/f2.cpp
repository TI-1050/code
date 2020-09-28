#include <bits/stdc++.h>

using namespace std;

bool f(string s) {
	string t = s;
	reverse(t.begin(), t.end());
	return s == t;
}

int n;
string s;

int check() {
	int len = s.length();
	string t = s;
	reverse(t.begin(), t.end());
	if (s != t) return 1;
	string l = "";
	for (int i = 0; i < len; ++i) {
		string mid = "";
		for (int j = i; j < len; ++j) {
			mid += s[j];
			string r = "";
			for (int k = j + 1; k < len; ++k) {
				r += s[k];
			}
			t = l + r;
			if (!f(mid) && !f(t)) {
				return 2;
			}
		}
		l += s[i];
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	while (cin >> n) {
		cin >> s;
		cout << check() << "\n";
	}	
	return 0;
}
