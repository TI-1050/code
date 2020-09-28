#include <bits/stdc++.h>
using namespace std;

#define N 4010
#define pii pair <int, int>
#define fi first
#define se second 
char s[N], t[N];
int n, m;
int f[N][2], g[N][2];
pii dp[N][2];
int pre[N][2]; 

void work(char *s, int **f, int len) {
	int nx[2] = {len, len};
	for (int i = len; i >= 0; --i) {
		f[i][0] = nx[0];
		f[i][1] = nx[1];
		if (i) {
			nx[s[i] - '0'] = i;
		}
	}
}

int main() {
	while (scanf("%s%s", s + 1, t + 1) != EOF) {
		n = strlen(s + 1);
		m = strlen(t + 1);
		work(s, f, n); work(t, g, m);
		int len = max(n, m) + 1;
		for (int i = 1; i <= len; ++i) {
				
		}
	}
	return 0;
}
