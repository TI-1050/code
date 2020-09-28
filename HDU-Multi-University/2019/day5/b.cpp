#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010 
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N], b[N], res[N];
unordered_map <int, int> mp; 

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
}trie;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
	//	cout << T << endl;
		scanf("%d", &n);
		mp.clear();
		trie.init();
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
			++mp[b[i]];
		}
		for (auto it : mp) {
			trie.insert(it.fi, it.se);
		}
		priority_queue <pii, vector <pii>, greater <pii> > pq;
		for (int i = 1; i <= n; ++i) {
			pq.push(pii(trie.query(a[i]), a[i]));
		}
		res[0] = 0;
		while (!pq.empty()) {
			pii it = pq.top(); pq.pop();
			if (mp[it.fi ^ it.se] == 0) {
				pq.push(pii(trie.query(it.se), it.se));
			} else {
				res[++res[0]] = it.fi;
				--mp[it.fi ^ it.se];
				trie.del(it.fi ^ it.se, 1);
			}
		}
		for (int i = 1; i <= n; ++i) 
			printf("%d%c", res[i], " \n"[i == n]);
	}
	return 0;
}
