#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
char s[N];
int n, id[N], sta[N], top; 

ll gao(int l, int r) {
//	cout << l << " " << r << endl;
	if (l == r + 1) return 1;
	if (l + 1 == r) return 2;
	ll res = 1;
	for (int i = l; i <= r; ) {
		res *= 1ll + gao(i + 1, id[i] - 1);
		i = id[i] + 1;
	}
	return res;
}

int main() {
	freopen("bracket-expression.in", "r", stdin);
	freopen("bracket-expression.out", "w", stdout);
	while (gets(s + 1)) {
		top = 0;
		n = strlen(s + 1);
		if (n == 0) {
			puts("1");
			continue;
		}
		for (int i = 1; i <= n; ++i) {
			if (s[i] == '(') {
				sta[++top] = i;
			} else {
				assert(top);
				int T = sta[top];
				id[T] = i;
				id[i] = T; 
				--top;
			}
		}
		printf("%lld\n", gao(1, n)); 
	}
	return 0;
}
