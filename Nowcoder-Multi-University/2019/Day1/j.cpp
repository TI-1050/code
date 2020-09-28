#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll x, y, a, b;

void out(ll A, ll B) {
	if (A == B) {
		puts("=");
	} else if (A < B) {
		puts("<");
	} else {
		puts(">");
	}
}

int main() {
	while (scanf("%lld%lld%lld%lld", &x, &a, &y, &b) != EOF) {
		ll A = x / a; x %= a;
		ll B = y / b; y %= b;
		if (A != B) {
			out(A, B);
		} else {
			out(x * b, y * a);
		}
	}
	return 0;
}
