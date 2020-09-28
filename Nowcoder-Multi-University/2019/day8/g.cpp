#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
char s[N];
char sta[N]; int top;

int main() {
	scanf("%s", s + 1);
	top = 0;
	int n = strlen(s + 1);
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (top >= 2 && sta[top] == s[i] && sta[top - 1] == s[i]) top -= 2, ++res;
		else sta[++top] = s[i];
	}
	printf("%d\n", res);
	return 0;
}
