#include <bits/stdc++.h>

using namespace std;

using db = double;
using ll = long long;

const db PI = acos(-1.0);

ll n, m;

int main() {
	while (scanf("%lld %lld", &n, &m) != EOF) {
		ll LCM = n * m / __gcd(n, m);
		db res = (sin(PI / LCM) * tan(PI / m)) / (sin(PI / n) * tan(PI / LCM));
		printf("%.10f\n", res);
	}	
	return 0;
}
