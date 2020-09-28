#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	cout << 3 << endl;
	for (int o = 1; o <= 3; ++o) {
		int n = 2e5;
		string s;
		for (int i = 1; i <= n; ++i) s += (rnd() % 26) + 'a';
		cout << s << endl;
		int q = 20000;
		cout << q << endl;
		int j = 0;
		for (int i = 1; i <= q; ++i) {
			for (int k = 0; k < 10; ++k, ++j)
				cout << s[j];
			cout << endl;
		}
	}
	return 0;
}
