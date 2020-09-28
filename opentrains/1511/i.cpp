#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		int n; scanf("%d", &n);
		cout << (char)(n % 2 + 'A') << "\n";
	}
	return 0;
}
