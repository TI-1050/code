#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
const int N = 1e5 + 10;
const int M = 1e7 + 10;
int n, q, a[N], pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	pri[0] = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++pri[0]] = i;
		}
		for (int j = 1; j <= pri[0]; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
}
vector <int> pri_fac[N], fac[N];
void get_pri_fac(int x, vector <int> &vec) {
	vec.clear();
	for (int i = 1; i <= pri[0] && 1ll * pri[i] * pri[i] <= x; ++i) {
		if (x % pri[i] == 0) vec.push_back(pri[i]);
		while (x % pri[i] == 0) x /= pri[i];
	}
	if (x != 1) vec.push_back(x);
}
void get_fac(vector <int> &pri_fac, vector <int> &fac) {
	fac.clear();
	int sze = (int)pri_fac.size();
	int S = 1 << sze;
	for (int i = 0; i < S; ++i) {
		int num = 1;
		int cnt_pri = 0;
		for (int j = 0; j < sze; ++j) {
			if ((i >> j) & 1) {
				num *= pri_fac[j];
				++cnt_pri;
			}
		}
		if (cnt_pri & 1) fac.push_back(-num);
		else fac.push_back(num);
	} 
}
struct Mo {
	int block, cnt_qrr; 
	uint tmp[M], ans[N], res; 
	struct Query {
		int id, l, r, bl, br;
		Query() {}
		Query(int id, int l, int r, int bl, int br) : id(id), l(l), r(r), bl(bl), br(br) {}
		bool operator < (const Query &other) const {
			if (bl != other.bl) return bl < other.bl;
			if (bl & 1) return r > other.r;
			return r < other.r;
		}
	}qrr[N];
	void init() {
		block = sqrt(n);
		res = 0; cnt_qrr = 0; 
	} 
	void addquery(int l, int r) {
		++cnt_qrr;
		qrr[cnt_qrr] = Query(cnt_qrr, l, r, l / block, r / block);
	}
	void up(int id, int f) {
		for (auto &it : fac[id]) {
			int T = abs(it);
			res -= tmp[T] * tmp[T] * it; 
			tmp[T] += a[id] / T * f;
			res += tmp[T] * tmp[T] * it; 
		}
	}
	void gao() {
		sort(qrr + 1, qrr + 1 + cnt_qrr);
	  	for (int i = 1, l = 1, r = 0; i <= cnt_qrr; ++i) {
	  		for (; r < qrr[i].r; ++r) up(r + 1, 1);
	  	  	for (; r > qrr[i].r; --r) up(r, -1);
	  	  	for (; l > qrr[i].l; --l) up(l - 1, 1);
	  	  	for (; l < qrr[i].l; ++l) up(l, -1);
	  	 		ans[qrr[i].id] = res;  
	  	}	
	  	for (int i = 1; i <= cnt_qrr; ++i)
			printf("%u\n", ans[i]); 
	}
	void clear() {
		for (int i = 1; i <= n; ++i)
			for (auto &it : fac[i]) 
				tmp[abs(it)] = 0;
	}
}mo;

int main() {
	sieve();
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			get_pri_fac(a[i], pri_fac[i]);
			get_fac(pri_fac[i], fac[i]);
		}
		mo.init();
		for (int i = 1, l, r; i <= q; ++i) {
			scanf("%d%d", &l, &r);
			mo.addquery(l, r); 
		}
		mo.gao(); 
		mo.clear();
	}
	return 0;
}

