#include <bits/stdc++.h>

using namespace std;

unsigned long long k1, k2;
unsigned long long rng() {
	unsigned long long k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return k2 + k4;
}

struct node {
	int a, b;

	node() {}

	node(int a, int b):a(a), b(b){}

	bool operator < (const node &other) const {
		return a + b > other.a + other.b;
	}
};

int n, m, p, mod;
unordered_map <int, int> num1, num2;
vector<node> vec;

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d %d %d", &n, &m, &p);
		num1.clear(), num2.clear();
		if (p == 1) {
			for (int i = 1, x; i <= n; ++i) {
				scanf("%d", &x);
				num1[x]++;
			}
			for (int i = 1, x; i <= m; ++i) {
				scanf("%d", &x);
				num2[x]++;
			}
		} else {
			scanf("%llu %llu %d", &k1, &k2, &mod);
			for (int i = 1, x; i <= n; ++i) {
				x = rng() % mod;
				num1[x]++;
			}
			scanf("%llu %llu %d", &k1, &k2, &mod);
			for (int i = 1, x; i <= m; ++i) {
				x = rng() % mod;
				num2[x]++;
			}
		}
		int sum1 = n, sum2 = m;
		vec.clear();
		for (auto it : num1) {
			if (num2.count(it.first)) {
				vec.push_back(node(it.second, num2[it.first]));
			}
		}
		sort(vec.begin(), vec.end());
		for (int i = 0, len = vec.size(); i < len; ++i) {
			if (i & 1) {
				sum2--;
				sum1 -= vec[i].a;
			} else {
				sum1--;
				sum2 -= vec[i].b;
			}
		}
		if (vec.size() & 1) sum2--;
		puts(sum1 > sum2 ? "Cuber QQ" : "Quber CC");
	}
	return 0;
}
