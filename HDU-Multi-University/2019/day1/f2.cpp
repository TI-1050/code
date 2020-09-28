#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int ALP = 26;
char s[N];
ll f[N], p, q;

struct SAM {
	//空间开两倍
	int maxlen[N << 1], trans[N << 1][ALP], link[N << 1], sze, lst;
	SAM() { sze = 0; lst = ++sze; }
	inline void init() {
		for (int i = 0; i <= sze; ++i) 
			for (int j = 0; j < ALP; ++j)
				trans[i][j] = 0; 
		sze = 0; lst = ++sze;
	}
	inline void extend(int id) {
		int cur = ++sze, p;
		maxlen[cur] = maxlen[lst] + 1;
		for (p = lst; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
		if (!p) {
			link[cur] = 1;
		} else {
			int q = trans[p][id];
			if (maxlen[q] == maxlen[p] + 1) {
				link[cur] = q;
			} else {
				int clone = ++sze;
				maxlen[clone] = maxlen[p] + 1;
				memcpy(trans[clone], trans[q], sizeof trans[q]);
				link[clone] = link[q];
				for (; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
				link[cur] = link[q] = clone;  
			}
		}
		lst = cur; 	
	}
	void gao(char *s) {
		int n = strlen(s + 1);
		init();
		f[1] = p;
		extend(s[1] - 'a');
		int cur = trans[1][s[1] - 'a'];
		for (int i = 2, j = 1; i <= n; ++i) {
			f[i] = f[i - 1] + p;
			while (1) {
				while (cur > 1 && maxlen[link[cur]] >= i - j - 1) cur = link[cur];
				if (trans[cur][s[i] - 'a']) {
					cur = trans[cur][s[i] - 'a'];
					break;
				} else {
					extend(s[++j] - 'a'); 
				}
			}
			f[i] = min(f[i], f[j] + q);
		}
		printf("%lld\n", f[n]);	
	}
}sam;

int main() {
	while (scanf("%s", s + 1) != EOF) {
		scanf("%lld%lld", &p, &q);
		sam.gao(s); 
	}
	return 0;
}
