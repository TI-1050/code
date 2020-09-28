#include <bits/stdc++.h>

using namespace std;

using ll = __int128;

ll gcd(ll a, ll b) {
	if (a == 0 || b == 0) return a + b;
	else return __gcd(a, b);
}

ll abs(ll x) {
	if (x < 0) return -x;
	return x;
}

int sta[1100];
void pt(ll x) {
	if (x < 0) putchar('-'), x = -x;
	*sta = 0;
	if (!x) sta[++*sta] = 0;
	while (x) {
		sta[++*sta] = x % 10;
		x /= 10;
	}
	for (int i = *sta; i >= 1; --i)
		putchar(sta[i] + '0');
}

struct Frac {
	ll x, y;

	void sim() {
		ll G = gcd(abs(x), abs(y));
		x /= G;
		y /= G;
		if (x * y < 0) x = -abs(x), y = abs(y);
		else x = abs(x), y = abs(y);
	}

	Frac() {}
	
	Frac(ll x, ll y) : x(x), y(y) { sim(); }

	Frac operator+(const Frac &u) {
		ll p = x * u.y + y * u.x, q = u.y * y;
		return Frac(p, q);
	}

	Frac operator-(const Frac &u) {
		ll p = x * u.y - y * u.x, q = u.y * y;
		return Frac(p, q);
	}

	Frac operator*(const Frac &u) {
		ll p = x * u.x, q = y * u.y;
		return Frac(p, q);
	}

	Frac operator/(const Frac &u) {
		ll p = u.y * x, q = y * u.x;
		return Frac(p, q);
	}

	bool operator!=(const Frac &other) {
		return x * other.y != y * other.x;
	}

	bool operator==(const Frac &other) {
		return x * other.y == y * other.x;
	}

	void out() {
		pt(x); putchar('/'); pt(y); 
	}
};

int n, m;
char str[110];
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

struct node {
	Frac x;
	int vis;

	node() {
	//	x = Frac(0, 1);
	}

	node(Frac x, int vis): x(x), vis(vis){}

	void input() {
		scanf("%s", str);
		if (str[0] == '?') vis = 0;
		else {
			vis = 1;
			int num = 0;
			int sgn = (str[0] == '-');
			for (int i = sgn; str[i]; ++i) {
				num = num * 10 + str[i] - '0';
			}
			if (sgn) num = -num;
			x = Frac(num, 1);
		}
	}
}a[20][20], b[20][20];

bool judge(int x, int y) {
	if (x >= 1 && x <= n && y >= 1 && y <= m) return true;
	else return false;
}

bool ok(int x, int y) {
	if (judge(x + 1, y) && judge(x - 1, y)) {
		if (a[x + 1][y].vis == 1 && a[x - 1][y].vis == 1) {
			if ((a[x][y].x) != ((a[x + 1][y].x + a[x - 1][y].x) / Frac(2, 1))) {
				return false;
			}
		}
	}
	if (judge(x, y + 1) && judge(x, y - 1)) {
		if (a[x][y + 1].vis == 1 && a[x][y - 1].vis == 1) {
			if ((a[x][y].x) != ((a[x][y + 1].x + a[x][y - 1].x) / Frac(2, 1))) {
				return false;
			}
		}
	}
	return true;
}

int preWork() {
	for (int cas = 1; cas <= n * m + 1; ++cas) {
		bool F = false;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[i][j].vis == 1) {
					if (!ok(i, j)) return -1;
				} else {
					for (int o = 0; o < 4; ++o) {
						int dx = i + dir[o][0], dy = j + dir[o][1];
						int ddx = i - dir[o][0], ddy = j - dir[o][1];
						if (judge(dx, dy) && judge(ddx, ddy) && a[dx][dy].vis == 1 && a[ddx][ddy].vis == 1) {
							a[i][j].x = (a[ddx][ddy].x + a[dx][dy].x) / (Frac(2, 1));
							a[i][j].vis = 1;
							F = true;
							break;
						}
						dx = i + dir[o][0], dy = j + dir[o][1];
						ddx = i + dir[o][0] * 2, ddy = j + dir[o][1] * 2;
						if (judge(dx, dy) && judge(ddx, ddy) && a[dx][dy].vis == 1 && a[ddx][ddy].vis == 1) {
							a[i][j].x = (a[dx][dy].x * Frac(2, 1)) - a[ddx][ddy].x;
							a[i][j].vis = 1;
							F = true;
							break;
						}
					}
				}
			}
		}
		if (!F) break;
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (a[i][j].vis == 0) cnt++;
		}
	}
	return cnt;
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				a[i][j].input();
			}
		}
		int S = preWork();
		if (S == -1) {
			puts("None");
		} else if (S == 0) {
			puts("Unique");
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if (j != 1) putchar(' ');
					a[i][j].x.out();
				}
				puts("");
			}
		} else {
			puts("Multiple");
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					b[i][j] = a[i][j];
				}
			}
			//1
			S = preWork();
			while (true) {
				bool F = false;
				for (int i = 1; i <= n; ++i) {
					for (int j = 1; j <= m; ++j) {
						if (a[i][j].vis == 0) {
							a[i][j].vis = 1;
							a[i][j].x = Frac(1, 1);
							F = true;
							break;
						}
					}
					if (F) break;
				}
				S = preWork();
				assert(S != -1);
				if (S == 0) break;
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if (j != 1) putchar(' ');
					a[i][j].x.out();
				}
				puts("");
			}
			puts("and");
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					a[i][j] = b[i][j];
				}
			}
			S = preWork();
			while (true) {
				bool F = false;
				for (int i = 1; i <= n; ++i) {
					for (int j = 1; j <= m; ++j) {
						if (a[i][j].vis == 0) {
							a[i][j].vis = 1;
							a[i][j].x = Frac(2, 1);
							F = true;
							break;
						}
					}
					if (F) break;
				}
				S = preWork();
				assert(S != -1);
				if (S == 0) break;
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if (j != 1) putchar(' ');
					a[i][j].x.out();
				}
				puts("");
			}
		}
	}
	return 0;
}
