#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		int need = n / 10;
		ll res = 0;
		while (need--) {
			putchar('1');
			putchar('9');
			res = res * 10 + 1;
			res = res * 10 + 9;
			res %= n;
		}
		putchar(n % 10 + '0');
		puts("");
		res = res * 10 + (n % 10);
		res %= n;
		if (res) {
			cout << " # " << n << " " << res << endl;
		}
	}
	return 0;
}
