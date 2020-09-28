#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e6 + 10;
const int ALP = 2; 
int q; char w[N]; 

struct SAM {
	struct node {
		int maxlen, cnt, fa, nx[ALP], has[2];  
		node() { maxlen = cnt = fa = has[0] = has[1] = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst[2];
	inline int newnode() {  
		++tot;
		t[tot] = node();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst[0] = lst[1] = newnode();
	}
	inline void extend(int id, int &lst) { 
		int cur = newnode(), p; 
		t[cur].cnt = 1;
		t[cur].maxlen = t[lst].maxlen + 1; 
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) {
			t[cur].fa = 1;
		} else {
			int q = t[p].nx[id];
			if (t[q].maxlen == t[p].maxlen + 1) {
				t[cur].fa = q;
			} else {
				int clone = newnode();
			  	t[clone] = t[q]; t[clone].cnt = 0;
				t[clone].maxlen = t[p].maxlen + 1; 
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur; 	
	}
	void gao() {
		int len = 0;
		ll res = 0;
		for (int i = 1; i <= q; ++i) {
			int tmp = len ^ (w[i] - '0');
			int a = tmp % 2;
			int c = (tmp / 2) % 2;
			extend(c, lst[a]);
			int it = lst[a];
			while (it) {
				if (t[it].has[a]) break;
				if (t[it].has[a ^ 1]) len = max(len, t[it].maxlen);
				t[it].has[a] = 1;
				it = t[it].fa;
			}
			res += len;
		}
		printf("%lld\n", res);
	}
	void solve() {
		ll res = 0;
		for (int i = 1; i <= tot; ++i) if (t[i].cnt > 1) {
			res = max(res, 1ll * t[i].cnt * t[i].maxlen);
		}
		printf("%lld\n", res);
	}
}sam;

int main() {
	while (scanf("%d", &q) != EOF) {
		scanf("%s", w + 1);
		sam.init(); sam.gao();
	}	
	return 0;
}
