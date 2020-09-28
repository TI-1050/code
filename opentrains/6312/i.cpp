#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
char str[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", str);
			if (str[0] == 'L') ++cnt;
		}
		puts((cnt & 1) ? "LIE" : "TRUTH");
	}
	return 0;
}
