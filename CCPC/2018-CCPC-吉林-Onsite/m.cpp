#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define N 100010
int n, m;
vector <ll> w;

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		scanf("%d", &n);
		printf("Case #%d:\n", kase); 
		w.resize(n);
		for (int i = 0; i < n; ++i) {
			scanf("%lld", &w[i]);
		}
		sort(w.begin(), w.end(), [](int a, int b) {
			return a > b;
		});	
		scanf("%d", &m); 
		multiset <ll> se;
		se.insert(m);
		ll res = 0; 
		while (!w.empty()) {
			int Max = *se.rbegin();  
			while (!w.empty() && w.back() < Max) {
				se.insert(w.back());
				w.pop_back();
			}
		//	puts("------");
		//    for (auto it : se) {
		//		cout << it << endl;
		//	}	
			if (w.empty()) {
				break;
			}
			Max = w.back();
			while (se.size() >= 2 && *se.rbegin() <= Max) {
				ll x = *se.begin(); se.erase(se.begin());
				ll y = *se.begin(); se.erase(se.begin());
		//		cout << x << " " << y << endl;
				res += x + y;
				se.insert(x + y); 
			}
			if (*se.rbegin() <= Max) {
				break;
			}
		}
		while (se.size() >= 2) {
			ll x = *se.begin(); se.erase(se.begin());
			ll y = *se.begin(); se.erase(se.begin());
			res += x + y;
			se.insert(x + y);
		}
		printf("%lld %lld\n", *se.rbegin(), res);
		
	}
	return 0;
}
