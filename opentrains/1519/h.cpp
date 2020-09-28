#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int N = 1e2 + 10;
const int M = 1 << 24;
const int INF = 0x3f3f3f3f;

int n, s;
int a[N];
pii f[M];

pii Cal(pii a, pii b) {
	if (a.first < b.first) return a;
	else if (a.first == b.first && a.second > b.second) return a;
	else return b;
}

int main() {
	while (scanf("%d %d", &n, &s) != EOF) {
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		for (int i = 0; i < (1 << n); ++i) {
			f[i] = pii(INF, 0);
		}
		f[0] = pii(1, s);
		int limit = 1 << n;
		for (int S = 0; S < limit; ++S) {
			for (int i = 0; i < n; ++i) {
				if (S & (1 << i)) {
					continue;
				}
				pii tmp = f[S];
				if (tmp.second >= a[i]) tmp.second -= a[i];
				else {
					tmp.first++;
					tmp.second = s - a[i];
				}
				f[S | (1 << i)] = Cal(f[S | (1 << i)], tmp);
			}
		} 
		printf("%d\n", f[limit - 1].first);
	}
	return 0;
}
