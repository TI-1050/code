#include <bits/stdc++.h>
using namespace std;

mt19937 rd(time(0));
int main() {
	int a[100010];
	int n = 100000; printf("%d\n", n);
	for (int i = 1; i <= n; ++i) a[i] = i;
	shuffle(a + 1, a + 1 + n, rd);
	for (int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
	return 0;
}
