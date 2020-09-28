#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	while (cin >> s) {
		string res = "\"";
		res += s;
		res += "\", ";
		cout << res;
	}
	return 0;
}
