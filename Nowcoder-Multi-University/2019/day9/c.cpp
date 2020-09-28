#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
int a[N];
int num[N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		a[i] = i;
	}
	do {
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				if (a[i] < a[j]) {
					res++;
				}
			}
		}
		num[res]++;
	} while (next_permutation(a + 1, a + 1 + n));
	for (int i = 0; i <= n * n; ++i) {
		cout << i << " " << num[i] << endl;
	}
	return 0;
}
