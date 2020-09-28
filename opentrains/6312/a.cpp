#include <bits/stdc++.h>

using namespace std;

const int N = 2e3 + 10;

char str[N];

int main() {
	while (scanf("%s", str + 1) != EOF) {
		int cnt[2] = {0, 0};
		int n = strlen(str + 1);
		for (int i = 1; i <= n; ++i) {
			cnt[str[i] - '0']++;
		}
		if (cnt[0] != cnt[1]) {
			int now = 0;
			if (cnt[1] < cnt[0]) now = 1;
			for (int i = 1; i <= n; ++i) putchar(now + '0');
			puts("");
		} else {
			int now = str[1] - '0';
			now ^= 1;
			putchar(now + '0');
			now ^= 1;
			for (int i = 2; i <= n; ++i) putchar(now + '0');
			puts("");
		}
	}
	return 0;
}
