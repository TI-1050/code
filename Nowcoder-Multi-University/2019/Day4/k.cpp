#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
char s[N];
ll f[N][3];

int main() {
	while (scanf("%s", s + 1) != EOF) {
		memset(f, 0, sizeof f);
		int len = strlen(s + 1);
		int cnt = 0;
		ll res = 0;
		for (int i = 1; i <= len; ++i) {
			int num = (s[i] - '0') % 3;
			++f[i][num];
			for (int j = 0; j < 3; ++j) {
				f[i][j] += f[i - 1][(j - num + 3) % 3];  
			}
			cnt += (s[i] == '0');
			if (i >= 2 && s[i] == '0' && s[i - 1] == '0') {
				res += f[i - 2][0] + 1;
			}
		}
		printf("%lld\n", res + cnt);
	}
	return 0;
}
