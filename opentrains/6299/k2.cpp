#include <bits/stdc++.h>
using namespace std;

int main() {
	printf("{");
	long long x;
	for (int i = 1; i <= 70; ++i) {
		cin >> x;
		printf("%lld%c", x, ",}"[i == 70]);
	}
	cout << ";\n";
	return 0;
}
