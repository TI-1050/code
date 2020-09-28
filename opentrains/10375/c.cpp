#include <bits/stdc++.h>
using namespace std;

#define N 110
int n, l, r;
char s[N];

int main() {
	while (scanf("%d%d%d", &n, &l, &r) != EOF) {
		assert((r - l + 1) % 2 == 0 && n % 2 == 0);
		if (l % 2 == 0) {
			s[1] = '(';
			s[n] = ')';
			bool F = 1; 
			for (int i = 2; i < l; ++i) {
				if (F) s[i] = '(';
				else s[i] = ')';
				F ^= 1;
			}	
			for (int i = r + 1; i < n; ++i) {
				if (F) s[i] = '(';
				else s[i] = ')';
				F ^= 1;
			}
		} else {
			bool F = 1;
			for (int i = 1; i < l; ++i) {
				if (F) s[i] = '(';
				else s[i] = ')';
				F ^= 1;
			}
			for (int i = r + 1; i <= n; ++i) {
				if (F) s[i] = '(';
				else s[i] = ')';
				F ^= 1;
			}
		}
		bool F = 1;
		for (int i = l; i <= r; ++i) {
			if (F) s[i] = '[';
			else s[i] = ']';
			F ^= 1;
		}
		s[n + 1] = 0;
		printf("%s\n", s + 1);
	}
	return 0;
}
