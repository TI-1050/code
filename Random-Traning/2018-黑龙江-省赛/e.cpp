#include <bits/stdc++.h>
using namespace std;

#define N 5010
char s[N];
bool same (char x, char y) {
	if (x > y) swap(x, y);
	if (y - x <= 26) {
		return false;
	} else if (y - 32 == x) {
		return true;
	}
	return false;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		int res = 0;
		int len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) {
			int l = i, r = i + 1;
			int t = 0;
			while (l >= 1 && r <= len && same(s[l], s[r])) {
				t += 2;
				--l;
				++r;
			}
			res = max(res, t);
		}
		printf("%d\n", res);
	}
	return 0;
}
