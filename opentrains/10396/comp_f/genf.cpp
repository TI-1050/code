#include <bits/stdc++.h>

using namespace std;

int main() {
	int n = rand() % 10 + 1;
	string s = "";
	for (int i = 0; i < n; ++i) {
		s += rand() % 4 + 'a';
	}
	string t = s;
	reverse(t.begin(), t.end());
	s += t;
	cout << s.size() << endl;
	cout << s << endl;
	return 0;
}
