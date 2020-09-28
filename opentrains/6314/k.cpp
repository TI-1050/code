#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int n, m;
char a[N], b[N], res[N];

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		scanf("%s", a);
		scanf("%s", b);
		res[m] = 0;
		for (int i = m - 1, j = n - 1; j >= 0; --i, --j) {
			res[i] = a[j];
		}
		for (int i = m - n - 1; i >= 0; --i) {
			res[i] = ((b[i + n] - 'a') - (res[i + n] - 'a') + 26) % 26 + 'a';
		}
		puts(res);
	}
	return 0;
}
