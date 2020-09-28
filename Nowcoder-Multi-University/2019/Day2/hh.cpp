#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
#define pii pair <int, int>
#define fi first
#define se second
int n, m, G[N][N], a[N][N];

struct Cartesian_Tree {
	struct node {
		int id, val, fa;
		int son[2];
		node() {}
		node (int id, int val, int fa) : id(id), val(val), fa(fa) {
			son[0] = son[1] = 0;
		}
	}t[N];
	int root;
	pii b[N];
	void init() {
		t[0] = node(0, 0, 0);
	}
	void build(int n, int *a) {
		for (int i = 1; i <= n; ++i) {
			t[i] = node(i, a[i], 0);
		}
		for (int i = 1; i <= n; ++i) {
			int k = i - 1;
			while (t[k].val > t[i].val) {
				k = t[k].fa;
			}
			
			t[i].son[0] = t[k].son[1];
			t[k].son[1] = i;
			t[i].fa = k;
			t[t[i].son[0]].fa = i;
		}
		root = t[0].son[1];
	}
	int DFS(int u) {
		if (!u) return 0;
		int lsze = DFS(t[u].son[0]);  
		int rsze = DFS(t[u].son[1]);
		b[t[u].id] = pii(lsze, rsze);
		return lsze + rsze + 1;
	}
}T[N]; 

ll f(ll l, ll r) {
	if (l > r) return 0;
	return (r + l) * (r - l + 1) / 2;
}

//计算总个数
ll gettot(int n, int *a, pii * b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] > 0) {
			ll l = b[i].fi, r = b[i].se;
			res += (l + 1) * (r + 1);		
		}
	}
	return res;
}

//计算面积<=x的个数
ll getMin(int x, int n, int *a, pii *b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (!a[i]) continue;
		ll len = x / a[i];
		ll l = b[i].fi, r = b[i].se;
		if (len <= 0) continue;
		if (len - r <= 0) { //右边部分大于len
			res += f(max(1ll, len - l), len);
		} else { //右边部分小于len
			res += 1ll * min(len - r, 1ll * l + 1) * (r + 1);
			if (len <= l + r + 1) {  //全长大于len 
				res += f(max(1ll, len - l), r);
			}
		}
	}
	return res;
}	

//计算面积>=x的个数
ll getMax(int x, int n, int *a, pii *b) {
	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		if (!a[i]) continue;
		int len = x / a[i] + (x % a[i] != 0);
		int l = b[i].fi, r = b[i].se;
		if (len <= 1) {
			res += 1ll * (l + 1) * (r + 1);
			continue;
		}
		if (len > l + r + 1) continue;
		--len;
		if (l >= len) { //左边大于len
			res += 1ll * (l + 1 - len) * (r + 1);
			if (r >= len) { //右边大于len
				res += f(r + 1 - len, r);
			} else { //右边小于len
				res += f(1, r);
			}
		} else {
			res += f(max(1, r + 1 - len), r + 1 - (len - l));
		}
	}
	return res;
}


ll check(int x) {
	ll res = 0; 
	for (int i = 1; i <= n; ++i) {
		res += getMax(x, m, a[i], T[i].b);
	}
	return res;
}

//求第k大全1矩形
int solve(ll k) {
	int l = 1, r = n * m, res = 0;
	while (r - l >= 0) {
		int mid = (l + r) >> 1;
		if (check(mid) >= k) {
			l = mid + 1;
			res = mid; 
		} else {
			r = mid - 1;
		}
	}
	return res;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= m; ++j)
				scanf("%1d", G[i] + j);
		//对每一行处理出向上的最大高度，就转换成直方图的形式再用笛卡尔树直接计算即可
		for (int i = 1; i <= m; ++i) a[0][i] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (G[i][j]) a[i][j] = a[i - 1][j] + 1;
				else a[i][j] = 0;
			}
			T[i].init();
			T[i].build(m, a[i]);
			T[i].DFS(T[i].root);
		}	
		printf("%d\n", solve(2));
	}	
	return 0;
}

