#include <bits/stdc++.h>
using namespace std;

#define db double
const db PI = acos(-1.0);

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) {
		db res = PI;
		db angle = 2 * PI / n;  
		db one = PI / n - sin(angle) / 2;
		db one2 = PI / n / 2 - sin(angle / 2) / 2;
		res -= (n - 1) * one;
		res -= 2 * one2;
		printf("%.6f\n", res);
	}
	return 0;
}
