#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 10;
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
bool work() {
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
		if (tar == -1) return false;
		s[i] = tar + '0';
		hs.add(s[i], i);
		use[hs.get(i - n + 1, i)] = 1;
		++cnt[hs.get(i - n + 1, i - 1)];
	}
	return true;
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
		while (!work());
		s[n + k] = 0;
		printf("%s\n", s + 1);
	}
	return 0;
}
