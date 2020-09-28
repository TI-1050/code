#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int x[2], a, b, mod;
char s[N];

inline void chadd(ll &x, ll y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}
template <int N, int M>
struct Matrix {
	ll a[N][M];
	Matrix() {}
	ll* operator[] (int x) { return a[x]; }
	void init() { memset(a, 0, sizeof a); }
    void set() {
        memset(a, 0, sizeof a);
    	for (int i = 0; i < min(N, M); ++i) a[i][i] = 1;
    }
	void print() {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				printf("%d%c", a[i][j], " \n"[j == M - 1]);
			}
		}
	}
	template <int _N, int _M> 
    Matrix operator * (const Matrix <_N, _M> &other) const {
        Matrix res = Matrix<N, _M>();
		res.init();
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < _M; ++j) {
				for (int k = 0; k < M; ++k) {
					chadd(res.a[i][j], a[i][k] * other.a[k][j] % mod);
				}
			}
		}
		return res;
    }
	Matrix operator ^ (long long n) {
		Matrix base = *this;
		Matrix res = base; res.set();
		while (n) {
			if (n & 1) res = res * base;
			base = base * base;
			n >>= 1;
		}
		return res;
	}
	Matrix qpow(long long n, Matrix base, Matrix res) {
		while (n) {
			if (n & 1) res = res * base;
			base = base * base;	
			n >>= 1;
		}
		return res;
	} 
	Matrix qpow(char *s, Matrix base, Matrix res) {
		for (int i = strlen(s) - 1; i >= 0; --i) {
			res = qpow(s[i] - '0', base, res);
			base = base ^ 10;
		}
		return res;
	}
};

int main() {
	while (scanf("%d%d%d%d", x, x + 1, &a, &b) != EOF) {
		scanf("%s%d", s + 1, &mod);
		Matrix <2, 2> base, res;
		base.init(); res.init();
		base[0][0] = a; base[0][1] = 1;
		base[1][0] = b; base[1][1] = 0;
		res[0][0] = x[1];
		res[0][1] = x[0];
		res = base.qpow(s + 1, base, res);
		printf("%lld\n", res[0][1]);
	}
	return 0;
}
