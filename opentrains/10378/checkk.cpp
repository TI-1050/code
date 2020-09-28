#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int x[N], y[N];

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
	for (int i = 0; i < n; ++i) {
		if (!ok(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]))
	}
	return 0;
}
