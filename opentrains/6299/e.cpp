#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, ALP = 26;
int n, f[N]; char s[N];

struct SAM {
	struct node {
		int len, fa, nx[ALP];
		node() { len = fa = 0; memset(nx, 0, sizeof nx); }
	}t[N << 1];
	int tot, lst;
	int newnode() {
		++tot;
		t[tot] = node();
		return tot;
	}
	void init() {
		tot = 0;
		lst = newnode();
	}
	void extend(int id) {
		int cur = newnode(), p;
		t[cur].len = t[lst].len + 1;
		for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
		if (!p) t[cur].fa = 1;
		else {
			int q = t[p].nx[id];
			if (t[q].len == t[p].len + 1) t[cur].fa = q;
			else {
				int clone = newnode();
				t[clone] = t[q]; 
				t[clone].len = t[p].len + 1;
				for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
				t[cur].fa = t[q].fa = clone;
			}
		}
		lst = cur;
	}
	void gao(char *s) {
		init();
		n = strlen(s + 1);
		f[0] = 0;
		for (int i = 1, j = 0, p = 1; s[i]; ++i) {
			f[i] = f[i - 1] + 1;
			while (1) {
				while (p > 1 && t[t[p].fa].len >= i - j - 1) {
					p = t[p].fa;
				}
				if (!p) p = 1; 
				if (!t[p].nx[s[i] - 'a']) {
					++j;
					extend(s[j] - 'a');
				} else {
					p = t[p].nx[s[i] - 'a'];
					break;
				}
			}
			if (j < i) f[i] = min(f[i], f[j] + 1);
		}	
		printf("%d\n", f[n]);
	}
}sam;


int main() {
	while (scanf("%s", s + 1) != EOF) {
		sam.gao(s);
	}
	return 0;
}
