#include <bits/stdc++.h>
using namespace std;

int n, k, t;
vector <vector<int>> vec;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		if ((1ll * n * (n + 1) / 2) % k) {
			puts("no");
			continue;
		}
		vec.clear(); vec.resize(k + 1);
		t = n / k;
		if (t % 2 == 0) { 
			for (int i = 1; i <= t; i += 2) {
				int l = (i - 1) * k + 1, r = (i + 1) * k;
				for (int j = 1; j <= k; ++j) {
					vec[j].push_back(l);
					vec[j].push_back(r);
					++l; --r;  
				}
			}
		} else {
			if (k == 1) {
				for (int i = 1; i <= n; ++i) vec[1].push_back(i);
			} else {
				for (int i = 1; i <= k; ++i) vec[k - i + 1].push_back(i);
				int pos = k + 1;
				for (int i = 1; i <= k; i += 2) {
					vec[i].push_back(pos);
					++pos;
				}		
				for (int i = 2; i <= k; i += 2) {
					vec[i].push_back(pos);
					++pos;
				}
				pos = 2 * k + 1;
				for (int i = 2; i <= k; i += 2) {
					vec[i].push_back(pos);
					++pos;
				}
				for (int i = 1; i <= k; i += 2) {
					vec[i].push_back(pos);
					++pos;
				}
				for (int i = 4; i <= t; i += 2) {
					int l = (i - 1) * k + 1, r = (i + 1) * k;
					for (int j = 1; j <= k; ++j) {
						vec[j].push_back(l);
						vec[j].push_back(r);
						++l; --r;
					}	
				}
			}
		}
		puts("yes");
		for (int i = 1; i <= k; ++i) 
			for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j) 
				printf("%d%c", vec[i][j], " \n"[j == sze - 1]); 
	}
	return 0;
}
