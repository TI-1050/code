#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, cnt, a[N];
void out(int x) {
	cnt += x;
//	printf("%d\n", x);
	fflush(stdout);
}

struct BIT {
	int a[N]; 
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = max(a[x], v);
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res;
	}
}bit;

int main() {
	int S = 200;  
	while (scanf("%d", &n) != EOF) {
		cnt = 0;
		int pre = 0, nx = S;  
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x); 
			a[i] = x; 
			if (x > pre) {
				if (x <= nx) {
					out(1); 
					pre = x;
					nx += S;
				} else out(0);
			} else out(0);
		}
		for (int i = 1; i <= n; ++i) {
			int f = bit.query(a[i] - 1);
			bit.update(a[i], f + 1);	
		}
		cout << cnt << endl;
		cout << bit.query(n) << endl;
	}
	return 0;
}
