#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char s[N]; int n;

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		int res = 0, f = 0, g = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 'L') ++g;
			else --g;
			f = max(f, g);
		}
		res += f; f = 0, g = 0;
		for (int i = n; i >= 1; --i) {
			if (s[i] == 'R') ++g;
			else --g;
			f = max(f, g);
		}
		res += f;
		printf("%d\n", res);
	}
	return 0;
}
