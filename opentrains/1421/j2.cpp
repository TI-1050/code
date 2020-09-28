#include <bits/stdc++.h>
using namespace std;

void f1(int x) {
	int cnt = 0, sum = 0;
	for (int i = 1; i <= x; ++i) {
		if (x % i == 0) {
			cnt += 2;
			sum += i * x / i;
		}
	}
	cout << cnt / 2 << endl;
}

int main() {
	for (int i = 1; i <= 100; ++i) {
		int cnt = 0;
		for (int j = 1; j <= i; ++j) {
			cnt += (i % j == 0 || (j % (i % j)) == 0);
		}
		printf("%d %d ", i, cnt);
		for (int j = 1; j <= i; ++j) {
			if (i % j == 0 || (j % (i % j)) == 0) {
				cout << j << " ";
			}
		}
		cout << endl;
		//f1(i);
	}
}
