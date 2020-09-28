#include <bits/stdc++.h>
using namespace std;

int n, q, p;

int main() {
	while (scanf("%d%d%d", &n, &q, &p) != EOF) {
		set <int> se;
		for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			se.insert(x);
		}
		int lazy = 0;
		int op, x;
		while (q--) {
			scanf("%d", &op);
			if (op == 2) {
				--lazy;
				se.erase(se.begin());
				se.insert(p - 1 - lazy);
			} else {
				scanf("%d", &x);
				se.insert(x - lazy);
			}
		}
		bool flag = 0;
		for (auto &it : se) {
			if (flag) putchar(' '); flag = 1;
			printf("%d", it + lazy);
		} 
		puts("");
	}
	return 0;
}
