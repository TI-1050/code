#include <bits/stdc++.h>
using namespace std;

#define ll long long
ll A, B, C;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld%lld", &A, &B);
		C = 0; 
		for (int i = 32; i >= 0; --i) { 
			if ((A >> i) % 2 && (B >> i) % 2)
				C |= (1ll << i);
		}
		printf("%lld\n", C);
	}
	return 0;
}
