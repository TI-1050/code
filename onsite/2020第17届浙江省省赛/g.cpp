#include <bits/stdc++.h>
using namespace std;

const int N = 4e3 + 10;
#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> 
void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}
using db = double;

struct node {
	int x, y, h;
	
	node() {}
	
	node(int x, int y, int h): x(x), y(y), h(h) {}
	
	void input() {
		scanf("%d %d %d", &x, &y, &h);
	}
	
	bool operator < (const node &other) {
		return h < other.h;	
	}
}a[N];

int n;
int sx, sy, ex, ey;
int vf, vp, vh;
db f[N];

db dis(int i, int j) {
	db res = (a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y);
	return sqrt(res);
}

db calc(int i, int j) {
	db t = dis(i, j) / vh;
	db d = t * vp;
	if (a[i].h - vp <= 0) return 1e9;
	t += d / (a[i].h - vp);
	return t;
}

int main() {
	int _T;
	scanf("%d", &_T);
	while (_T--) {
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		scanf("%d %d %d", &vf, &vp, &vh);
		scanf("%d", &n);
		++n;
		for (int i = 1; i <= n; ++i) {
			a[i].input();
		}
		++n;
		a[n] = node(ex, ey, 100000);
		sort(a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++i) f[i] = 1e9;
		int st = 0;
		for (int i = 1; i <= n; ++i) {
			if (a[i].x == sx && a[i].y == sy) st = i;
		}
		f[st] = 0;
		for (int i = st; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				f[j] = min(f[j], f[i] + calc(i, j));
			}
		}		
		printf("%.10f\n", f[n]);
	}
	return 0;
}
