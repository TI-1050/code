#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define INF 0x3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second
int n, m, a[N], b[N], f[N][2], g[N][2]; 
vector <vector<vector<int>>> vec; 

struct SEG {
	int t[N << 2];
	void build(int id, int l, int r) {
		t[id] = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
	}
	void update(int id, int l, int r, int pos, int x) {
		if (l == r) {
			t[id] = max(t[id], x);
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) update(id << 1, l, mid, pos, x);
		else update(id << 1 | 1, mid + 1, r, pos, x); 
		t[id] = max(t[id << 1], t[id << 1 | 1]);
	}
	int query(int id, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (l >= ql && r <= qr) return t[id];
		int mid = (l + r) >> 1;
		int res = 0;
		if (ql <= mid) res = max(res, query(id << 1, l, mid, ql, qr));
		if (qr > mid) res = max(res, query(id << 1 | 1, mid + 1, r, ql, qr));
		return res;
	}
}seg[2]; 


int main() {
	while (scanf("%d", &n) != EOF) {
		m = 0;   
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[++m] = a[i];
		sort(b + 1, b + 1 + m);
		m = unique(b + 1, b + 1 + m) - b - 1;
		for (int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b; 
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				f[i][j] = 0;
				g[i][j] = 0;
			}
		}	
		//0表示处于上升状态
		//1表示处于下降状态　
		seg[0].build(1, 1, m);
		seg[1].build(1, 1, m);
		for (int i = 1; i <= n; ++i) {
			f[i][0] = 1;
			f[i][1] = 1;
			//0的转移
			f[i][0] = max(f[i][0], seg[0].query(1, 1, m, 1, a[i] - 1) + 1);
			//1的转移
			f[i][1] = max(f[i][1], seg[0].query(1, 1, m, a[i] + 1, m) + 1);
			f[i][1] = max(f[i][1], seg[1].query(1, 1, m, a[i] + 1, m) + 1);
			f[i][1] = max(f[i][1], f[i][0]);
		    seg[0].update(1, 1, m, a[i], f[i][0]);
			seg[1].update(1, 1 ,m, a[i], f[i][1]);	
		}	
		//0表示处于下降状态
		//1表示处于上升状态
		seg[0].build(1, 1, m);
		seg[1].build(1, 1, m);
		for (int i = n; i >= 1; --i) {
			g[i][0] = 1;
			g[i][1] = 1;
			//0的转移 
			g[i][0] = max(g[i][0], seg[0].query(1, 1, m, a[i] + 1, m) + 1);
			g[i][0] = max(g[i][0], seg[1].query(1, 1, m, a[i] + 1, m) + 1);
			//1的转移
			g[i][1] = max(g[i][1], seg[1].query(1, 1, m, 1, a[i] - 1) + 1);
			g[i][0] = max(g[i][0], g[i][1]); 
			seg[0].update(1, 1, m, a[i], g[i][0]);
			seg[1].update(1, 1, m, a[i], g[i][1]);
		}
		int Max = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 2; ++j) {
				Max = max(Max, f[i][j]);
			}
		}
		vec.clear(); vec.resize(n + 1); 
		for (int i = 1; i <= n; ++i) vec[i].resize(2);  
		for (int i = n; i >= 1; --i) {
			vec[g[i][0]][0].push_back(i);
			vec[g[i][1]][1].push_back(i);
		}
		vector <int> small, big; 
		int now = 0, sta = 0, len = 0;  
		while (len < Max) {
			int pos = -1, nsta = -1; 
			//当前处于上升状态　
			if (sta == 0) {
				for (auto it : vec[Max - len][0]) {
					if ((now == 0 || a[it] > a[now]) && it > pos && it > now) {
						pos = it;
						nsta = 0;
					    break;	
					} 
				}	
				for (auto it : vec[Max - len][1]) {
					if ((now == 0 || a[it] != a[now]) && it > pos && it > now) {
						pos = it;
						nsta = 1;
						break;
					}
				}
			} else { //当前处于下降状态
				nsta = 1;
				for (auto it : vec[Max - len][1]) {
					if ((now == 0 || a[it] < a[now]) && it > pos && it > now) {
						pos = it;
						break;
					}
				}
			}
			big.push_back(pos);
			now = pos;
			sta = nsta;
		    ++len;	
		}
		now = 0, sta = 0, len = 0;
		while (len < Max) {
			int pos = INF, nsta = -1; 
			//当前处于上升状态　
			if (sta == 0) {
				for (auto it : vec[Max - len][0]) {
					if ((now == 0 || a[it] > a[now]) && it < pos && it > now) {
						pos = it;
						nsta = 0; 
					} 
				}	
				for (auto it : vec[Max - len][1]) {
					if ((now == 0 || a[it] != a[now]) && it < pos && it > now) {
						pos = it;
						nsta = 1;
					}
				}
			} else { //当前处于下降状态
				nsta = 1;
				for (auto it : vec[Max - len][1]) {
					if ((now == 0 || a[it] < a[now]) && it < pos && it > now) {
						pos = it;
					}
				}
			}
			small.push_back(pos);
			now = pos;
			sta = nsta;
		    ++len;	
		}
		for (int i = 0; i < Max; ++i) printf("%d%c", small[i], " \n"[i == Max - 1]);
		for (int i = 0; i < Max; ++i) printf("%d%c", big[i], " \n"[i == Max - 1]); 
	}
	return 0;
}
