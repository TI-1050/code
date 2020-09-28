#include <bits/stdc++.h>
using namespace std;

using db = double;
const int N = 1e5 + 10;
const db eps = 1e-12;
int sgn(db x) {
	if (fabs(x) < eps) return 0;
	else return x > 0 ? 1 : -1;
}
int n, m, S, a[N], c[N], v[N];
struct node {
	db w, need;
	node() {}
	node(db w, db need) : w(w), need(need) {}
	bool operator < (const node &other) const {
		return w > other.w; 
	}
};

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d%d", &n, &m, &S);
		memset(v, 0, sizeof (v[0]) * (n + 10));
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			++v[x];
		}
		for (int i = 1; i <= n; ++i) scanf("%d%d", a + i, c + i);
		priority_queue <node> pq;
		for (int i = 1; i <= n; ++i) if (v[i]) {
			pq.push(node(a[i] * 1.0 / v[i], c[i] * v[i])); 
		}
		db remind = S;
		while (!pq.empty()) {
			if (pq.size() == 1) {
				node tmp = pq.top(); pq.pop();
				tmp.w += remind / tmp.need;
				pq.push(tmp);
				break;
			} else {
				node a = pq.top(); pq.pop();
				node b = pq.top(); pq.pop();
				if (sgn(remind - (b.w - a.w) * a.need) >= 0) {
					remind -= (b.w - a.w) * a.need;
					b.need += a.need;
					pq.push(b);
				} else {
					a.w += remind / a.need;
					pq.push(a);
					break;
				}
			}
		}
		printf("%.16f\n", pq.top().w);
	}
	return 0;
}
