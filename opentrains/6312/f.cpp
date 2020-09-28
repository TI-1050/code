#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e5 + 10;

int n, m;
int a[N], b[N], nxt[N];
ll sa[N], sb[N];
vector<int> res;

int main() {
	while (scanf("%d %d", &n, &m) != EOF) {
		res.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sa[i] = sa[i - 1] + a[i];
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", b + i);
			sb[i] = sb[i - 1] + b[i];
		}
		int p = 0;
		for (int i = 1; i <= n; ++i) {
			if (sa[i] <= m) p = i;
		}
		nxt[p] = p;
		int lst = p;
		for (int i = p - 1; i >= 1; --i) {
			nxt[i] = lst;
			if (b[i] > b[lst]) {
				lst = i;
			} 
		}
		int have = 1;
		ll Time = sb[lst - 1];
		while (lst < p) {
			while (have <= p && sa[have] <= Time + b[lst]) {
				have++;
				Time += b[lst];
				if (Time > m) break;
				res.push_back(Time);
			}
			Time += sb[nxt[lst] - 1] - sb[lst - 1];
			lst = nxt[lst];
		}
		if (lst == p) while (have <= p && sa[have] <= Time + b[lst]) {
			have++;
			Time += b[lst];
			if (Time > m) break;
			res.push_back(Time);
		}
		if (Time + b[p] > m) {
			int len = res.size();
			printf("%d\n", len);
			for (int i = 0; i < len; ++i) {
				printf("%d%c", res[i],  " \n"[i == len - 1]);
			}
		} else {
			puts("-1");
		}
	}
	return 0;
}
