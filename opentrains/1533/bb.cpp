#include <bits/stdc++.h>
using namespace std;

#define N 5010
#define pii pair <int, int>
#define fi first
#define se second
map <int, int> vs[N];
int n;
int a[N], b[N], c[N];
map <int, int> mp; 

int main() {
	while (scanf("%d", &n) != EOF) {
		mp.clear();
		for (int i = 1; i <= n; ++i) vs[i].clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			mp[a[i]] = i;  
		}		
		int res = 2;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				vs[j][a[j] - a[i]] = max(vs[j][a[j] - a[i]], 2); 
			}
			for (auto it : vs[i]) {
				res = max(res, it.se);
				auto nx = mp.find(a[i] + it.fi);
				if (nx != mp.end()) {
					int pos = nx->se;
					vs[pos][it.fi] = max(vs[pos][it.fi], it.se + 1);  
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
