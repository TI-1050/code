#include <bits/stdc++.h>
using namespace std;

mt19937 rd(time(0));
int main() {
	int n = 50000; cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		string s = "";
		for (int j = 0; j < 5; ++j)
			s += rd() % 75 + 48;
		cout << s << endl;
	}
	return 0;
}
