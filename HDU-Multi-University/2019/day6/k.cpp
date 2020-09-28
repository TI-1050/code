#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 5e4 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll p = 1e9 + 7;
int n, m, q; ll _;
ll ten[N];
ll f[N][20];  
char s[N];

int main() {
	ten[0] = 1;
	for (int i = 1; i < N; ++i) ten[i] = ten[i - 1] * 10 % p;
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &q);
		scanf("%s", s + 1);
		f[0][0] = 1;
			
	}
	return 0;
}
