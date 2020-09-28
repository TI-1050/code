#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 5010
#define M 20000
const ll p = 1e9 + 7;
const double PI = acos(-1.0);
struct Complex {
	double x, y;
	Complex(double _x = 0.0, double _y = 0.0) {
		x = _x;
		y = _y;
	}
	Complex operator - (const Complex &b) const {
		return Complex(x - b.x, y - b.y);
	}
	Complex operator + (const Complex &b) const {
		return Complex(x + b.x, y + b.y);
	}
	Complex operator * (const Complex &b) const {
		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
}x1[M], x2[M];
void change(Complex y[], int len) {
	int i, j, k;
	for (i = 1, j = len / 2; i < len - 1; ++i) {
		if (i < j) {
			swap(y[i], y[j]);
		}
		k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) {
			j += k;
		}
	}
}
void FFT(Complex *y, int len, int on) {
	change(y, len);
	for (int h = 2; h <= len; h <<= 1) {
		Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
		for (int j = 0; j < len; j += h) {
			Complex w(1.0);
			for (int k = j; k < j + h / 2; ++k) {
				Complex u = y[k];
				Complex t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1) {
		for (int i = 0; i < len; ++i) {
			y[i].x /= len;
		}
	}
}


int n, m, k, len;
vector < vector<int> > G;
int f[N][N];
int vis[N];  

void DFS(int u, int fa) {
	if (vis[u]) {
		f[u][0] = 1;
	}
	for (auto v : G[u]) if (v != fa) {
		DFS(v, u);
		for (int i = 0; i < len; ++i) {
			x1[i] = x2[i] = Complex(0, 0);
		}
		for (int i = 0; i <= k; ++i) {
			x1[i] = Complex(f[u][i], 0);
			x2[i] = Complex(f[v][i], 0);
		}
		FFT(x1, len, 1);
		FFT(x2, len, 1);
		for (int i = 0; i < len; ++i) {
			x1[i] = x1[i] * x2[i];
		}
		FFT(x1, len, -1);
		for (int i = 0; i <= k; ++i) {
			if (i) {
				(f[u][i] += (ll)(x1[i - 1].x + 0.5) % p + f[v][i - 1]) %= p;
			}
		}
	}
}

void init() {
	G.clear();
	G.resize(n + 1);
	memset(vis, 0, sizeof vis);
	memset(f, 0, sizeof f);
}
int main() {
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		init();
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		for (int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			vis[x] = 1;
		}
		len = 1;
		while (len < 2 * k + 5) len <<= 1;
		DFS(1, 1);
		ll res = 0;
		for (int i = 0; i <= k; ++i) {
			(res += f[1][i]) %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
