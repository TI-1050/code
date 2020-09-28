#include <bits/stdc++.h>
using namespace std;

int main() {
	int s;
	while (scanf("%d", &s) != EOF) {
		if (s <= 2) printf("%d\n", s);
		else {
			if (s % 3 == 0) {
				for (int i = 1; i <= s / 3; ++i)
					printf("21");
				puts("");
			} else if (s % 3 == 1) {
				s -= 1;
				for (int i = 1; i <= s / 3; ++i)
					printf("12");
				puts("1");
			} else {
				s -= 2;
				for (int i = 1; i <= s / 3; ++i)
					printf("21");
				puts("2");
			}
		}
	}
	return 0;
}
