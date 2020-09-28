#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

struct Point {
	int n;
	ll a[N];
	
	void set(int _n) {
		n = _n;
	}

	void input() {
		for (int i = 0; i < n; ++i) scanf("%lld", a + i);
	}

	ll len() {
		ll res = 0;
		for (int i = 0; i < n; ++i) res += a[i] * a[i];
		return res;
	}

	ll operator * (const Point &b) const {
		ll res = 0;
		for (int i = 0; i < n; ++i) res = res + a[i] * b.a[i];
		return res;
	}

	Point operator^(const Point &b) const {
		Point res;
		res.set(n);
		for (int i = 0; i < n; ++i) 
	}
}

int main() {
	
	return 0;
}
