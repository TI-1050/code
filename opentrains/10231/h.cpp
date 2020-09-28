#include <bits/stdc++.h>
using namespace std;

#define N 510
#define uint unsigned int
int n, q;
uint A[N], B[N];
bitset <N> G[N], H[N];

uint gao() {
	for (int i = 1; i <= n; ++i) {
		H[i] = G[i];
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			if (H[i][k]) {
				H[i] |= H[k];
			}
		}
	}
	uint res = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i != j && H[i][j]) {
				res += A[i - 1] * B[j - 1];
			} 
		}
	}
	return res;
}

int main() {
	freopen("reachability.in", "r", stdin);
	freopen("reachability.out", "w", stdout);
	A[0] = B[0] = 1;
	scanf("%d%d%u%u", &n, &q, A + 1, B + 1);
	for (int i = 1; i <= n; ++i) {
		A[i] = A[i - 1] * A[1];
		B[i] = B[i - 1] * B[1];
	}
	for (int i = 1; i <= n; ++i) G[i].reset();
	char op1[5], op2[5]; int v, a[N];
	for (int _q = 1; _q <= q; ++_q) {
		scanf("%s%s%d%d", op1, op2, &v, a);
		for (int i = 1; i <= a[0]; ++i) {
			scanf("%d", a + i);
			if (op2[0] == 'o') {
				G[v][a[i]] = G[v][a[i]] ^ 1;
			} else {
				G[a[i]][v] = G[a[i]][v] ^ 1;
			}
		}
		printf("%u\n", gao());
	}
	return 0;
}
