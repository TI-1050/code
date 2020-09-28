#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1100
int n;
char s[N];

ll get() {
	scanf("%s", s + 1);
	int len = strlen(s + 1); 
	int pos = -1;
	for (int i = 1; i <= len; ++i) {
		if (s[i] == '.') {
			pos = i;
			break;
		}
	}
	if (pos == -1 || len - pos < 3) return 0;
	int num = s[pos + 3] - '0';
	if (num <= 4) return -num;
	else return 10 - num; 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			res += get();
		}
		printf("%.3f\n", res * 0.001);
	}
	return 0;
}
