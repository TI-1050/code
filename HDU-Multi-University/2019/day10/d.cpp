#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;  
const int N = 1e5 + 10;
const int M = 23;
const int ALP = 26;
int _T, n, q, pos[N]; ll w[N]; 
char s[N];

struct SAM {
	//空间开两倍，节点个数是两倍字符串长度
	//maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
	//minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1 
	//fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小 
	//c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
	//pos表示那个结点在字符串的endpos的最小值，即firstpos
	struct node { 
		int maxlen, cnt, fa, nx[ALP];
		node() { maxlen = cnt = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	struct L_B {
	    ll d[65];  
		ull total;
	    void init() {
			memset(d, 0, sizeof d);
			total = 0;
	    }  
	    bool Insert(ll x) {
			ll bk = x; 
	        for (int i = 60; i >= 0; --i) {
	            if (x & (1ll << i)) { 
	                if (!d[i]) {
	                    d[i] = x;
						total += bk;
						return true;
	                }
					x ^= d[i];
	            }
	        }
			return 0;
	    }
	}lb[N << 1];  
	int tot, lst, c[N << 1], rk[N << 1], p[N << 1], fa[N << 1][M];  
	inline int newnode() { 
		++tot;
		t[tot] = node();
		lb[tot].init();
		return tot;
	}
	inline void init() {
		tot = 0;
		lst = newnode();
	}
	inline void extend(int id) { 
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
	//字符串从0开始 
	void build(char *s) { 
		init();
		for (int i = 0; s[i]; ++i) {
			extend(s[i] - 'a'); 
			pos[i + 1] = lst; 
		}
		memset(c, 0, sizeof c); 
		for (int i = 1; i <= tot; ++i) c[t[i].maxlen]++;
		for (int i = 1; i <= tot; ++i) c[i] += c[i - 1];
		for (int i = 1; i <= tot; ++i) rk[c[t[i].maxlen]--] = i;
		for (int i = tot; i; --i) t[t[rk[i]].fa].cnt += t[rk[i]].cnt, p[i] = i;
		for (int i = 1; i <= tot; ++i) {
			int x = rk[i];
			fa[x][0] = t[x].fa;
			for (int j = 1; j < M; ++j)
				fa[x][j] = fa[fa[x][j - 1]][j - 1];
		}
		sort(p + 1, p + 1 + tot, [&](int x, int y){
			return w[t[x].cnt] > w[t[y].cnt];		
		});
		for (int i = 1; i <= tot; ++i) {
			int u = p[i];
			ll x = w[t[u].cnt];
			while (u > 1 && lb[u].Insert(x)) u = t[u].fa;
		}
	}
	ull query(int l, int r) {
		int u = pos[r];
		for (int i = M - 1; i >= 0; --i) {
			if (fa[u][i] && t[fa[u][i]].maxlen >= r - l + 1)
				u = fa[u][i];
		}	
		return lb[u].total;
	}
}sam;

int main() {
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d%s", &n, s);
		for (int i = 1; i <= n; ++i) scanf("%lld", w + i);
		sam.build(s); 
		scanf("%d", &q);
		for (int _q = 1, l, r; _q <= q; ++_q) {
			scanf("%d%d", &l, &r);
			printf("%llu\n", sam.query(l, r));
		}
	}
	return 0;
}
