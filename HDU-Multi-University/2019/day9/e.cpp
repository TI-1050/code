#include <bits/stdc++.h>
using namespace std;

const int N = 1100;
char s[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%s", s + 1);
		int cnt = 1;
		while (s[cnt] == 'y') ++cnt;
		if (cnt <= strlen(s + 1) && s[cnt] == 'z') s[cnt] = 'b';
		printf("%s\n", s + 1);
	}
	return 0;
}
