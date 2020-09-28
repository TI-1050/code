#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 50;
int n, m, a[N][N];
//第i行第j个数字
int f[1 << 20][21]; 

inline bool up(vector <int> &vec) {
	int sze = (int)vec.size();
	for (int i = 1; i < sze; ++i)
		if (vec[i] < vec[i - 1])
			return 0;
	return 1;
}

inline bool down(vector <int> &vec) {
	int sze = (int)vec.size();
	for (int i = 1; i < sze; ++i)
		if (vec[i] > vec[i - 1])
			return 0;
	return 1;
}

inline bool ok(int i, vector <int> &ord) {
	vector <int> vec;
	for (auto it : ord) vec.push_back(a[i][it]);
	return up(vec) or down(vec);
}

inline vector <int> get(unsigned mask) {
	vector <int> vec;
	for (int j = 0; j < m; ++j) {
		if ((mask >> j) & 1) {
			vec.push_back(j + 1);
		}
	}
	return vec;
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", a[i] + j);
		vector <int> vec;
		ll res = 0;
		unsigned limit = 1 << m;
		for (unsigned mask = 1; mask < limit; ++mask) {
			vec.clear(); 
			vector <int> ord = get(mask); 
			for (int i = 1; i <= n; ++i) {
				if (ok(i, ord)) {
					vec.push_back(i);
				}
			}
			int sze = (int)vec.size(), now, pre;  
			for (int i = 0; i < sze; ++i) {
				now = vec[i]; 
				++res; 
				for (int j = 0; j < i; ++j) {
					pre = vec[j]; 
					//大于 1 小于 0
					unsigned S = 0;
					for (auto &it : ord) {
						S = S * 2 + (a[now][it] > a[pre][it]); 
					}
					res += f[S][pre] + 1;
					f[S][now] += f[S][pre] + 1;
				}		
			}
			for (int i = 0; i < sze; ++i) {
				now = vec[i]; 
				for (int j = 0; j < i; ++j) {
					pre = vec[j]; 
					//大于 1 小于 0
					unsigned S = 0;
					for (auto it : ord) {
						S = S * 2 + (a[now][it] > a[pre][it]); 
					}
					f[S][now] = f[S][pre] = 0;
				}		
			}
		}
		printf("%lld\n", res);
	}
	return 0;
}
