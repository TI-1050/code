#include <bits/stdc++.h>
using namespace std;

#define N 200010 
int res[N];

int get(int x) {
	for (int i = 0; i <= 25; ++i) {
		if (((x >> i) & 1) == 0) {
			return (1 << i);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		int fee = 0;
		for (int i = 2; i <= n; ++i) {
			int f = get(i);
			if (f <= n) {
				res[i] = f;
			} else {
				res[i] = 1;
				++fee;
			}
		}
		printf("%d\n", fee);
		for (int i = 2; i <= n; ++i)
			printf("%d%c", res[i], " \n"[i == n]);
	}
	return 0;
}
