#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
#define fi first
#define se second
const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, tot[N]; 
vector <map<int, int>> f;
vector <vector<int>> vec;
template <class T> 
int sze(const T &x) { return x.size(); }

int main() {
	while (scanf("%d", &n) != EOF) {
		f.clear(); f.resize(n + 1);
		vec.clear(); vec.resize(N + 10);
		int res = INF;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", tot + i); 
			for (int j = 1; j <= tot[i]; ++j) {
				scanf("%d", &x);
				++f[i][x]; 
			}
			if (sze(f[i]) != tot[i]) res = min(res, 1 + sze(f[i]));
			for (auto &it : f[i]) {
				vec[it.fi].push_back(sze(f[i]));  
			}
		}
		for (int i = 1; i < N; ++i) if (!vec[i].empty()) {
			sort(vec[i].begin(), vec[i].end());
			if (sze(vec[i]) > 1) {
				res = min(res, vec[i][0] + vec[i][1]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			int Max = -1;
			for (auto &it : f[i]) {
				if (sze(vec[it.fi]) > 1) {
					int a = vec[it.fi][0], b = vec[it.fi][1];
					if (a == tot[i] - it.se + 1) Max = max(Max, 1 + b);
					else Max = max(Max, 1 + a);
				}
			}
			if (Max != -1) {
				res = min(res, Max);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
