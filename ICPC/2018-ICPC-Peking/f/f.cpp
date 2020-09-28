#include <bits/stdc++.h>
using namespace std;
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
using ll = long long;
using ull = unsigned long long;
const int N = 5e4 + 10, M = 2e5 + 10;
struct Bitset {
    #define W (64)

    int n;
    ull bits[N / W + 10];
    int num[N / W + 10];

    void preWork() {
        for(int i = 0;i <= n / W; ++i) num[i] = __builtin_popcountll(bits[i]);
        for(int i = n / W - 1;i >= 0; --i) num[i] += num[i + 1];
    }

    int ask(int x) {
        if(x > n) return 0; 
        int blockid = x / W;
        int ans = __builtin_popcountll(bits[blockid]>>(x%W));
        blockid++;
        if(blockid <= n/W) ans += num[blockid];
        return ans;
    }

    int ask(int l,int r) {
		if (l > r) return 0;
        return ask(l) - ask(r+1);
    }

	void Xor(const Bitset &t) {
		for (int i = 0; i <= n / W; ++i) bits[i] ^= t.bits[i]; 
	}

	void And(const Bitset &t) {
		for (int i = 0; i <= n / W; ++i) bits[i] &= t.bits[i];
	}

    void Or(const Bitset &t) {
        for(int i = 0; i <= n / W; ++i) bits[i] |= t.bits[i];
    }

    void Copy(const Bitset &t) {
        n = t.n;
        for(int i = 0; i <= n / W; ++i) bits[i] = t.bits[i];
    }

    void Set(int x) { 
        bits[x / W] |= 1llu << (x % W);
    }

	void Reset(int x) {
		Set(x);
		bits[x / W] ^= 1llu << (x % W);
	}

    void init(int _n) {
        n = _n + 1; //n++;
        for(int i = 0; i <= n / W; i++) bits[i] = 0;
    }

    void print() {
        for(int i = 0; i <= n; ++i) { 
            if(bits[i / W] >> (i % W) & 1) 
                printf("%d ", i);
        }
        puts("");
    }

    #undef W
}bs[N], bg[N];
int n, m, q, f[N];
vector <vector<int>> G; 
struct Tarjan {
	int Low[N], DFN[N], sta[N], Belong[N], num[N], d[N], scc; 
	bool Insta[N];
	void dfs(int u) {
		Low[u] = DFN[u] = ++*Low;
		sta[++*sta] = u;
		Insta[u] = 1;
		for (auto &v : G[u]) {
			if (!DFN[v]) {
				dfs(v);
				Low[u] = min(Low[u], Low[v]);
			} else if (Insta[v]) {
				Low[u] = min(Low[u], DFN[v]);
			}
		}
		if (Low[u] == DFN[u]) {
			++scc;
			int v;
			do {
				v = sta[(*sta)--];
				Insta[v] = 0;
				Belong[v] = scc;
				++num[scc];
			} while (v != u);
		}
	}
	void gao() {
		memset(DFN, 0, sizeof DFN);
		memset(Insta, 0, sizeof Insta);
		memset(num, 0, sizeof num);
		memset(d, 0, sizeof d);
		scc = *sta = *Low = 0;
		for (int i = 1; i <= n; ++i) if (!DFN[i]) dfs(i);	
		vector <vector<int>> H(scc + 1), bk(scc + 1);
		for (int i = 1; i <= scc; ++i) bg[i].init(n); 
		for (int u = 1; u <= n; ++u) {
			bk[Belong[u]].push_back(u);
			for (auto &v : G[u]) {
				if (Belong[u] == Belong[v]) {
					continue;
				}
				H[Belong[v]].push_back(Belong[u]);
				++d[Belong[u]];
			}
		}
		queue <int> que;
		for (int i = 1; i <= scc; ++i) if (!d[i]) que.push(i);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (auto &it : bk[u]) {
				bg[u].Set(it); 
			}
			for (auto &v : H[u]) {
				bg[v].Or(bg[u]); 
				if (--d[v] == 0) {
					que.push(v);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			bs[i] = bg[Belong[i]]; 
			bs[i].Set(i);
			bs[i].preWork();
		}
	}
}tarjan;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d", &n, &m, &q);
		G.clear(); G.resize(n + 1); 
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
		}
		tarjan.gao();
	//	for (int i = 1; i <= n; ++i) bs[i].print();
		int len = 1, cnt = 1;
		while (len < n * 2) len <<= 1, ++cnt;  
		while (q--) {
			ll K; int res = 0; scanf("%lld", &K); --K; 
			memset(f, 0, sizeof f); 
			for (int i = cnt; i >= 0; --i) {
				//试着放1 
				ll num = 0;
				int bit = 1 << i; 
				for (int j = 1; j <= n; ++j) {
					if (((j >> i) & 1) == 0) { 
						f[j] |= bit; 
					}
					num += bs[j].ask(f[j], min(n, (f[j] | (bit - 1)))); 
					if (((j >> i) & 1) == 0) {
						f[j] ^= bit;
					}
				}
				if (K >= num) {
					K -= num; 
					for (int j = 1; j <= n; ++j) {
						if ((j >> i) & 1) {
							f[j] |= bit;
						}
					}
				} else {
					res |= bit; 
					for (int j = 1; j <= n; ++j) {
						if (((j >> i) & 1) == 0) {
							f[j] |= bit;
						}
					}
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
