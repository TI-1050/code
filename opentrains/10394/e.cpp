#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}
void sim(ll &a, ll &b) {
	ll t = gcd(a, b);
	a /= t; b /= t;
}
void gao(ll a, ll b, ll c, ll d, ll &x, ll &y) {
	sim(a, b); sim(c, d);
	ll nx = a / b + 1, ny = (c + d - 1) / d - 1;
	if (nx <= ny) x = nx, y = 1;
	else if (!a) x = 1, y = d / c + 1;
	else if (a < b && c <= d) gao(d, c, b, a, y, x);
	else gao(a % b, b, c - d * (a / b), d, x, y), x += y * (a / b);
}

void pt(ll x) {
	if (x / 10) pt(x / 10);
	putchar(x % 10 + '0');
}

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		char s[30];
		scanf("%s", s);
		ll r = 0, t = 10, a, b, c, d, x, y;
		for (int i = 2; s[i]; ++i) r = r * 10 + s[i] - '0';
		if (!r) {
			puts("0 1");
			continue;
		}
		for (int i = 1; i <= 18; ++i) t = t * 10;
		a = r * 10 - 5, b = t; sim(a, b);
		c = r * 10 + 5, d = t; sim(c, d);
		gao(a, b, c, d, x, y);
		sim(x, y);
		if (b < y) x = a, y = b;
		assert(x <= 1000000000 && y <= 1000000000);
		pt(x); putchar(' ');
		pt(y); putchar('\n');
	}
	return 0;
}
