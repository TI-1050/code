#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << 1 << endl;
	int n = 500, m = 0;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j)
			printf("1%c", " \n"[j == n]);
	return 0;
}
