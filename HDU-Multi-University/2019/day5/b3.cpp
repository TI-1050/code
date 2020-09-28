#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010 
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N], b[N], res[N];
pii sta[N]; int top;

struct Trie {
	struct node {
		int son[2];
		int tot;
		node() {
			memset(son, -1, sizeof son);
			tot = 0;
		}
	}t[N * 32];
	int cnt;
	void init() {
		cnt = 1;
		t[1] = node();
	}
	void insert(int x, int y) {
		int root = 1;
		for (int i = 30; i >= 0; --i) {
			int &nx = t[root].son[(x >> i) & 1];
			if (nx == -1) {
				nx = ++cnt;
				t[nx] = node();
			}
			root = nx;
			t[root].tot += y;
		}
	}
	void del(int x, int y) {
		int root = 1;
		for (int i = 30; i >= 0; --i) {
			int nx = t[root].son[(x >> i) & 1];
			if (nx == -1) {
				return;	
			}
			t[nx].tot -= y;
			root = nx;
		}
	}
	int query(int x) {
		int root = 1;
		ll res = 0;
		for (int i = 30; i >= 0; --i) {
			int f = (x >> i) & 1;
			int nx = t[root].son[f];
			if (nx == -1 || t[nx].tot == 0) {
				res |= (1 << i);
				nx = t[root].son[!f];
			}
			root = nx;
		}
		return res; 
	}
}trie[2];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n); 
		trie[0].init(); trie[1].init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			trie[0].insert(a[i], 1);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
			trie[1].insert(b[i], 1);
		}
		top = 0;
		for (int i = 1; i <= n; ++i) {
			if (!top) {
				sta[++top] = pii(trie[0].query(0), 0);
			}
			if (top == 1) {
				pii tmp = sta[top];
				pii nx = pii(trie[tmp.se ^ 1].query(tmp.fi) ^ tmp.fi, tmp.se ^ 1); 
				sta[++top] = nx;
			}
			while (1) {
				pii tmp = sta[top];
				pii nx = pii(trie[tmp.se ^ 1].query(tmp.fi) ^ tmp.fi, tmp.se ^ 1);
				if (nx.fi == sta[top - 1].fi) {
					res[i] = nx.fi ^ sta[top].fi;
					trie[nx.se].del(nx.fi, 1);
					trie[sta[top].se].del(sta[top].fi, 1);
					top -= 2;
					break;
				} else {
					sta[++top] = nx;
				}
			}
		}
		sort(res + 1, res + 1 + n);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", res[i], " \n"[i == n]);
		
	}
	return 0;
}
