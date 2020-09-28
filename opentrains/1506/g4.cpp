#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N];

void out(vector <int> &vec) {
	int sze = (int)vec.size();
	printf("%d", sze);
	for (auto it : vec) printf(" %d", it);
	puts("");
}

void gao() {
	vector <int> up, down;
	up.push_back(0); down.push_back(n + 1);
	for (int i = 1; i <= n; ++i) {
		if (a[i] < up.back() and a[i] > down.back()) {
			puts("NO");
			return;
		} else if (a[i] < up.back()) {
			down.push_back(a[i]);
		} else if (a[i] > down.back()) {
			up.push_back(a[i]);
		} else {
			if (i == n) {
				up.push_back(a[i]);
			} else if (a[i] < a[i + 1]) {
				up.push_back(a[i]);
			} else {
				down.push_back(a[i]);
			}
		}
	}
	up.erase(up.begin()); down.erase(down.begin());
	puts("YES");
	out(up); out(down);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i); 
		gao();
	}
	return 0;
}
