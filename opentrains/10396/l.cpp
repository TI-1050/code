#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
const int N = 5e2 + 10, M = 1e6 + 10, INF = 0x3f3f3f3f;
int n, m, a[N][N], vis[M];
template <class T1, class T2> void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> void chmin(T1 &x, T2 y) { if (x > y) x = y; }
struct E {
	int x[2], y[2];
	E() { x[0] = INF, x[1] = -INF, y[0] = INF, y[1] = -INF; }
	void up(int a, int b) {
		chmin(x[0], a);
		chmax(x[1], a);
		chmin(y[0], b);
		chmax(y[1], b);
	}
	bool cover(const E& other) const {
		if (x[0] <= other.x[0] && x[1] >= other.x[1] && y[0] <= other.y[0] && y[1] >= other.y[1])
			return true;
		return false;
	}
}e[M];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 0; i < M; ++i) e[i] = E();
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
				e[a[i][j]].up(i, j);
			}
		ll res = 0;
		memset(vis, 0, sizeof vis);
		int tim = 0;
		for (int i = 0; i < M; ++i) {
			if (e[i].x[0] != INF) { 
		//		dbg(i, e[i].x[0], e[i].x[1], e[i].y[0], e[i].y[1]);
				++tim;
				for (int j = e[i].x[0]; j <= e[i].x[1]; ++j) {
					for (int k = e[i].y[0]; k <= e[i].y[1]; ++k) {
						int num = a[j][k];
						if (num == i) continue;
						if (e[i].cover(e[num]) && vis[num] < tim) {
							vis[num] = tim;
							++res;
						}
					}
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
