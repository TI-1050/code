#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int n, a[N];

void gao() {
	int num = 0;
	for (int i = 1; i <= n; ++i) {
		num = max(num, a[i] / 100);
		a[i] %= 100;
		if(a[i] % 10) {
			puts("-1");
			return;
		}
	}
	sort(a + 1, a + 1 + n);
	n = unique(a + 1, a + 1 + n) - a - 1;
	memset(b, 0, sizeof b);
	int five = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] >= 50) {
			five = 1;
			a[i] -= 50;
		}
		b[a[i]] = 1;
	}
	num += five;
	if (b[40] && (b[10] || b[30])) {
		num += 3;
	} else if (b[10] + b[20] + b[30] + b[40] == 1) {
		if (b[10] || b[20]) num += 1;
		else num += 2;
	} else {
		num += 2;
	}
	printf("%d\n", num);
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		gao();
	}
	return 0;
}
