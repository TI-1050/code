#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }
int main() {
	int n = random(1, 6);
	cout << n << endl;
	for (int i = 2; i <= n; ++i)
		cout << i << " " << random(1, i - 1) << endl;
}
