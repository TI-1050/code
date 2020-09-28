#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 400010
int n, m, a[N], tmp[N]; 

struct Hash {
	int a[N << 1], cnt;
	void init() {
		cnt = 0; 
	}
	void add(int x) {
		a[++cnt] = x;
	}
	void work() {
		sort(a + 1, a + 1 + cnt);
		cnt = unique(a + 1, a + 1 + cnt) - a - 1;
	}
	int get(int x) {
		return lower_bound(a + 1, a + 1 + cnt, x) - a;
	}
}ha;

struct Mo {
	//储存修改过程中的临时变量
	int tmp[N];
	//计数
	int cnt[N];
	//块大小
	int block;
	//询问数和操作数
	int cnt_qu, cnt_op; 
	//储存答案 
	ll res, ans[N]; 
	struct Query {
		int id, l, r, t, bl, br;
		Query() {}
		Query(int id, int l, int r, int t, int bl, int br) : id(id), l(l), r(r), t(t), bl(bl), br(br) {}
		bool operator < (const Query &other) const {  
		   	if (bl != other.bl) return bl < other.bl;
			if (br != other.br) return br < other.br;
			return t < other.t;	
		}
	}qu[N];
	struct Op {
		int id, pre, now;
		Op() {} 
		Op(int id, int pre, int now) : id(id), pre(pre), now(now) {}
	}op[N];
	void init(int n) {
		//设置块的大小
		block = max(10, (int)pow(n, 2.0 / 3)); 
		cnt_qu = cnt_op = 0;
		res = 0;
	}
	void addquery(int l, int r) {
		++cnt_qu;
		qu[cnt_qu] = Query(cnt_qu, l, r, cnt_op, l / block, r / block); 
	}
	void addop(int id, int pre, int now) {
		op[++cnt_op] = Op(id, pre, now);
	}
	ll calc(ll x) {
		return x * (x - 1) / 2;
	}
	void update(int id, int opt) { 
		res -= calc(cnt[tmp[id]]);
		cnt[tmp[id]] += opt;
		res += calc(cnt[tmp[id]]); 
	}
	void change(int t, int opt, int l, int r) {
		int pos = op[t].id;
		int v = opt ? op[t].now : op[t].pre;
		if (pos >= l && pos <= r) {
			update(pos, -1);
			tmp[pos] = v;
			update(pos, 1);
		} else {
			tmp[pos] = v;   
		}
	}
	void work(int *a, Hash &ha) {
		//赋初始值
		for (int i = 0; i <= n; ++i) tmp[i] = a[i];
		for (int i = 1; i <= cnt_op; ++i) {
			op[i].pre = ha.get(op[i].pre);
			op[i].now = ha.get(op[i].now);
		}
		sort(qu + 1, qu + 1 + cnt_qu);
		for (int i = 1, l = 1, r = 0, t = 0; i <= cnt_qu; ++i) {
			for (; t < qu[i].t; ++t) change(t + 1, 1, l, r);
			for (; t > qu[i].t; --t) change(t, 0, l, r);
			for (; r < qu[i].r; ++r) update(r + 1, 1);
			for (; r > qu[i].r; --r) update(r, -1);
			for (; l > qu[i].l; --l) update(l - 1, 1);
			for (; l < qu[i].l; ++l) update(l, -1);
			ans[qu[i].id] = calc(qu[i].r - qu[i].l + 1) - res;
		}
		for (int i = 1; i <= cnt_qu; ++i)
			printf("%lld\n", ans[i]);
	}
	//多组数据记得清空
	void clear(int n) {
		for (int i = 0; i <= n; ++i) cnt[i] = 0;
	}
}mo; 


void init() {
	mo.init(n); ha.init();
	ha.add(0); a[0] = 0; tmp[0] = 0;
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		init(); 
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			a[i] ^= a[i - 1];
			tmp[i] = a[i];
			ha.add(a[i]);
		}
		for (int i = 1, op, x, y; i <= m; ++i) {
			scanf("%d%d", &op, &x);
			if (op == 1) {
				scanf("%d", &y);
				mo.addquery(x - 1, y);
			} else {
				int var = tmp[x + 1] ^ tmp[x - 1]; 
				mo.addop(x, tmp[x], tmp[x] ^ var);  
				tmp[x] ^= var;  
				ha.add(tmp[x]); 
			}
		}
		ha.work();
		for (int i = 0; i <= n; ++i) {
			a[i] = ha.get(a[i]); 
		}
		mo.work(a, ha);
		mo.clear(ha.cnt);
	}
	return 0;
}
