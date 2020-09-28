#include <bits/stdc++.h>
using namespace std;

const int N = 110 + 10;
int n, q, x[N], y[N];
mt19937 rnd(time(0));
int main() {
	int n = 10;
	cout << n << endl;
	for (int i = 1; i <= n; ++i) cout << rnd() % 10 + 1 << " " << rnd() % 10 + 1 << endl;
	int q = 5; cout << q << endl;
	while (q--) {
		cout << rnd() % 10 + 1 << " " << rnd() % 10 + 1 << " " << rnd() % 10 + 1 << endl;
	}
}
