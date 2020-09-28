#include <bits/stdc++.h>
using namespace std;

void out(int x, int n) {
	for (int i = 1; i <= n; ++i)
		printf("%d", x);
	puts("");
}

int main() {
	int n, d;
	while (scanf("%d%d", &n, &d) != EOF) {
		if (d == 9) {
			if (n % 8) printf("%d", n % 8);
			out(8, n / 8);
		} else {
			if (n % 9 == d) {
				if (d == 0) {
					out(9, n / 9);
				} else if (d == 1) {
					printf("2");
					if (n / 9) printf("8");
					out(9, n / 9 - 1);
				} else {
					if (n / 9 == 0) {
						printf("1%d\n", d - 1);
						continue;
					}
					if (d == 8) {
						printf("17");
						out(9, n / 9);
						continue;
					}
					printf("%d", d + 1);
					printf("8"); 
					out(9, n / 9 - 1);
				}
			} else {
				if (n % 9) printf("%d", n % 9);
				out(9, n / 9);
			}
		}
	}
	return 0;
}
