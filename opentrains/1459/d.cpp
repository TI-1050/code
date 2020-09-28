#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int S = 400;
int n, q, a[N];

struct BIT {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) a[x] += v; 
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) res += a[x];
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}bit;

struct UF {
	

}uf;

int main() {
	while (scanf("%dd%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		char op[10], int x, y;
		while (q--) {
			scanf("%s%d%d", op, &x, &y);
			if (op[1] == 'u') {
				
			} else if (op[1] == 'e') {
			
			} else {
			
			}
		}
	}
	return 0;
}
