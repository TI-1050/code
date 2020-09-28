#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j) 
				if (i == j)	{
					if (n % 2 == 1 && i == (n + 1) / 2) 
						printf("%d %d %d %d\n", (n - j) * 4 + 3, i - 1, (n - j) * 4 + 4, i - 1);
					else if (i <= (n + 1) / 2)
						printf("%d %d %d %d\n", (i - 1) * 4 + 1, j - 1, (i - 1) * 4 + 2, j - 1);
					else printf("%d %d %d %d\n", (n - i) * 4 + 3, i * 2 - n - 1, (n - i) * 4 + 4, i * 2 - n - 1);
				}
				else {
					if (i <= (n + 1) / 2) {
						if (i + j <= n + 1) {
							printf("%d %d %d %d\n", (i - 1) * 4 + 1, j - 1, (i - 1) * 4 + 2, j - 1);
						}
						else {
							printf("%d %d %d %d\n", (n - j) * 4 + 3, i - 1, (n - j) * 4 + 4, i - 1);
						}
					}
					else {
						printf("%d %d %d %d\n", (n - j) * 4 + 3, i - 1, (n - j) * 4 + 4, i - 1);
					}
				}
	}
	return 0;
}
