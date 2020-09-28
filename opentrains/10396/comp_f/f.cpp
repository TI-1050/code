#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, len; string s, t;

bool ispar() {
	t = s;
	reverse(t.begin(), t.end());
	return s == t;	
}

bool ok() {
	for (int i = 1; i < len; ++i)
		if (s[i] != s[i - 1])
			return false;
	return true;
}

bool ok2() {
	if (ispar()) {
		if (len % 2 != 1) return false;
		int mid = len / 2;
		for (int i = 1; i < mid; ++i)
			if (s[i] != s[i - 1]) 
				return false;
		for (int i = mid + 2; i < len; ++i)
			if (s[i] != s[i - 1])
				return false;
	} else {
		return false;
	}
	return true;
}

bool ok3() {
	if (len % 2 == 1) {
		for (int i = 2; i < len; ++i)
			if (s[i] != s[i - 2])
				return false;
	} else 
		return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		cin >> s; len = s.size();
		if (len == 1) {
			cout << -1 << "\n";
			continue;
		}
		if (!ispar()) cout << 1 << "\n";
		else {
			if (ok() || ok2() || ok3()) cout << -1 << "\n";
			else cout << 2 << "\n";
		}
	}
	return 0;
}
