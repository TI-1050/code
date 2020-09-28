#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n; char s[N];
bitset <N> b[26], f;

int main() {
	while (scanf("%s", s + 1) != EOF) {
		int res = 0, k = 0;
		for (int i = 1; s[i]; ++i) {
			f = f << 1 & b[s[i] - 'a'];
			if (f.none()) {
				++res;
				for (int j = k + 1; j < i; ++j)
					b[s[j] - 'a'][j] = 1;
				f = b[s[i] - 'a'];
			    k = i - 1;	
			}
		}	
		printf("%d\n", res);
	}
	return 0;
}
