#include <bits/stdc++.h>
using namespace std;
using uint = unsigned int;
using ull = unsigned long long;
const int N = 1e7 + 10;
int n, m; uint s;
vector <int> f;
struct E {
	int u, v, id; ull w;
	E() {}
	E(int u, int v, int id, ull w) : u(u), v(v), id(id), w(w) {}
	bool operator < (const E &other) const {
		return w < other.w; 
	}
}; 
vector <vector<E>> G;
uint getNext() {
	s = s ^ (s << 13);
	s = s ^ (s >> 17);
	s = s ^ (s << 5);
	return s;
}

int find(int u) { return f[u] == u ? u : f[u] = find(f[u]); }
bool merge(int u, int v) {
	int fu = find(u), fv = find(v);
	if (fu == fv) return false;
	f[u] = v;
	return true;
}

int main() {
	while (scanf("%d%d%u", &n, &m, &s) != EOF) {
		f.clear(); f.resize(n);
		for (int i = 0; i < n; ++i) {
			f[i] = i;
		}
		G.clear(); G.resize((1 << 21) + 10);
		for (int i = 0; i < m; ++i) {
			int u = getNext() % n;
			int v = getNext() % n;
			ull w = getNext() / 4;
			w = w * getNext();
			G[w >> 43].push_back(E(u, v, i, w));
		}
		for (auto &vec : G) if (!vec.empty()) {
			sort(vec.begin(), vec.end()); 
			for (auto &it : vec) {
				int u = it.u, v = it.v; 
				if (merge(u, v)) {
					it.w = 0; 
				//	ans[id / 32] |= (1 << (id % 32));
				}
			}
		}
		int sze = (m + 31) / 32;
		f.clear(); f.resize(sze);
		for (auto &vec : G) if (!vec.empty()) {
			for (auto &it : vec) {
				int id = it.id;
				if (it.w == 0) {
					f[id / 32] |= (1 << (id % 32));
				}
			}
		}
		for (int i = 0; i < sze; ++i)
			printf("%u%c", f[i], " \n"[i == sze - 1]);
	}
	return 0;
}
