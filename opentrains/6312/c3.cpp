#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
typedef long long ll;
typedef unsigned long long ull;
struct Hash {
	static ull base[N];
	ull a[N]; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i) 
			base[i] = base[i - 1] * 131;
	}
	inline void gao() { a[0] = 0; }
	inline void add(char c, int it) {
		a[it] = a[it - 1] * 131 + c;
	}
	inline ull get(int l, int r) {
		return a[r] - a[l - 1] * base[r - l + 1];
	}
}hs;
ull Hash::base[N] = {0};
int n, m, k;
vector <int> ch;
char s[N];
map <ull, int> cnt, use; 
map <string, int> id; int cnt_id;
vector <string> fid;
void work() {
	srand(time(0));
	cnt.clear(); use.clear();
	for (int i = 1; i < n; ++i) {
		s[i] = ch[rand() % m] + '0';  
		hs.add(s[i], i);
	}
	++cnt[hs.get(1, n - 1)];
	for (int i = n; i <= n + k - 1; ++i) {
		int tar = -1, Min = m;
		for (auto &c : ch) {
			s[i] = c + '0';
			hs.add(s[i], i);
			if (use.count(hs.get(i - n + 1, i))) continue; 
			int t = cnt[hs.get(i - n + 2, i)];
			if (t < Min) {
				Min = t;
				tar = c;
			}
		}
		assert(tar != -1);  
		s[i] = tar + '0';
		hs.add(s[i], i);
		use[hs.get(i - n + 1, i)] = 1;
		++cnt[hs.get(i - n + 1, i - 1)];
	}
	s[n + k] = 0;
	printf("%s\n", s + 1);
}

void DFS(int cur, string s) {
	if (cur == n) {
		id[s] = ++cnt_id;
		fid.push_back(s);
		return;
	}
	for (auto &c : ch) {
		s += c + '0';
		DFS(cur + 1, s);
		s.pop_back();
	}
}

struct Edge{int v, nx, vis; }e[N * 10]; int h[N];
inline void addedge(int u, int v) { e[++*h] = {v, h[u], 0}; h[u] = *h; }
char ans[N * 10]; int cnt_ans;  
void DFS2(int u) {
	for (int i = h[u]; i; i = e[i].nx) if (!e[i].vis) {
		e[i].vis = 1;
		int v = e[i].v;
		DFS2(v);
		ans[++cnt_ans] = fid[v].back();
	}
}

int main() {
	Hash::init();
	while (scanf("%d%d%d", &n, &m, &k) != EOF) { 
		hs.gao(); 
		ch.clear(); ch.resize(m);
		for (auto &it : ch) cin >> it; 
		if (n == 1) { 
			for (int i = 0; i < k; ++i) s[i] = ch[i] + '0'; 
			s[k] = 0;
			printf("%s\n", s);
			continue; 
		}
		if (m == 1) {
			assert(k == 1);
			for (int i = 1; i <= n; ++i) s[i] = ch[0] + '0';
			s[n + 1] = 0; 
			printf("%s\n", s + 1);
			continue;
		}
		ll tot = 1;
		for (int i = 1; i < n; ++i) {
			tot *= m;
			if (tot > k * 2) break;
		}
		if (tot > k * 2) work();
		else {
			id.clear(); fid.clear(); cnt_id = 0;
			fid.push_back("");
			DFS(1, "");
			memset(h, 0, sizeof h);
			for (int i = 1; i <= cnt_id; ++i) {
				string t = fid[i];
				t.erase(0, 1);
				for (auto &c : ch) {
					t += c + '0';
					addedge(i, id[t]);
					t.pop_back();
				}
			}
			cnt_ans = 0;
			DFS2(1);
			assert(cnt_ans >= (n + k - (n - 1) - 1));
			reverse(ans + 1, ans + 1 + cnt_ans);
			ans[n + k - (n - 1)] = 0;
			cout << fid[1];
			printf("%s\n", ans + 1);
		}
	}
	return 0;
}
