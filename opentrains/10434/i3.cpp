#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pLL = pair <ll, ll>;
#define fi first
#define se second
const int N = 2e5 + 10;
const ll M = 1e6;
int n, m; ll mod, lst;

//6 digits
ll getdb() {
	char s[30];
	scanf("%s", s);
	ll a = 0, b = 0;
	int i = 0, j = 0;
	for (; s[i]; ++i) {
		if (s[i] == '.') break;
		a = a * 10 + s[i] - '0';
	}
	int len = strlen(s);
	assert(len - (i + 1) <= 6);
	for (++i, j = 0; j < 6; ++i, ++j) {
		if (i >= len) b = b * 10;
		else b = b * 10 + s[i] - '0';
	}
	return a * M + b;
}

struct FHQ {
	#define ls t[x].son[0]
	#define rs t[x].son[1]
	struct node {
		int son[2], rnd, sze, v;
		ll sum, key;
	}t[N];
	int tot, rt;
	inline void init() { tot = rt = 0; } 
	inline void pushup(int x) { 
		t[x].sze = t[ls].sze + t[rs].sze + 1; 
		t[x].sum = t[ls].sum + t[rs].sum + t[x].v;
	}
	inline int random() {
		static int seed = 703;
		return seed = int(seed * 48217ll % 2147483647);
	} 
	inline int newnode(ll key, int v) { 
		++tot; 
		t[tot].sze = 1; 
		t[tot].key = key;  
		t[tot].sum = t[tot].v = v; 
		t[tot].rnd = random();  
		t[tot].son[0] = t[tot].son[1] = 0;
		return tot;
	} 
	//默认x < y
	//假设第一棵树的权值小于等于第二棵树的权值，那么就比较它们的随机权值
	//如果rnd[l] < rnd[r]，那么保留第一棵树的左子树，另一棵树作为它的右子树
	//如果rnd[l] >= rnd[r]，那么保留第二棵树的右子树，另一棵树作为它的左子树
	int merge(int x, int y) { 
		if (!x || !y) return x + y;
		if (t[x].rnd < t[y].rnd) {
			t[x].son[1] = merge(t[x].son[1], y);
			pushup(x);
			return x;
		} else {
			t[y].son[0] = merge(x, t[y].son[0]);
			pushup(y);
			return y;
		}
	}
	//以权值key分离now成x, y
	void split(int now, ll key, int &x, int &y) {
		if (!now) x = y = 0;
		else {
			//将所有权值小于等于key的保留在左边
			if (t[now].key <= key) {
				x = now;
				split(t[now].son[1], key, t[now].son[1], y);
			//权值大于key的去右边
			} else {
				y = now;
				split(t[now].son[0], key, x, t[now].son[0]);
			}
			pushup(now);
		}
		//最终得到的根为x的树，里面的权值是小于key的
		//得到的根为y的树，里面的权值是大于key的
	}
	//查询key的排名，若有多个相同的数，输出最小的排名
	//按照key - 1将树分成x, y两棵，那么x树中最大的权值应该小于等于a - 1, 那么a的排名就是sze[x] + 1
	inline pLL query(ll l, ll r) { 
		if (l > r) return pLL(0, 0);
		int x, y, z;
		split(rt, l - 1, x, y);
		split(y, r, y, z); 
		pLL res = pLL(t[y].sze, t[y].sum);
		y = merge(y, z);
		rt = merge(x, y);
		return res;
	}
	//插入一个数key
	//先按权值key将树分成两段，x树中是权值小于等于key的，y树中是权值大于key的
	//那么新建一个节点z，它的权值为key，那么先将x, z合并起来，再将x和y合并起来
	inline void insert(ll key, int v) {
		int x, y;
		split(rt, key, x, y); 
		rt = merge(merge(x, newnode(key, v)), y); 
	}
}fhq[2];  

int main() {
	while (scanf("%d", &n) != EOF) {
		fhq[0].init(); fhq[1].init();
		mod = 1ll * n * M;
		lst = 0;
		m = 0;
		int op;
		for (int i = 1; i <= n * 2; ++i) {
			scanf("%d", &op);
			if (op == 0) {
				ll C = (getdb() + lst) % mod, R = getdb();
				ll l = max(0ll, C - R), r = min(mod, C + R);
				fhq[0].insert(l, m); fhq[1].insert(r, m); 	
				++m;
			} else {
				ll x = (getdb() + lst) % mod;
				pLL a = fhq[0].query(0, x);
				pLL b = fhq[1].query(0, x - 1); 
				pLL res = pLL(a.fi - b.fi, a.se - b.se);
				lst = (lst + res.se * M % mod) % mod;
				printf("%lld\n", res.fi);
			}
		}
	}
	return 0;
}
