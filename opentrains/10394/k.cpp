#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 5e5 + 10;
int n, m, cnt[30]; string qs[N];
unordered_map<ll, int> mp; int id;
struct Hash {
	constexpr static ll seed[2] = {233, 13331};
	constexpr static ll mod[2] = {998244353, 1000000007};
	static ll base[2][30];
	static void init() {
		base[0][0] = base[1][0] = 1;
		for (int i = 1; i < 30; ++i) {  
			base[0][i] = base[0][i - 1] * seed[0] % mod[0];
			base[1][i] = base[1][i - 1] * seed[1] % mod[1];
		}
	}
	ll a[2];                     
	void gao(int *s) { 
		a[0] = a[1] = 0;
		for (int i = 0; i < 26; ++i) {
			a[0] = (a[0] + base[0][i] * s[i] % mod[0]) % mod[0];
			a[1] = (a[1] + base[1][i] * s[i] % mod[1]) % mod[1]; 
		}
	}
	void change(int id, int c) {
		a[0] = (a[0] - base[0][id] * cnt[id] % mod[0] + mod[0]) % mod[0];
		a[1] = (a[1] - base[1][id] * cnt[id] % mod[1] + mod[1]) % mod[1];
		cnt[id] = c;
		a[0] = (a[0] + base[0][id] * cnt[id] % mod[0] + mod[0]) % mod[0];
		a[1] = (a[1] + base[1][id] * cnt[id] % mod[1] + mod[1]) % mod[1];
	}
	ll get() {
		return a[0] * mod[0] + a[1];
	}
}hs;
ll Hash::base[2][30] = {{0}, {0}};
struct node {
	ll H;
	int nx, f, len, id;
	string t;
	node() { H = nx = f = len = id = 0; } 
	node(ll H, int nx, int f, int len, int id, string t) : H(H), nx(nx), f(f), len(len), id(id), t(t) {}
}a[N];

int main() {
	Hash::init();
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	while (cin >> n) {
		for (int i = 1; i <= n; ++i) cin >> qs[i];
		id = 0; memset(cnt, 0, sizeof cnt);
		cin >> m;
		for (int i = 1; i <= m; ++i) {
			string t; cin >> t;
			for (auto &c : t) ++cnt[c - 'a'];
			hs.gao(cnt);
			ll H = hs.get();
			++id;
			a[id] = node(H, 0, 1, t.size(), id, t);
			for (auto &c : t) cnt[c - 'a'] = 0;
		}
		sort(a + 1, a + 1 + id, [&](const node &x, const node &y) { return x.len < y.len; });
		mp.clear();
		for (int i = 1; i <= id; ++i) {
			mp[a[i].H] = i;
			a[i].id = i; 
		}
		a[0] = node(0, 0, 1, 1, 0, ".");
		hs.gao(cnt);
		for (int i = 0; i < 26; ++i) {
			hs.change(i, 1);
			int nx = 0;
			ll H = hs.get();
			if (mp.count(H)) nx = mp[H];
			if (nx) {
				a[nx].nx = 0;
				a[nx].f = 2;
			}
			hs.change(i, 0);
		}	
		for (int i = 1; i <= id; ++i) {
			for (auto &c : a[i].t) ++cnt[c - 'a'];
			hs.gao(cnt);
			for (int j = 0; j < 26; ++j) {
				hs.change(j, cnt[j] + 1);
				int nx = 0;
				ll H = hs.get();
				if (mp.count(H)) nx = mp[H]; 
				if (nx) { 
					if (a[nx].nx == 0 || a[nx].f < a[i].f + 1) {
						a[nx].f = a[i].f + 1;
						a[nx].nx = i; 
					}
				}
				hs.change(j, cnt[j] - 1);
			}
			for (auto &c : a[i].t) cnt[c - 'a'] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			if (qs[i].size() == 1) {
				cout << 2 << "\n";
				cout << qs[i] << " -> .\n";
				continue;
			}
			for (auto &c : qs[i]) ++cnt[c - 'a'];
			hs.gao(cnt); 
			int p = 0, f = 0; ll H;
			for (int j = 0; j < 26; ++j) if (cnt[j]) {
				hs.change(j, cnt[j] - 1);
				H = hs.get();
				if (mp.count(H)) {
					int now = mp[H];
					if (a[now].f > f) {
						f = a[now].f;
						p = now;
					}
				}
				hs.change(j, cnt[j] + 1);
			}
			if (p) {
				cout << f + 1 << "\n";
				cout << qs[i]; 
				for (int j = 1; j <= f; ++j) {
					cout << " -> " << a[p].t;
					p = a[p].nx;
				} 
				cout << "\n";
			} else {
				cout << 1 << "\n" << qs[i] << "\n";
			}
			for (auto &c : qs[i]) cnt[c - 'a'] = 0;
		}
	}	
	return 0;
}
