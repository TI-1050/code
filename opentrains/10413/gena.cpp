#include <bits/stdc++.h>

using namespace std;

int main() {
	int d = 1, n = 500000;
	cout << d << " " << n << " " << n << " " << n << endl;
	for (int cas = 1; cas <= 3; ++cas) {
		for (int i = 1; i <= n; ++i) {
			cout << 1 << " \n"[i == n];
		}
	}
	return 0;
}
