#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;
const int INF = 0x3f3f3f3f;

char str[N];

struct postOffice {
	int o;
	int vis;

	void input() {
		scanf("%s", str);
		if (str[0] == '?') vis = 0;
		else {
			vis = 1;
			o = 0;
			for (int i = 0, len = strlen(str); i < len; ++i) {
				o = o * 10 + str[i] - '0';
			}
		}
	}
}post[N];

struct Edge {
	int to, nxt, w;

	Edge() {}
	
	Edge(int to, int nxt ,int w): to(to), nxt(nxt), w(w) {}
}edge[N << 4];

struct node {
	int a, b, d;

	node() {}

	node(int a, int b, int d): a(a), b(b), d(d) {}

	void input() {
		scanf("%d %d %d", &a, &b, &d);
	}
}qrr[N << 1];

int n, m;
int head[N], tot;
int dis[N], inq[N], cnt[N];
int res[N];

void Init() {
	memset(head, -1, sizeof head);
	tot = 0;
}

void addedge(int u, int v, int w) {
	edge[tot] = Edge(v, head[u], w); head[u] = tot++;
	edge[tot] = Edge(u, head[v], w); head[v] = tot++;
}

bool SPFA() {
	for (int i = 0; i <= n; ++i) {
		dis[i] = 0;
		if (post[i].vis == 1) dis[i] = post[i].o;
		inq[i] = 0, cnt[i] = 0;
	}
	queue<int> q;
	q.push(0);
	dis[0] = 0;
	cnt[0] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = 0;
		for (int i = head[u]; ~i; i = edge[i].nxt) {
			int v = edge[i]. to, w = edge[i].w;
			if (dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
					if (++cnt[v] > n) return false;
				}
			}
		}
	}
	return true;
}

bool check(int T) {
	for (int i = 0; i <= n; ++i) head[i] = -1;
	for (int i = 1; i <= m; ++i) {
		//addedge(qrr[i].a, qrr[i].b, (T - qrr[i].d));
		//addedge(qrr[i].b, qrr[i].a, -(T - qrr[i].d));
	}
	if (SPFA()) {
		for (int i = 1; i <= n; ++i) res[i] = dis[i];
		return true;
	} else {
		return false;
	}
}

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		Init();
		for (int i = 1; i <= n; ++i) {
			post[i].input();
		}
		for (int i = 1; i <= m; ++i) {
			qrr[i].input();
		}
		int l = 0, r = INF, T = -1; 
		while (r - l >= 0) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				T = mid;
			} else {
				l = mid + 1;
			}
		}
		printf("%d\n", T);
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", res[i], " \n"[i == n]);
		}
	}
	return 0;
}
