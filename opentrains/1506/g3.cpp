#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, a[N], vis[N];

void gao(int l, int r) {
	if (l > r) return;
	int pos = l;
	for (int i = l + 1; i <= r; ++i) {
		if (a[i] < a[pos]) pos = i;
	}
	//左边下降，右边上升
	int isdown = 1, isup = 1;
	for (int i = l + 1; i < pos; ++i) {
		if (a[i] > a[i - 1]) {
			isdown = 0;
			break;
		}
	}
	for (int i = pos + 1; i < r; ++i) {
		if (a[i] > a[i + 1]) {
			isup = 0;
			break;
		}
	}
	if (isdown == 0 && isup == 0) {
		return;
	}
	if (isdown == 1 && isup == 1) {
		for (int i = l; i <= pos; ++i)
			vis[i] = 0;
		for (int i = pos + 1; i <= r; ++i)
			vis[i] = 1;
		return;
	} else if (isdown == 1) {
		for (int i = l; i < pos; ++i)
			vis[i] = 0;
		vis[pos] = 1;
		gao(pos + 1, r);
	} else {
		for (int i = pos + 1; i <= r; ++i)
			vis[i] = 1;
		vis[pos] = 0;
		gao(l, pos - 1);
	}
}

void out(vector <int> &vec) {
	int sze = (int)vec.size();
	printf("%d", sze);
	for (auto it : vec) printf(" %d", it);
	puts("");
}

bool ok() {
	vector <int> up, down;
	for (int i = 1; i <= n; ++i) {
		if (vis[i] == -1) return 0;
		if (vis[i] == 0) {
			if (!down.empty() && a[i] > down.back())
				return 0;
			down.push_back(a[i]);
		} else {
			if (!up.empty() && a[i] < up.back()) 
				return 0;
			up.push_back(a[i]);
		}
	}
	puts("YES");
	out(up); out(down);
	return 1;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) vis[i] = -1; 
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		gao(1, n);
		if (!ok()) {
			puts("NO");
		} 
	}
	return 0;
}
