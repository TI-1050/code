#include <bits/stdc++.h>
using namespace std;

#define db double
#define N 2000010
int x, y, n;
db f[N];
void DFS(int u) {
	if (u > n) {
		return;	
	}
	int ls = (u << 1);
	int rs = (u << 1 | 1);
	DFS(ls); DFS(rs);
	if (u <= x) {
		f[u] = 0;
	} else {
		f[u] = 1;
	}
	if (ls <= n && rs <= n) {
		f[u] = f[u] * 1.0 / 4 + f[ls] * 1.0 / 2 + f[rs] * 1.0 / 4;
	} else if (ls <= n) {
		f[u] = (f[u] + f[ls]) / 2.0;
	} 
}

int main() {
	while (scanf("%d%d", &x, &y) != EOF) {
		n = x + y;
		DFS(1);
		printf("%.10f\n", f[1]);
	}
	return 0;
}
