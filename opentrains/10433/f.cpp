#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, k, a[N], b[N], que[N], head, tail;

struct KMP {
	int Next[N];
	void get_Next(int *s, int len) {
		int i, j;
		j = Next[0] = -1;
		i = 0;
		while (i < len) {
			while (-1 != j && s[i] != s[j]) j = Next[j];
			Next[++i] = ++j;
		}
	}
	int gao(int *s, int *t, int lens, int lent) {
		int i, j;
		get_Next(t, lent);
		i = j = 0;
		while (i < lens) {
			while (-1 != j && s[i] != t[j]) j = Next[j];
			++i, ++j;
			if (j >= lent) {
				return i - lent + 1;
			}
		}
		return -1;
	}
}kmp;

int main() {
	while (scanf("%d%d", &n, &k) != EOF) {
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		head = 1, tail = 0;
		for (int i = 0; i < n - k; ++i) {
			while (head <= tail && a[i] > a[que[tail]]) --tail;
			que[++tail] = i;
		}
		for (int i = 0; i < k; ++i) {
			while (i + (n - k + 1) - 1 < n && head <= tail && a[i + (n - k + 1) - 1] > a[que[tail]]) --tail;
			que[++tail] = i + (n - k + 1) - 1;
			while (head <= tail && que[head] < i) ++head; 
			b[i] = a[que[head]];
		}
	//	for (int i = 0; i < k; ++i) printf("%d%c", b[i], " \n"[i == k - 1]);
		printf("%d\n", kmp.gao(a, b, n, k));
	}
	return 0;
}
