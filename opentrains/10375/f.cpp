#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define N 100010

int n;
int idx[N];
int r[N];

ll solve() {
	multiset<int>s;
	int Max = idx[1] + r[1];
	int pos = 1;
	while (pos < n && Max >= idx[pos + 1]) {
		pos++;
		Max = max(Max, idx[pos] + r[pos]);
	}
	if (pos < n) return -1;
	for (int i = 1; i <= n; ++i) {
		s.insert(idx[i] - r[i]);
	}
	for (int i = 1; i <= n; ++i) {
		auto it = s.find(idx[i] - r[i]);
		s.erase(it);
		if (*s.begin() > idx[i]) return -1;
	}
	return 3ll * (idx[n] - idx[1]);
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d %d", idx + i, r + i);
		}
		printf("%lld\n", solve());
	}
	return 0;
}
