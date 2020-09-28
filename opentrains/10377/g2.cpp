#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char s[N]; int n;

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		int res = 0, l = 0, r = n + 1;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 'R') {
				break;
			}
			l = i; 
			++res;
		}
		for (int i = n; i >= 1; --i) {
			if (s[i] == 'L') {
				break;
			}
			r = i;
			++res;
		}
		if (l + 1 < r) ++res;
		printf("%d\n", res);
	}
	return 0;
}
