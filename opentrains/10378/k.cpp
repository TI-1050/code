#include <bits/stdc++.h>

using namespace std;


int find(int t) {
	int x = t, y = 1;
	while (x % 2 == 0) {
		x = x / 2;
		y = y * 2;
	}
	return x * x / 2 * y;
}

int main() {
	int n;
	scanf("%d", &n);
	if (n == 3) {
		printf("0 0\n4 3\n-20 21\n");
	}
	else if (n == 4) {
		printf("0 3\n4 0\n0 -3\n-4 0\n");
	}
	else if (n % 2 == 0) {
		int x = 0, y = 0;
		printf("3 -4\n");
		for (int i = 1; i <= (n / 2) - 2; ++i) {
			printf("%d %d\n", x, y);
			if (i % 2 == 0) 
				x += 4 ,y +=3;
			else x += 3, y += 4;
		}
		for (int i = (n / 2) - 1; i <= n - 4; ++i) {
			printf("%d %d\n", x, y);
			if (i % 2 == 0) 
				x += 3, y -= 4;
			else x += 4, y -= 3;
		}
		printf("%d 0\n%d -4\n", x, x + 3);
		int t = find(x / 2);
		printf("%d %d\n", x + 3 - x / 2, -4 - t);
	}
	else {
		int x = 0, y = 0;
		printf("0 0\n");
		for (int i = 1; i <= (n - 3) / 2; ++i) {
			if (i % 2 == 1) 
				x -= 4, y += 3;
			else x -= 3, y += 4;
			printf("%d %d\n", x, y);
		}
		for (int i = (n - 3) / 2 + 1; i <= n - 3; ++i) {
			if (i % 2 == 1)
				x += 3, y += 4;
			else x += 4, y += 3;
			printf("%d %d\n", x ,y);
		}
		int t = find(y / 2);
		printf("%d 0\n%d %d\n", t * 2, t , - (y / 2));
	}
	return 0;
}
