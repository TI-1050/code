#include <bits/stdc++.h>
using namespace std;

#define ll long long 
ll p, a, b, x, y;

void gao(ll pa, ll pb, ll qa, ll qb, ll &x, ll &y) {
	ll z = (pa + pb - 1) / pb;
	if (z <= qa / qb) {
		x = z, y = 1;
		return;
	}
	pa -= (z - 1) * pb;
	qa -= (z - 1) * qb;
	gao(qb, qa, pb, pa, y, x);
	x += (z - 1) * y;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &p, &x);
		gao(p, x, p, x - 1, b, y);
		a = b * x - p * y; 
		printf("%lld/%lld\n", a, b);
	}
	return 0;
}
