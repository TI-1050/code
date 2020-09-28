#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll A, B;

ll f(ll x) {
	vector <int> vec;
	while (x) {
		vec.push_back(x % 10); 
		x /= 10;	
	}
	ll res = 0;
	for (auto it : vec) res = res * 10 + it;
	return res;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld", &A, &B);
		printf("%lld\n", f(f(A) + f(B)));
	}
	return 0;
}
