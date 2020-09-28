#include <bits/stdc++.h>
using namespace std;

int main() {
	for (int i = 2; i <= 1000; ++i) {  
		printf("%lld\n", ((1ll * i * i * i * i) - (1ll * i * i * i)) % (i - 1));
	}
	return 0;
}
