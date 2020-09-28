#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n, res; char s[N], t[N];
int f[N][3], nx[3], cnt[3]; 

void calc(int len) {
	int it = 0;
	int cnt = 0;
	while (it <= n) { 
	//	cout << it << endl; 
		for (int i = 1; i <= len; ++i) {
			it = f[it][t[i] - 'a'];
		}
		if (it <= n) ++cnt;  
	}
//	if (cnt * cnt * len) cout << len << endl;
	res = max(res, cnt * cnt * len); 
}

void dfs(int cur) {
	if (cur) calc(cur);
	if (cur == 8) return;
	for (int i = 0; i < 3; ++i) {
		t[cur + 1] = 'a' + i;
		dfs(cur + 1); 
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		for (int i = 0; i < 3; ++i) nx[i] = n + 1;
		for (int i = 0; i < 3; ++i) f[n + 1][i] = n + 1;
		for (int i = n; i >= 0; --i) { 
			for (int j = 0; j < 3; ++j)
				f[i][j] = nx[j];
			if (i) {
				nx[s[i] - 'a'] = i;
				++cnt[s[i] - 'a'];
			}
		}
		res = n;
	    for (int i = 0; i < 3; ++i) res = max(res, cnt[i] * cnt[i]);	
		dfs(0); 
		printf("%d\n", res);
			
	}
	return 0;
}
