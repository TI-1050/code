#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using LL = __int128;

const int N = 2e3 + 10;
const ll mod = 998244353;

ll qpow(ll x, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return res;
}

int n;

LL abs(LL x) {
	if (x < 0) return -x;
	else return x;
}

struct Point {
	LL x, y;

	Point() {}

	Point(LL x, LL y): x(x), y(y) {}

	Point operator + (const Point &other) const {
		return {x + other.x, y + other.y};
	}

	Point operator - (const Point &other) const {
		return {x - other.x, y - other.y};
	}

	LL operator ^ (const Point &other) const {
		return x * other.y - y * other.x;
	}

	LL operator * (const Point &other) const {
		return x * other.x + y * other.y;
	}

	LL length() {
		return x * x + y * y;
	}
}p[N];

vector<Point> vec;

struct cmp {
	Point P;
	cmp(const Point &p0) {
		P = p0;
	}

	bool operator()(const Point &aa, const Point &bb) {
		Point a = aa, b = bb;
		LL d = (a - P) ^ (b - P);
		if (d == 0) {
			return a.length() - b.length() < 0;
		} else {
			return d > 0;
		}
	}
};

LL gao() {
	LL res1 = 0;
	LL res2 = 0;
	for (int i = 1; i <= n; ++i) {
		vec.clear();
		for (int j = 1; j <= n; ++j) if (i != j){
			vec.push_back(p[j] - p[i]);
		}
		sort(vec.begin(), vec.end(), cmp(p[i]));
		int sze = vec.size();
		// triangles
		int L = 1;
		Point Left = Point(0, 0);
		for (int j = 0; j < sze; ++j) {
			while (L != j && (vec[L] ^ vec[j]) > 0) {
				Left = Left + vec[L];
				L = (L + 1) % sze;
			}
			res1 = res1 + abs(vec[j] ^ Left);
			res1 %= mod;
			Left = Left - vec[j];
		}
		reverse(vec.begin(), vec.end());
		int R = 1;
		Point Right = Point(0, 0);
		for (int j = 0; j < sze; ++j) {
			while (R != j && (vec[R] ^ vec[j]) < 0) {
				Right = Right + vec[R];
				R = (R + 1) % sze;
			}
			res1 = res1 + abs(vec[j] ^ Right);
			res1 %= mod;
			Right = Right - vec[j];
		}
		// not acute triangles
		reverse(vec.begin(), vec.end());
		L = 1, R = 1;
		Left = Point(0, 0);
		while (L != 0 && (vec[L] ^ vec[0]) > 0 && (vec[L] * vec[0]) > 0) {
			L = (L + 1) % sze;
		}
		R = L;
	   	while (R != 0 && (vec[R] ^ vec[0]) > 0 && (vec[R] * vec[0]) < 0) {
			R = (R + 1) % sze;
		}	
		for (int j = 0; j < sze; ++j) {
			while (R != j && (vec[R] ^ vec[0]) > 0 && (vec[R] * vec[j]) < 0) {
				Left = Left + vec[R];
				R = (R + 1) % sze;
			}
			while (L != j && (vec[L] ^ vec[j]) > 0 && (vec[L] * vec[j]) > 0) {
				Left = Left - vec[L];
				L = (L + 1) % sze;
			}
			res2 = res2 + abs(vec[j] ^ Left);
			res2 %= mod;
			Left = Left - vec[j];
		}
		cout << (ll)res1 << " " << (ll)res2 << endl;
	}
	ll res = (res1 - res2 * 2 % mod + mod) % mod * qpow(3, mod - 2) % mod;
	return res;
}


int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d", &n);
		ll x, y;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld %lld", &x ,&y);
			p[i] = Point(x, y);
		}
		ll res = gao();
		printf("%lld\n", res);
	}
	return 0;
}
