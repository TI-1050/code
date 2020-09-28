#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n;
struct node {
	int id, v, vis;
	node() {}
	void scan(int _id) {
		id = _id;
		scanf("%d", &v);
		vis = -1;
	}
	bool operator < (const node &other) const {
		return id < other.id;
	}
}a[N];

void gao(int l, int r) {
	if (l > r) return;
//	cout << l << " " << r << endl;
	int pos = l;
	for (int i = l + 1; i <= r; ++i) {
		if (a[i].v < a[pos].v) pos = i;
	} 
	//左边下降，右边上升
	int isdown = 1, isup = 1;
	for (int i = l + 1; i < pos; ++i) {
		if (a[i].v > a[i - 1].v) {
			isdown = 0;
			break;
		}
	}
	for (int i = pos + 1; i < r; ++i) {
		if (a[i].v > a[i + 1].v) {
			isup = 0;
			break;
		}
	}
	if (isdown == 0 && isup == 0) { 
		return;
	}
	if (isdown == 1 && isup == 1) {
		for (int i = l; i < pos; ++i)
			a[i].vis = 0;
		for (int i = pos + 1; i <= r; ++i)
			a[i].vis = 1;
		if (pos == l) {
			a[pos].vis = 1;
		} else  {
			a[pos].vis = 0;
		}	
		return;
	} else if (isdown == 1) {
		for (int i = l; i < pos - 1; ++i)
			a[i].vis = 0;
		a[pos].vis = 1; 
		if (pos != l) {
			swap(a[pos], a[pos - 1]);
			gao(pos, r);	
		} else {
			gao(pos + 1, r);
		}
	} else {
		for (int i = pos + 2; i <= r; ++i)
			a[i].vis = 1;
		a[pos].vis = 0;
		if (pos != r) {
			swap(a[pos], a[pos + 1]);
			gao(l, pos);
		} else {
			gao(l, pos - 1);
		}
	}
}

void out(vector <int> &vec) {
	int sze = (int)vec.size();
	printf("%d", sze);
	for (auto it : vec) printf(" %d", it);
	puts("");
}

bool ok() {
	sort(a + 1, a + 1 + n);
	vector <int> up, down;
	for (int i = 1; i <= n; ++i) {
		if (a[i].vis == -1) return 0;
		if (a[i].vis == 0) {
			if (!down.empty() && a[i].v > down.back())
				return 0;
			down.push_back(a[i].v);
		} else {
			if (!up.empty() && a[i].v < up.back()) 
				return 0;
			up.push_back(a[i].v);
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
		for (int i = 1; i <= n; ++i) a[i].scan(i); 
		gao(1, n);
		if (!ok()) {
			puts("NO");
		} 
	}
	return 0;
}
