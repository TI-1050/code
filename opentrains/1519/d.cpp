#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
char s[N]; int sta[N], n;

void add(int ch) {
	sta[++*sta] = ch;
	if (*sta >= 5) {
		int a = sta[*sta], b = sta[*sta - 1];
		if (sta[*sta] == sta[*sta - 2] && sta[*sta] == sta[*sta - 4] && sta[*sta - 1] == sta[*sta - 3] && sta[*sta] != sta[*sta - 1]) {
			*sta -= 5;
			add(b);
			add(a);
			add(b);
		}
	}
	if (*sta >= 2 && sta[*sta] == sta[*sta - 1]) *sta -= 2;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		*sta = 0; n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) {
			add(s[i] - 'a');
		}
		if (*sta) puts("open");
		else puts("closed");
	}
	return 0;
}
