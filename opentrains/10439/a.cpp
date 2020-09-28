#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n;
char s[N]; 

int main() {
	while (scanf("%s", s + 1) != EOF) {
		n = strlen(s + 1);
		reverse(s + 1, s + 1 + n);
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 'b') {
				putchar('b');
				continue;
			} 
			for (int j = 0; j < 5; ++j) {
				putchar(s[i]);
			}
		}
		puts("");
	}
	return 0;
}
