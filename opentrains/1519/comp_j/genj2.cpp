#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }
int main() {
	int n = 2000, m = 2000;
//	int n = random(1, 15), m = random(1, 15);
	cout << n << " ";
	for (int i = 1; i <= n; ++i) cout << i % 2 + 1 << " \n"[i == n];
	cout << m << " ";
	for (int i = 1; i <= m; ++i) cout << i % 2 + 1 << " \n"[i == m];
	return 0;
}
