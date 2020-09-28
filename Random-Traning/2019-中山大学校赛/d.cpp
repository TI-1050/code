#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
#define INF 0x3f3f3f3f
int n, m, p, q;
struct qnode {
	int x[2], y[2];
	void scan() {
		scanf("%d%d%d%d", &x[0], &y[0], &x[1], &y[1]); 
	}
}a[N], b[N];
int bb[N << 2];
int get(int x, int *b) {
	return lower_bound(b + 1, b + 1 + b[0], x) - b;
}
void Hash() {
	bb[0] = 0;
	for (int i = 1; i <= p; ++i) {
		for (int j = 0; j < 2; ++j) {
			bb[++bb[0]] = a[i].x[j];
		}
	}
	for (int i = 1; i <= q; ++i) {
		for (int j = 0; j < 2; ++j) {
			bb[++bb[0]] = b[i].x[j];
		}
	}
	sort(bb + 1, bb + 1 + bb[0]);
	bb[0] = unique(bb + 1, bb + 1 + bb[0]) - bb - 1;
	n = bb[0];
	for (int i = 1; i <= p; ++i) {
		for (int j = 0; j < 2; ++j) {
			a[i].x[j] = get(a[i].x[j], bb);
		}
	}
	for (int i = 1; i <= q; ++i) {
		for (int j = 0; j < 2; ++j) {
			b[i].x[j] = get(b[i].x[j], bb);
		}
	}

	bb[0] = 0;
	for (int i = 1; i <= p; ++i) {
		for (int j = 0; j < 2; ++j) {
			bb[++bb[0]] = a[i].y[j];
		}
	}
	for (int i = 1; i <= q; ++i) {
		for (int j = 0; j < 2; ++j) {
			bb[++bb[0]] = b[i].y[j];
		}
	}
	sort(bb + 1, bb + 1 + bb[0]);
	bb[0] = unique(bb + 1, bb + 1 + bb[0]) - bb - 1;
	m = bb[0];
	for (int i = 1; i <= p; ++i) {
		for (int j = 0; j < 2; ++j) {
			a[i].y[j] = get(a[i].y[j], bb);
		}
	}
	for (int i = 1; i <= q; ++i) {
		for (int j = 0; j < 2; ++j) {
			b[i].y[j] = get(b[i].y[j], bb);
		}
	}
}
struct node {
	int x, y, op;
	node () {}
	node (int x, int y, int op) : x(x), y(y), op(op) {}
};
vector <int> vec[N << 2];
int f[N << 2];
vector <node> qrr;  

void init() {
	memset(f, 0, sizeof f);
	for (int i = 0; i <= n + 1; ++i) {
		vec[i].resize(m + 1);
	}
}
int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		scanf("%d", &p);
		for (int i = 1; i <= p; ++i) {
			a[i].scan();		
		}
		scanf("%d", &q);
		for (int i = 1; i <= q; ++i) {
			b[i].scan();
		}
		Hash(); init();
		
		for (int i = 1; i <= p; ++i) {
			qrr[a[i].x[0]].emplace_back(a[i].y[0], a[i].y[1], 1);
			qrr[a[i].x[1] + 1].emplace_back(a[i].y[0], a[i].y[1], -1);
		}
		for (int i = 1; i <= n; ++i) {
			for (auto it : qrr[i]) {
				f[it.x] += it.op;
				f[it.y + 1] -= it.op;
			}
			for (int j = 1; j <= m; ++j) {
				f[j] += f[j - 1];
				vec[i][j] = (f[j] >= 1);
				vec[i][j] += vec[i][j - 1] + vec[i - 1][j] - vec[i - 1][j - 1];
			}
		}
		for (int i = 1; i <= q; ++i) {
			int x[2] = {b[i].x[0], b[i].x[1]};
			int y[2] = {b[i].y[0], b[i].y[1]};
			int area = vec[x[1]][y[1]] - vec[x[0] - 1][y[1]] - vec[x[1]][y[0] - 1] + vec[x[0] - 1][y[0] - 1];	
			if (area == (y[1] - y[0] + 1) * (x[1] - x[0] + 1)) {
				puts("YES");
			} else {
				puts("NO");
			}
		}
		for (int i = 0; i <= n + 1; ++i) {
			vec[i].clear();
		}
		qrr.clear(); 
	}
	return 0;
}
