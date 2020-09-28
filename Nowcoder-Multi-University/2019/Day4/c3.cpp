#include <bits/stdc++.h>
using namespace std;
 
#define pii pair <int, int>
#define fi first
#define se second
#define ll long long
#define INFLL 0x3f3f3f3f3f3f3f3f
#define N 3000010
int n, a[N], b[N];
ll res;
 
struct Cartesian_Tree {
	struct Info {
		ll pre, suf, sum;
		Info(int x = 0) {
			pre = suf = max(x, 0);
			sum = x;  
		}
		Info(ll pre, ll suf, ll sum) : pre(pre), suf(suf), sum(sum) {}
		friend Info operator + (const Info &l, const Info &r) {
			return Info(max(l.pre, l.sum + r.pre),
					    max(r.suf, l.suf + r.sum),
						l.sum + r.sum);
		}
	};
    struct node {
        int id, val, fa, S; 
        int son[2];
		Info Max, Min;
        node() {}
        node(int id, int val, int fa, int S) : id(id), val(val), fa(fa), S(S) {
            son[0] = son[1] = 0;
        }
		//定义排序规则
		bool operator < (const node &other) const {
			//小根堆<
			//大根堆>
			return val < other.val; 
		}
    }t[N];
    int root; 
	int Sta[N], top;
    void init() {
		//小根堆这里放-INF
		//大根堆这里放INF
        t[0] = node(0, -1e9, 0, 0);   
    }
    void build(int n, int *a, int *b) {
		top = 1; Sta[1] = 1;
        for (int i = 1; i <= n; ++i) {
            t[i] = node(i, a[i], 0, b[i]); 
        }
    	for (int i = 2; i <= n; ++i) {
			while (top && t[i] < t[Sta[top]]) {
				t[Sta[top]].son[1] = t[i].son[0];
				t[i].son[0] = Sta[top];
				--top;
			}
			Sta[++top] = i;
		}
		while (top > 1) {
			t[Sta[top - 1]].son[1] = Sta[top];
			--top;
		}
		root = Sta[1];
	}
    void DFS(int u) {
		int ls = t[u].son[0], rs = t[u].son[1];
		if (ls) DFS(ls);
		if (rs) DFS(rs);
		//将值取负，那么最小就变成最大，这样就只需要写一种排序规则，减小代码难度
		res = max(res, 1ll * t[u].val * (t[ls].Max.suf + t[u].S + t[rs].Max.pre));
		res = max(res, 1ll * t[u].val * -(t[ls].Min.suf - t[u].S + t[rs].Min.pre));
		t[u].Max = t[ls].Max + Info(t[u].S) + t[rs].Max;
		t[u].Min = t[ls].Min + Info(-t[u].S) + t[rs].Min;
	}
}CT;
 
int main() {
	scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) scanf("%d", b + i);
    res = -INFLL;
	CT.init();
    CT.build(n, a, b);
    CT.DFS(CT.root);
    printf("%lld\n", res);
    return 0;
}
