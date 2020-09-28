#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
int n, m, a[N], b[N], c[N];
struct node {
	ll sum, x, a, b;
	node() {}
	node (ll sum, ll x, ll a, ll b) : sum(sum), x(x), a(a), b(b) {}
	bool operator < (const node &other) const {
		return sum > other.sum;
	}
};

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		ll res = 0;
		priority_queue <node> pq;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d", a + i, b + i, c + i);
			res += a[i] + b[i] + c[i];
			pq.push(node(2ll * a[i] + a[i] + b[i], 2, a[i], b[i]));
		}
		m -= n;
		while (m--) {
			node top = pq.top(); pq.pop();
			res += top.sum;
			top.sum = 2ll * top.a * top.x + top.a + top.b;
			++top.x;
			pq.push(top);
		}
		printf("%lld\n", res);
	}
	return 0;
}
