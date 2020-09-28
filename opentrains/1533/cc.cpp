#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 600000
int n, m, p; 
struct node {
	int x, y, z;
	node() {}
	void scan() {
		scanf("%d%d", &x, &y);
		--x; --y;
		if (y >= m) ++y;
		z = n - x + abs(y - m);
	}
	bool operator < (const node &other) const {
		return z > other.z;
	}
}a[N];

int main() {
	while (scanf("%d%d%d", &n, &m, &p) != EOF) {
		for (int i = 1; i <= p; ++i) {
			a[i].scan();
		}
		sort(a + 1, a + 1 + p);
		int res = 0;
		for (int i = 1; i <= p; ++i) {
			res = max(res, (i - 1) + a[i].z);
		}
		printf("%d\n", res);
	}
	return 0;
}
