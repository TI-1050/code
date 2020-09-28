#include <bits/stdc++.h>

using namespace std;



int main() {
	srand(time(NULL));
	int n = 100000, k = 0, m = 100000;
	cout << n << " " << k << " " << m << endl;
	for (int i = 1 ; i <= k; ++i) {
		int x = rand() % n + 1, y = rand() % n + 1;
		if (x > y) swap(x, y);
		cout << x << " " << y << endl;
	}
	for (int i = 1 ; i <= m; ++i) {
		int x = rand() % n + 1, y = rand() % n + 1;
		if (x > y) swap(x, y);
		cout << x << " " << y << endl;
	}
	return 0;
}
