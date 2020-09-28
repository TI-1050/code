#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k;
char s[N], t[N];
int l[30], r[30], used[30], f[N][30], nx[30], g[N][30], cnt[30];  

bool ok(int x) {
	++used[s[x] - 'a'];
	for (int i = 0; i < 26; ++i) {
		if (g[x][i] < l[i] - used[i]) {
			--used[s[x] - 'a'];
			return 0;
		}
	}
	--used[s[x] - 'a'];
	return 1;
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		for (int i = 0; i < 26; ++i) nx[i] = n + 1, cnt[i] = 0;
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < 26; ++j) {
				f[i][j] = nx[j];
				g[i][j] = cnt[j];
			}
			if (i) {
				++cnt[s[i] - 'a'];
				nx[s[i] - 'a'] = i;
			}
		}
		memset(used, 0, sizeof used);
		scanf("%d", &k);
		int need = 0;
		for (int i = 0; i <= 26; ++i) {
			scanf("%d%d", l + i, r + i);
			need += l[i]; 
		}
		bool F;  
		int it = 0; 
		for (int i = 1; i <= k; ++i) {
			F = 0; 
			for (int j = 0; j <= 26; ++j) {
				if (r[j] > used[j]) {
					if (used[j] >= l[j] && k - i + 1 <= need) continue;
					int Nx = f[it][j];
					if (Nx > n) continue;
					if (ok(Nx)) {
						F = 1;
						t[i] = j + 'a';
						it = Nx;
						++used[j];
						if (used[j] <= l[j]) {
							--need; 
						}
						break;
					}
				}
			}
			if (!F) break;
		}	
		if (!F) puts("-1");
		else {
			t[k + 1] = 0;
			printf("%s\n", t + 1);
		}
	}
	return 0;
}
