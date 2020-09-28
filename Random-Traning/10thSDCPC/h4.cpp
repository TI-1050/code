#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
struct node {
	int l, r;
	node() {}
	node(int l, int r) : l(l), r(r) {}
	void scan() {
		scanf("%d%d", &l, &r);
	}
	bool operator < (const node &other) const {
		if (l != other.l) {
			return l > other.l;
		}
		return r > other.r;
	}
}a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		priority_queue <node> pq;
		int res = 0, last = 0;
		for (int i = 1; i <= n; ++i) {
			pq.push(a[i]);
		}
		while (!pq.empty()) {
			node top = pq.top(); pq.pop();
			if (top.l > last) {
				last = top.l;
				++res;
			} else if (top.l <= last && last + 1 <= top.r) {
				pq.emplace(last + 1, top.r);
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
