#include <bits/stdc++.h>
using namespace std;

int n, m; bool flag;
void out(int x, int y) {
	if (flag) swap(x, y);
	printf("%d %d\n", x, y);
}

void gao1() {
	for (int i = n; i >= 3; --i) {
		if (i & 1) {
			for (int j = ((m & 1) ? m : m - 1); j >= 1; j -= 2) 
				out(i, j);
		} else {
			for (int j = 2; j <= m; j += 2)
				out(i, j);
		}
	}	
	out(1, 1);
	for (int i = 2; i <= m; i += 2) out(2, i);
	for (int i = ((m & 1) ? m : m - 1); i >= 3; i -= 2) out(1, i);
}

void gao2() {
	for (int i = 1; i <= m; ++i) 
		out(((i & 1) ? 2 : 1), i);
	for (int i = 3; i <= n; ++i) {
		if (i & 1) {
			for (int j = ((m & 1) ? m - 1 : m); j >= 1; j -= 2) {
				out(i, j);		
			} 
		} else {
			for (int j = 1; j <= m; j += 2) {
				out(i, j);
			}
		}
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		if ((flag = bool(n > m))) swap(n, m);
		if (n == 1 and m == 1) {
			puts("YES");
			out(1, 1);
			continue;
		}
		if (n < 2 or m < 3) {
			puts("NO");
			continue; 
		}
		puts("YES");
		gao1(); gao2(); 
	}
	return 0;
}
