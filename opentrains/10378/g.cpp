#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lll = __int128;

const int N = 110;

lll gcd(lll a, lll b) {
	return b ? gcd(b, a % b) : a;
}

lll abs(lll x) {
	return x < 0 ? -x : x;
}

struct Frac {
	lll x, y;

	void sim() {
		lll G = gcd(abs(x), abs(y));
		x /= G, y /= G;
		if (x * y < 0) x = -abs(x), y = abs(y);
		else x = abs(x), y = abs(y);
	}

	Frac() {}

	Frac(lll x, lll y): x(x), y(y) {}

	Frac operator+(const Frac &other) {
		lll p = x * other.y + y * other.x, q = y * other.y;
		lll G = gcd(p, q);
		p /= G, q /= G;
		return Frac(p, q);
	}

	Frac operator-(const Frac &other) {
		lll p = x * other.y - y *other.x, q = y * other.y;
		lll G = gcd(p, q);
		p /= G, q /= G;
		return Frac(p, q);
	}

	Frac operator*(const Frac &other) {
		lll p = x * other.x, q = y * other.y;
		lll G = gcd(p, q);
		p /= G, q /= G;
		return Frac(p, q);
	}

	bool operator < (const Frac &other) const {
		return x * other.y < y * other.x;
	}

	bool operator == (const Frac &other) const {
		return x * other.y == y * other.x;
	}
}goal;

struct node {
	int cnt;
	Frac x;

	node() {}

	node(int cnt, Frac x): cnt(cnt), x(x) {}
};

int n;
int a, b;
int m[N], t[N];
vector<node> vec;
map<Frac, int> mp[N];

int main() {
	while (scanf("%d %d %d", &n, &a, &b) != EOF) {
		vec.clear();
		for (int i = 0; i < n; ++i) {
			mp[i + 1].clear();
			scanf("%d %d", m + i, t + i);
		}
		goal = Frac(a, b);
		int half = n >> 1, nhalf = n - half;
		for (int S = 1; S < (1 << half); ++S) {
			Frac sum = Frac(0, 1);
			int cnt = 0;
			for (int i = 0; i < half; ++i) {
				if (S & (1 << i)) {
					cnt++;
					sum = (sum + Frac(m[i], t[i]));
				}
			}
			vec.push_back(node(cnt, sum)); 
		}
		for (int S = 1; S < (1 << nhalf); ++S) {
			Frac sum = Frac(0, 1);
			int cnt = 0;
			for (int i = 0; i < nhalf; ++i) {
				if (S & (1 << i)) {
					cnt++;
					sum = (sum + Frac(m[i + half], t[i + half]));
				}
			}
			mp[cnt][sum]++;
		}
		ll res = 0;
		for (int i = 1; i <= nhalf; ++i) {
			if (mp[i].find(goal * Frac(i, 1)) != mp[i].end())
				res += mp[i][goal * Frac(i, 1)];
		}
		for (auto &it : vec) {
			if (goal * Frac(it.cnt, 1) == it.x) ++res;
			for (int i = 1; i <= nhalf; ++i) { 
				Frac other = (goal * Frac(it.cnt + i, 1)) - it.x;
				if (mp[i].find(other) != mp[i].end()) {
					res += mp[i][other];
				}
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
