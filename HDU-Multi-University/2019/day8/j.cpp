#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, d;
struct node {
	char s[10];
	int p, t;
	node() {}
	void scan() {
		scanf("%s%d%d", s, &p, &t);
	}
	bool operator < (const node &other) const {
		if (p != other.p) return p > other.p;
		return t < other.t;
	}
}a[N];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &d);
		for (int i = 1; i <= n; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + n);
		if (n * d % 10 == 5) {
			int t = n * d / 10 + 1;
			puts(a[t].s);
		} else {
			puts("Quailty is very great");
		}
	}
	return 0;
}
