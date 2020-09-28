#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];
ll res, tot;
map <int, int> mp;  
set <int> se;
vector <int> vec;

void add(int x) {
	if (mp.find(x) != mp.end() && mp[x] == 1) return;
	++tot; mp[x] = 1;	
	if (mp.find(x - 1) != mp.end() && mp[x - 1] == 1) {
		se.erase(x - 1);
	}
	if (mp.find(x + 1) != mp.end() && mp[x + 1] == 1) {
		return;
	}
	se.insert(x);
}

void del(int x) {
	--tot; mp[x] = 0;
	if (mp.find(x - 1) != mp.end() && mp[x - 1] == 1) {
		se.insert(x - 1);
	} 
}

int main() {
	while (scanf("%d", &n) != EOF) {
		mp.clear();  
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
			a[i].se = (a[i].se - a[i].fi) / 2;  
		}
		se.clear();
		sort(a + 1, a + 1 + n); 
		res = 0, tot = 0;
		int x = -1e9 - 10, pos = 1;
		while (1) {
			//cout << x << " " << tot << " " << pos << endl;
			if (tot == 0 && pos > n) {
				break;
			}
			if (tot == 0) {
				x = a[pos].fi;
			}
			vec.clear();
			for (auto it : se) {
				vec.push_back(it);
			}
			se.clear();
			for (auto it : vec) del(it); 
			while (pos <= n && a[pos].fi <= x) {
				add(a[pos].se);
			    ++pos; 	
			}
			res += tot;
			++x;
		}
		printf("%lld\n", res);
	}
	return 0;
}
