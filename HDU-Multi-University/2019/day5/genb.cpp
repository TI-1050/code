#include <bits/stdc++.h>
using namespace std;

inline int random(int l, int r) {
	return rand() % (r - l + 1) + l;
}

int main() {
	srand(time(NULL));
	puts("6");
	for (int T = 1; T <= 6; ++T) {
		int n = 100000; printf("%d\n", n);
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", rand(), " \n"[i == n]);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", rand(), " \n"[i == n]);
		}
	}
	return 0;
}
