#include <bits/stdc++.h>

using namespace std;

int n;

string solve(int n) {
	if (n == 1) return "1";
	if (n == 2) return "1+1";
	if (n == 3) return "1+1+1";
	int tmp = n / 2;
	string s = solve(tmp);
	s = "(" + s + ")*(1+1)";
	if (n & 1) return s + "+1";
	else return s;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n;
		cout << solve(n) << endl;
	}
	return 0;
}
