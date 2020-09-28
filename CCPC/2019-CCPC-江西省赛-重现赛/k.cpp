#include <bits/stdc++.h>
using namespace std;

int main() {
	int x, y;
	while (cin >> x >> y) {
		int a = (x + y) / 2;
		int b = (x - y) / 2;
		cout << a * b << "\n";
	}
	return 0;
}
