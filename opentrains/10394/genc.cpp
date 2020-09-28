#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 12; cout << n << endl;
	for (int i = 1; i <= n; ++i) printf("%d%c", i, " \n"[i == n]);
	for (int i = 1; i <= n; ++i) printf("%d%c", i + 1, " \n"[i == n]);
	return 0;
}
