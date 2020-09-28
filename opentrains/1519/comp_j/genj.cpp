#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }
int main() {
	int n = random(1, 20), m = random(1, 20);
	cout << n << " ";
	for (int i = 1; i <= n; ++i) cout << random(-10, 10) << " \n"[i == n];
	cout << m << " ";
	for (int i = 1; i <= m; ++i) cout << random(-10, 10) << " \n"[i == m];
	return 0;
}
