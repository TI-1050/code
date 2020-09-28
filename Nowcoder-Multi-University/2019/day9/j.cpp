#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int n;
struct node {
	ll l, r, mid;
	node() {}
	void scan() {
		scanf("%lld%lld", &l, &r);
		l *= 2, r *= 2;
		mid = (l + r) >> 1;	
	}
	bool operator < (const node &other) const {
		return mid < other.mid; 
	}
}a[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) a[i].scan();
		int num[2] = {0, 0}; ll sum[2] = {0, 0};
		ll res = 0;
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) {
			
		}
	}
	return 0;
}
