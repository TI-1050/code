#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
using pss = pair<string, string>;
#define fi first
#define se second
struct BigInt {
	const static int mod = 10000;
	const static int DLEN = 4;
	int a[100], len;
	BigInt() { memset(a, 0, sizeof a); len = 1; }
	BigInt(int v) { memset(a, 0, sizeof a); len = 0; do { a[len++] = v % mod; v /= mod; } while(v); }
	BigInt(const string &s) {
		memset(a, 0, sizeof a);
		int L = s.size();
		len = L / DLEN;
		if (L % DLEN) len++;
		int index = 0;
		for (int i = L - 1; i >= 0; i -= DLEN) {
			int t = 0;
			int k = i - DLEN + 1;
			if (k < 0) k = 0;
			for (int j = k; j <= i; ++j) 
				t = t * 10 + s[j] - '0';
			a[index++] = t;
		}
	}
	BigInt operator + (const BigInt &b) const {
		BigInt res;
		res.len = max(len, b.len);
		for (int i = 0; i <= res.len; ++i) 
			res.a[i] = 0;
		for (int i = 0; i < res.len; ++i) {
			res.a[i] += ((i < len) ? a[i] : 0) + ((i < b.len) ? b.a[i] : 0);
			res.a[i + 1] += res.a[i] / mod;
			res.a[i] %= mod;
		}
		if (res.a[res.len] > 0) res.len++;
		return res;
	}
	BigInt operator * (const BigInt &b) const {
		BigInt res;
		for (int i = 0; i < len; ++i) {
			int up = 0;
			for (int j = 0; j < b.len; ++j) {
				int temp = a[i] * b.a[j] + res.a[i + j] + up;
				res.a[i + j] = temp % mod;
				up = temp / mod;
			}
			if (up != 0) 
				res.a[i + b.len] = up;
		}
		res.len = len + b.len;
		while (res.a[res.len - 1] == 0 && res.len > 1) res.len--;
		return res;
	}
	void output() {
		printf("%d", a[len - 1]);
		for (int i = len - 2; i >= 0; --i)
			printf("%04d", a[i]);
		puts("");
	}
};
using uint = unsigned int;
const int N = 1e7 + 10;
const uint mod = (1u << 31) - 1;
int a[N], n; uint seed;
BigInt res; string tmp;
bool cmp (const string &x, const string &y) {
	int lenx = x.size(), leny = y.size();
	if (lenx != leny) return lenx < leny;  
	for (int i = 0; i < lenx; ++i) {
		if (x[i] != y[i])
			return x[i] < y[i];
	}
	return 0;
}
pss dfs(int u) {
	if (u > n) return pss("", "");
	int ls = u * 2, rs = u * 2 + 1; 
	//fi up -> down se down -> up
	pss L = dfs(ls), R = dfs(rs); 
	if (ls <= n) {
		tmp = a[ls] + '0';
		L.fi = tmp + L.fi;
		L.se += tmp;  
	}
	if (rs <= n) {
		tmp = a[rs] + '0';
		R.fi = tmp + R.fi;
		R.se += tmp;
	}
	if (ls <= n) res = res + BigInt(max(L.se + R.fi, R.se + L.fi, cmp)); 
	return pss(max(L.fi, R.fi, cmp), max(L.se, R.se, cmp));
}

int main() {
	while (scanf("%d%u", &n, &seed) != EOF) {
		res = BigInt("0");
		for (int i = 2; i <= n; ++i) {
			seed = 1u * 1103515245 * seed + 12345;
			a[i] = (((seed & mod) >> 16) % 9) + 1;
		}
	//	for (int i = 2; i <= n; ++i) cout << a[i] << endl;
		dfs(1);  
		res.output();
	}
	return 0;
}
