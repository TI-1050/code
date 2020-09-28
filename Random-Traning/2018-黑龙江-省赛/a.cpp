#include <bits/stdc++.h>
using namespace std;

int main() {
	string s = "", t = "a"; 
	char c = 'b';
	while (1) {
		s += t;
		if ((int)s.size() >= 10000) {
			break;
		}
		t += c;
		if (c == 'z') {
			c = 'a';
		} else {
			++c;
		}
	}
	int T; cin >> T;
	while (T--) {
		int n;
		scanf("%d", &n);
		printf("%c\n", s[n - 1]);
	}
	return 0;
}
