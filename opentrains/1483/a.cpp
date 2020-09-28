#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10; 
int n, cnt;
void out(int x) {
	cnt += x;
//	printf("%d\n", x);
	fflush(stdout);
}

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int v) {
		for (; x < N; x += x & -x)
			a[x] += v;
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}bit;

int main() {
	int S = 300; 
	while (scanf("%d", &n) != EOF) {
		cnt = 0;
		int pre = 0;
		bit.init();
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			if (x > pre) {
				if (x - pre - bit.query(pre + 1, x) <= S) {
					out(1);
					pre = x;
				} else out(0);
			} else out(0);
			bit.update(x, 1);
		}
		cout << cnt << endl;
	}
	return 0;
}
