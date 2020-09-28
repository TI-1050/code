#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ull = unsigned long long;
int n, m; uint s;
vector <int> f;
struct E {
	ull w; int id;
	E() {}
	E(ull w, int id) : w(w), id(id) {}
	bool operator < (const E &other) const {
		return w < other.w; 
	}
};
vector <E> e;
uint getNext() {
	s = s ^ (s << 13);
	s = s ^ (s >> 17);
	s = s ^ (s << 5);
	return s;
}

int main() {
	while (scanf("%d%d%u", &n, &m, &s) != EOF) {
		e.clear(); e.resize(n + 1);
		for (int i = 0; i < n; ++i) {
			e[i] = E(-1, 0);
		}
		for (int i = 0; i < m; ++i) {
			int u = getNext() % n;
			int v = getNext() % n;
			ull w = getNext() / 4;
			w = w * getNext();
			if (u == v) continue;
			e[u] = min(e[u], E(w, i));
			e[v] = min(e[v], E(w, i));
		}
		int sze = (m + 31) / 32;
		f.clear(); f.resize(sze);
		for (int i = 0; i < n; ++i) {
			if (e[i].id) {
				f[e[i].id / 32] |= (1 << (e[i].id % 32));
			}
		}
		for (int i = 0; i < sze; ++i)
			printf("%u%c", f[i], " \n"[i == sze - 1]);
	}
	return 0;
}
