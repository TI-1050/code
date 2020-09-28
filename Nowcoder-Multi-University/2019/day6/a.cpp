#include <bits/stdc++.h>
using namespace std;

#define N 2010
char s[N], t[N], mp[N];

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%s%s", s + 1, t);
		for (int i = 0; i < 26; ++i) {
			mp['a' + i] = t[i];
		}
		int d = 0, w = 0, h = 0;
		int len = strlen(s + 1);
		for (int i = 1; i <= len; ++i) {
			int c = mp[s[i]];
			if (c == 'w') ++w;
			else if (c == 'd') ++d;
			else ++h;
		}
		if (h * 4 >= len) {
			puts("Harmful");
		} else if (h * 10 <= len) {
			puts("Recyclable");
		} else if (d >= w * 2) {
			puts("Dry");
		} else {
			puts("Wet");
		}
	}
	return 0;
}
