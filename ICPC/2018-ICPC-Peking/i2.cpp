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

int g(int x) {
	int res = 0;
	while (x) {
		res++;
		x /= 10;
	}
	return res;
}

int main() {
	int lst = 0;
	int cnt = 0;
	for (int i = 0; cnt <= 20000; ++i) {
		if (i == f(i)) {
			cnt++;
			if (g(i) != lst) {
				cout << cnt << " " << g(i) << endl;
				lst = g(i);
			}
		}
	}
	return 0;
}
