#include <bits/stdc++.h>
using namespace std;

#define N 100010
#define INF 0x3f3f3f3f
#define pii pair <int, int>
#define fi first
#define se second
int n, b[N], used[N], res[N];
vector <vector<pii>> vec, G;
struct Stack {
	int a[N], top;
	void init() { top = 0; }
	bool empty() { return !top; }
	void add(int x) { a[++top] = x; }
	void pop() { --top; }
	int back() { return a[top]; }
	bool check(int x, int i) {
		return abs(b[a[i]]) < x;
	}
	bool check2(int x, int i) {
		return abs(b[a[i]]) > x;
	}
	int get(int x, int op) {
		int l = 1, r = top, res = -INF;
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if ((op ? check2(x, mid) : check(x, mid))) {
				l = mid + 1;
				res = a[mid]; 
			} else {
				r = mid - 1;
			}
		}
		return res;
	}
}stk[2];
//0 表示b[i] > 0　维护单调上升序列
//1 表示b[i] < 0  维护单调下降序列

int get_left_bound(int x) {
	int res = 1;
	res = max(res, stk[0].get(x, 0) + n);
	res = max(res, stk[1].get(x, 1) + n);
	return res;
}

bool invalid() {
	for (int i = 1; i <= 2 * n; ++i) if (!vec[i].empty()) {
		sort(vec[i].begin(), vec[i].end());
	}
	multiset <int> se; 
	int lst = 1;
	for (int i = 1; i <= 2 * n; ++i) {
		if (lst < i) return 1;
		for (auto it : vec[i]) {
			se.insert(it.first); 
		}
		if (*se.begin() < lst) return 1;
		se.erase(se.begin());
		++lst;
	}
	return 0;
}

void solve() {
	stk[0].init(); stk[1].init();
	for (int i = 1; i <= 2 * n; ++i) used[i] = 0;
	vec.clear(); vec.resize(n * 2 + 10);
	for (int i = 1; i <= n; ++i) {
		used[abs(b[i])] = 1;
		vec[get_left_bound(abs(b[i]))].push_back(pii(n + i - 1, abs(b[i])));  
		if (b[i] > 0) {
			while (!stk[0].empty() && abs(b[stk[0].back()]) > abs(b[i])) {
				stk[0].pop();
			}
			stk[0].add(i);
		} else {
			while (!stk[1].empty() && abs(b[stk[1].back()]) < abs(b[i])) {
				stk[1].pop();
			}
			stk[1].add(i); 
		}
	}
	for (int i = 1; i <= 2 * n; ++i) if (!used[i]) {
		vec[get_left_bound(i)].push_back(pii(2 * n, i));
	}
	if (invalid()) puts("-1");
	else {
		multiset <int> se;
		G.clear(); G.resize(n * 2 + 10);
		for (int i = 1; i <= 2 * n; ++i) {
			for (auto it : vec[i])
				G[it.fi].push_back(it), se.insert(it.se); 
			int tmp = -1;
			for (auto it : G[i]) {
				if ((*se.lower_bound(it.se)) == it.se) {
					assert(tmp == -1);
					tmp = it.se;
					se.erase(it.se);
				}
			}
			if (tmp == -1) {
				tmp = *se.begin();
				se.erase(se.begin());
			}
			printf("%d%c", tmp, " \n"[i == 2 * n]);
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		solve();
	}
	return 0;
}
