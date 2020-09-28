#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
char z[N], x[N], y[N];

struct KMP {
	int Next[N];
	void get_Next(char *s) {
		int len = strlen(s);
		int i, j;
		j = Next[0] = -1;
		i = 0;
		while (i < len) {
			while (-1 != j && s[i] != s[j]) j = Next[j];
			Next[++i] = ++j;
		}
	}
	void work(char *s, char *t, vector <int> &vec) {
		vec.clear();
		int lens = strlen(s), lent = strlen(t);
		int i, j;
		get_Next(t);
		i = j = 0;
		while (i < lens) {
			while (-1 != j && s[i] != t[j]) j = Next[j];
			++i, ++j;
			if (j >= lent) {
				vec.push_back(i - lent + 1);
				j = Next[j];
			}
		}
	}
}kmp;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s%s%s", z, x, y);
		vector<int> A, B;
		kmp.work(z, x, A);
		kmp.work(z, y, B);
		if (A.empty() || B.empty()) puts("NO");
		else if (A[0] + strlen(x) - 1 < B.end()[-1] || B[0] + strlen(y) - 1 < A.end()[-1]) puts("YES");
		else puts("NO");
	}
	return 0;
}
