#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 1010, M = 2010;
int n, m;
vector <bitset<M>> f;
vector <pII> res;
inline void NO() { puts("No"); }
void get() {
	for (int x = 1; x <= n; ++x) {
		for (int y = 1; x * y <= n && x + y <= m; ++y) {
			if (f[n - x * y][m - x - y] == 1) {
				res.push_back(pII(x, y));
				n -= x * y, m -= x + y;		
				return;		
			}
		}
	}
}

void gao() {
	if (m % 2) return NO();
	m /= 2;
	if (!f[n][m]) return NO();
	puts("Yes");
	res.clear();
	while (n) get();
	int sze = res.size();
	printf("%d\n", sze);
	for (int i = 0; i < sze; ++i)
		printf("%d %d\n", res[i].fi, res[i].se);
}

int main() {
	f.clear(); f.resize(N);
	f[0][0] = 1;
	for (int i = 0; i < N; ++i) {
		for (int x = 1; i + x < N; ++x) {
			for (int y = 1; i + x * y < N; ++y) {
				f[i + x * y] |= f[i] << (x + y);
			}
		}
	}
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &m);
		gao();
	}
	return 0;
}
