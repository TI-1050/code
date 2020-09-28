#include <bits/stdc++.h>
using namespace std;

#define N 5010
#define pii pair <int, int>
#define fi first
#define se second
int n, m, a[N], b[N], del[N];   
pii _a[N];

int f(int j) {
	int tot = 0;
	for (int i = 1, k = 1; i <= n; ++i) if (del[_a[i].se] == 0) {
		while (k <= m && (b[k] <= _a[i].fi || k == j)) {
			++k;
		} 
		if (k <= m) {
			++k;
			++tot;
		} else {
			break;
		}
	}
	return tot;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(del, 0, sizeof del);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			_a[i].fi = a[i];
			_a[i].se = i;    
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);  
		}
		m = n;
		int sum = 0, tot = 0;
		sort(_a + 1, _a + 1 + n);   
		sort(b + 1, b + 1 + n);
		sum = f(n + 1); 
		vector <int> res;
		for (int i = 1, j; i <= n; ++i) {
			for (j = 1; j <= m; ++j) {
				if (b[j] > a[i]) {
					break;
				}
			}
			del[i] = 1;
			bool F = 0;
			if (j <= m) {
				int l = j, r = m, pos = -1;
				while (r - l >= 0) {
					int mid = (l + r) >> 1;
					if (tot + 1 + f(mid) == sum) {
						l = mid + 1;
						pos = mid;	
					} else {
						r = mid - 1;
					}
				}	
				if (pos != -1) {
					res.push_back(b[pos]);
					F = 1;
					++tot;
					int t = m; m = 0;
					for (int j = 1; j <= t; ++j) {
						if (j != pos) {
							b[++m] = b[j]; 
						}
					} 
				}
			}
			//[j, m]中没有合适的b
			if (!F) {
				int l = 1, r = j - 1, pos = -1;
				while (r - l >= 0) {
					int mid = (l + r) >> 1;
					if (tot + f(mid) == sum) {
						l = mid + 1;
						pos = mid;	
					} else {
						r = mid - 1;
					}
				}
				assert(pos != -1);
				res.push_back(b[pos]);
				int t = m; m = 0;
				for (int j = 1; j <= t; ++j) {
					if (j != pos) {
						b[++m] = b[j];
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			printf("%d%c", res[i], " \n"[i == n - 1]);
		}
	}
	return 0;
}
