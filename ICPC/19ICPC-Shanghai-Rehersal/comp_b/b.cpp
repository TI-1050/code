#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
bitset <N> S, T;
char s[N], t[N];
int ls, lt;

int main() {
	while (scanf("%s%s", s, t) != EOF) {
		ls = strlen(s), lt = strlen(t);
		S.reset(); T.reset(); 
		for (int i = 0; i < lt; ++i) {
			if (t[i] == '1') {
				T[i] = 1;
			}
			if (s[i] == '1') {
				S[i] = 1;	
			}
		}
		int res = (S ^ T).count();
		for (int i = lt; i < ls; ++i) {
			S >>= 1; 
			if (s[i] == '1') {
				S[lt - 1] = 1;
			}
			res = min(res, (int)(S ^ T).count());
		}
		printf("%d\n", res);
	}
	return 0;
}
