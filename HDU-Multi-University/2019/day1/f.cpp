#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define N 200010
#define INFLL 0x3f3f3f3f3f3f3f3f
int n;
char s[N];
ll f[N], p, q; 
ull Hash[N], Base[N];

void init() {
	Base[1] = 31;
	for (int i = 1; i <= n; ++i) {
		Hash[i] = Base[i] * s[i];
		Hash[i] += Hash[i - 1];
		Base[i + 1] = Base[i] * 31;
	}
}
int main() {
	while (scanf("%s", s + 1) != EOF) {
		scanf("%lld%lld", &p, &q);
		n = strlen(s + 1);
		init();
		for (int i = 1; i <= n; ++i) f[i] = INFLL;
		f[1] = p;
		for (int i = 1; i <= n; ++i) {
			f[i + 1] = min(f[i + 1], f[i] + p);
			if (i * 2 <= n) {
				ull L = Hash[i];
				ull R = Hash[i * 2] - Hash[i];
				L *= Base[i];
				if (L == R) {
					f[i * 2] = min(f[i * 2], f[i] + q);
				}
			}
		} 
		printf("%lld\n", f[n]);
	}
	return 0;
}
