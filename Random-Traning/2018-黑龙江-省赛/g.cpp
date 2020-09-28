#include <bits/stdc++.h>
using namespace std;

int main() {
	int T; cin >> T;
	while (T--) {
		int p, m;
		scanf("%d%d", &p, &m);
		--p;
		if (p % (m + 1) == 0) {
			puts("Bob");
		} else {
			puts("Alice");
		}
	}
	return 0;
}
