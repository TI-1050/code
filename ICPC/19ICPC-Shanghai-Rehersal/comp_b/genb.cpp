#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n, m;
int main() {
	n = 100000, m = rnd() % n + 1;
	for (int i = 1; i <= n; ++i) 
		printf("%d", rnd() % 2);
	puts("");
	for (int i = 1; i <= m; ++i)
		printf("%d", rnd() % 2);
	puts("");
}
