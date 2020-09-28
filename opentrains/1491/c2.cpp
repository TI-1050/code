#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		if (n == 1) puts("0 0 0 1");
		else if (n == 2) puts("1 1 1 2\n1 3 1 4\n1 5 1 6");
		else if (n == 3) {
			puts("1 3 2 3");	
			puts("1 2 2 2");	
			puts("3 2 4 2");	
			puts("1 1 2 1");	
			puts("5 2 5 3");	
			puts("3 1 4 1");	
		} else puts("impossible");
	}
	return 0;
}
