#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct node {
	ll x, y;

	void input() {
		scanf("%lld %lld", &x, &y);
	}

	ll operator ^ (const node &other) const {
		return x * other.y - y * other.x;
	}

	node operator - (const node &other) const {
		return {x - other.x, y - other.y};
	}
}p[5];

int main() {
	while (~scanf("%lld %lld", &p[1].x, &p[1].y)) {
		p[2].input();
		p[3].input();
		ll ans = abs((p[1] - p[2]) ^ (p[1] - p[3]));
		ans *= 11;
		printf("%lld\n", ans);
	}
	return 0;
}
