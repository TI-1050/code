#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char s[N];

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		if (len == 1) {
			printf("%c\n", s[1] - 1);
			continue;
		} 
		if (s[1] > '1') {
			s[1]--;
			printf("%s", s + 1);
			reverse(s + 1, s + len);
			s[len] = 0;
			printf("%s", s + 1);
		} else if (s[2] == '0') {
			for (int i = 1; i < len; ++i)
				s[i] = s[i + 1];
			s[1] = '9';
			s[len] = 0; len--;
			printf("%s", s + 1);
			reverse(s + 1, s + len);
			s[len] = 0;
			printf("%s", s + 1);
		} else {
			for (int i = 1; i < len; ++i)
				s[i] = s[i + 1];
			s[len] = 0; len--;
			printf("%s", s + 1);
			reverse(s + 1, s + len + 1);
			printf("%s", s + 1);
		}
		puts("");
	}
	return 0;
}
