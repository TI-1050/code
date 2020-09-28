#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
const int N = 5e4 + 10; 
int n;
char s[N][10];
pii res[100000 + 10]; int sze;
bitset <N> b[5][76], now; 

void gao() {
	sze = 0;
	for (int i = 0; i < 5; ++i) 
		for (int j = 0; j < 76; ++j)
			b[i][j].reset();
	for (int i = 0; i < 5; ++i) {
		for (int j = 1; j <= n; ++j) {  
			b[i][s[j][i] - 48][j - 1] = 1; 
		}
	}
	for (int i = 2; i <= n; ++i) { 
	    now.reset(); 	
		for (int j = 0; j < 5; ++j) {
			now |= b[j][s[i][j] - 48];
		}
		now = ~now;
	    for (int it = now._Find_first(); it < i - 1; it = now._Find_next(it)) {
			res[++sze] = pii(it + 1, i);
			if (sze >= 100000) return;
		} 	
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%s", s[i]);  
		gao();
		printf("%d\n", sze);
		for (int i = 1; i <= sze; ++i)
			printf("%d %d\n", res[i].fi, res[i].se);
	}
	return 0;
}
