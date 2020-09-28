#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
#define B bitset <110>
int n, k, a[N];
B G[N];
struct node {
	ll val;
	B mask; 
	node() {}
	node(ll val, B mask) {
		this->val = val;
		this->mask = mask;
	}
	bool operator < (const node &other) const {
		return val > other.val; 
	}
};

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= n; ++i) {
			G[i].reset();
			for (int j = 1, x; j <= n; ++j) {
				scanf("%1d", &x);	
				G[i][j] = x; 
			}
		}		
		priority_queue <node> pq;
		B tmp; tmp.reset();
		pq.push(node(0, tmp));
		while (!pq.empty()) {
			node top = pq.top(); pq.pop();
			if (--k == 0) {
				printf("%lld\n", top.val);
				return 0;
			}
			int pos = 1;
			for (int i = 1; i <= n; ++i) {
				if (top.mask[i]) {
					pos = i + 1;
				}
			}
			for (int i = pos; i <= n; ++i) {
				if ((G[i] & top.mask) == top.mask) {
					top.mask[i] = 1;
					pq.push(node(top.val + a[i], top.mask));
					top.mask[i] = 0;
				}
			}
		}
		puts("-1");
	}
	return 0;
}
