#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
char s[N];
ll x[2], a, b, mod;
inline void add(ll &x, ll y) {
	x += y;
	if (x >= mod) x -= mod;
}
struct node {
	ll a[2][2];
	node() {
		memset(a, 0, sizeof a);
	}
	void set() {
		memset(a, 0, sizeof a);
		a[0][0] = a[1][1] = 1;
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					add(res.a[i][j], 1ll * a[i][k] * other.a[k][j] % mod);
		return res;
	}
	node operator ^ (ll n) {
		node res = node(), base = *this; res.set();
		while (n) {
			if (n & 1) res = res * base;
			base = base * base;   
			n >>= 1;
		}
		return res;
	}
}base, res;

int main() {
	while (scanf("%lld%lld%lld%lld", x, x + 1, &a, &b) != EOF) {
		scanf("%s%lld", s + 1, &mod);
		int len = strlen(s + 1);
		base.a[0][0] = a; base.a[0][1] = 1;
		base.a[1][0] = b; base.a[1][1] = 0;
		res = node(); 
		res.a[0][0] = x[1];
		res.a[0][1] = x[0];
		for (int i = len; i >= 1; --i) {
			int num = s[i] - '0';
			node tmp = base;
			while (num) {
				if (num & 1) res = res * tmp;
				tmp = tmp * tmp;
				num >>= 1;
			}
			base = base ^ 10;
		}
		printf("%lld\n", res.a[0][1]);
	}
	return 0;
}
