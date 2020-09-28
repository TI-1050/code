#include <bits/stdc++.h>
using namespace std;

#define N 200010
char s[N];
int n;
int cnt[10]; 
int mp[220];

int main() {
	mp['x'] = 1;
	mp['t'] = 2;
	mp['C'] = 3;
	mp['p'] = 4;
	mp['c'] = 5;
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		memset(cnt, 0, sizeof cnt);
		for (int i = n; i >= 1; --i) {
			char ch = s[i];
			int x = mp[ch];
			if (x == 0) {
				continue;
			}
			if (x == 5) {
				++cnt[5];
			}
			if (cnt[x + 1]) {
				--cnt[x + 1];
				++cnt[x];
			}
		}
		printf("%d\n", cnt[1]);
	}
	return 0;
}
