#include <bits/stdc++.h>
using namespace std;

int x, y;
void out(char c) {
	printf("%c\n", c);
	fflush(stdout);
}

int main() {
	int l = 1, r = 1000000000;
	int cnt = 0;
	while (1) {
		++cnt;
		scanf("%d", &y);
		if (cnt >= 101) return 0;
		if (cnt >= 30 && (y >= l && y <= r)) {
			out('=');
			return 0;
		}
		if (y >= l && y <= r) {
			if (r - y + 1 > y - l) {
				out('>');
				l = y + 1;
			} else {
				out('<');
				r = y - 1;
			}
		} else {
			if (y > r) {
				out('<');
			} else {
				out('>');
			}
		}
	}
	return 0;
}
