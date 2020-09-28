#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 2000010
const ll p = 1e6 + 3;
int n;
ll fac[N];

int main() {
	fac[0] = 1;
	for (int i = 1; i <= 2000000; ++i) {
		fac[i] = fac[i - 1] * i % p;
	}	
	while (scanf("%d", &n) != EOF) {
		if (n >= p) puts("0");
		else {
			printf("%lld\n", fac[n]);
		}
	}
	return 0;
}
