#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010 
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N], b[N], res[N];

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

int Move[4][2] = {
	0, 0,
	1, 1,
	0, 1,
	1, 0
};

int query() {
	int num[2] = {0, 0};
	int it[2] = {1, 1};
	int nx[2];
	for (int i = 30; i >= 0; --i) {
		for (int j = 0; j < 4; ++j) {
			nx[0] = trie[0].t[it[0]].son[Move[j][0]];
			nx[1] = trie[1].t[it[1]].son[Move[j][1]];
			if (nx[0] != -1 && nx[1] != -1 && trie[0].t[nx[0]].tot > 0 && trie[1].t[nx[1]].tot > 0) {
				if (Move[j][0]) num[0] |= (1 << i);
				if (Move[j][1]) num[1] |= (1 << i);
				it[0] = nx[0];
				it[1] = nx[1];
			//	printf("%d %d\n", Move[j][0], Move[j][1]);
				break;
			}
		}
	}
	trie[0].del(num[0], 1);
	trie[1].del(num[1], 1);
//	printf("%d %d\n", num[0], num[1]);
	return num[0] ^ num[1];
}

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
		for (int i = 1; i <= n; ++i) {
			res[i] = query();
		}
		sort(res + 1, res + 1 + n);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", res[i], " \n"[i == n]);
	}
	return 0;
}
