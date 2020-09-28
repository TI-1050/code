#include <bits/stdc++.h>
using namespace std;

#define pii pair <int, int>
#define fi first
#define se second
int n, k, t;
vector <vector<int>> vec;
vector <pii> q3, q2, q;

void add(vector <int> &vec, pii x) {
	if (x.fi) vec.push_back(x.fi);
	if (x.se) vec.push_back(x.se);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		if (n == k) {
			if (n == 1) {
				puts("yes\n1");
			} else {
				puts("no");
			}
			continue;
		}
		vec.clear(); vec.resize(k + 1);
		t = n / k;
		if (t % 2 == 0) {
			puts("yes");
			for (int i = 1; i <= t; i += 2) {
				int l = (i - 1) * k + 1, r = (i + 1) * k;
				for (int j = 1; j <= k; ++j) {
					vec[j].push_back(l);
					vec[j].push_back(r);
					++l; --r;
				}
			}
			for (int i = 1; i <= k; ++i) {
				for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j) 
					printf("%d%c", vec[i][j], " \n"[j == sze - 1]); 
			}
		} else {
			if (k % 2 == 0) {
				puts("no");
			} else {
				q3.clear(); q2.clear(); q.clear();
				int need3q = t / 3 * k; 
				if (n % 4 == 1) {
					q.push_back(pii((n + 1) / 2, 0));
					int l_q = 1, r_q = (n - 1) / 2;
					int l_3q = (n + 3) / 2, r_3q = n;	
					while (l_3q < r_3q && need3q) {
						--need3q;
						q3.push_back(pii(l_3q, r_3q));
						++l_3q, --r_3q;
					}
					if (l_3q < r_3q) {
						l_q = 1 + (l_3q - (n + 3) / 2);
						r_q = (n - 1) / 2 - (n - r_3q);
						while (l_3q < r_3q) {
							q2.push_back(pii(l_3q, r_q));
							q2.push_back(pii())
						}
					}
					while (l_3q < r_3q) {
						
					}
					while (l < r) {
						q.push_back(pii(l, r));
						++l; --r;
					}
					l = (n + 3) / 2, r = n;
					while (l < r) {
						q3.push_back(pii(l, r));
						++l;
						--r;
					}
				} else if (n % 4 == 3) {
					int l = 1, r = (n - 1) / 2;
					while (l < r) {
						q.push_back(pii(l, r));
						++l; --r;
					}
					q.push_back(pii((n + 1) / 2, 0));
					q2.push_back(pii((n + 1) / 4, (3 * n + 3) / 4));
					l = (n + 3) / 2, r = n; 
					while (l < r) {
						q3.push_back(pii(l, r));
						++l; --r;
					}
				}
			//	puts("######");
			//	for (auto it : q) cout << it.fi << " " << it.se << endl;
			//	for (auto it : q2) cout << it.fi << " " << it.se  << endl;
			//	for (auto it : q3) cout << it.fi << " " << it.se  << endl;
			//	cout << q.size() << " " << q2.size() << " " << q3.size() << endl;
				bool F = 1;
				for (int i = 1; i <= k; ++i) {
					int need = t;
					while (need >= 3 && !q3.empty()) { 
						add(vec[i], q3.back()); q3.pop_back();
						need -= 3;
					}
					while (need >= 2 && !q2.empty()) {
						add(vec[i], q2.back()); q2.pop_back();
						need -= 2;
					} 
					while (need >= 1 && !q.empty()) {
						add(vec[i], q.back()); q.pop_back();
						need -= 1;
					}
					if (need) {
						F = 0;
						break;
					}	
			//		cout << need << endl;
			//		cout << q.size() << " " << q2.size() << " " << q3.size() << endl;
				}
				if (F) {
					puts("yes");
					for (int i = 1; i <= k; ++i) 
						for (int j = 0, sze = (int)vec[i].size(); j < sze; ++j)
							printf("%d%c", vec[i][j], " \n"[j == sze - 1]); 
				} else {
					puts("no");
				}
			}
		}
	}
	return 0;
}
