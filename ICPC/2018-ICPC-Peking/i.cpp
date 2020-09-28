#include <bits/stdc++.h>
using namespace std;

int f(int x) {
	int res = 0;
	while (x) {
		res = res * 10 + x % 10;
		x /= 10;
	}
	return res;
}

int main() {
	int cnt = 0;
	for (int i = 0; cnt <= 20000; ++i) {
		if (i == f(i)) {
			cnt++;
			cout << i << endl;
		}
	}
	return 0;
}
