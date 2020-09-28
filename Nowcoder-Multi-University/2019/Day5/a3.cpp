#include <bits/stdc++.h>
using namespace std;

#define N 10010
#define ll long long
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
char s[N];
int phi(int n) {
	int res = 0;
	for (int i = 1; i < n; ++i) {
		res += (gcd(i, n) == 1);
	}
	return res; 
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		if (n < 10) {
			printf("%d\n", n);
			continue;
		}
		int Phi = phi(n);
		int need = n / 9, remind = n % 9;
		int m = 0;
		for (int i = 0; ; ++i) {
			if (i % Phi == 0) {
				if (need) {
					--need;
					s[++m] = 9 + '0';
				} else  {
					s[++m] = remind + '0'; 
					break;
				}
			} else {
				s[++m] = '0';
			}
		}
	//	reverse(s + 1, s + 1 + m);
		s[m + 1] = 0;
		puts(s + 1);
	}
	return 0;
}
