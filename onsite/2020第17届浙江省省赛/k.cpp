#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int a[N], b[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) {
			scanf("%d", a + i);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", b + i);
		}
		int n = -1;
		for (int i = 1; i <= m; ++i) {
			if (a[i] * 3 < b[i]) {
				n = i;
				break;
			}
		}
		printf("%d\n", n);
	}
	return 0;
}
