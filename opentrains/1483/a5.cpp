#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, cnt, a[N];
mt19937 rd(time(0));
void out(int x) {
	cnt += x;
	printf("%d\n", x);
	fflush(stdout);
}

struct BIT {
	int a[N]; 
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) {
			a[x] = max(a[x], v);
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res = max(res, a[x]);
		}
		return res;
	}
}bit;

struct BIT2 {
	int a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, int v) {
		for (; x < N; x += x & -x) a[x] += v;
	}
	int query(int x) { 
		int res = 0;
		for (; x > 0; x -= x & -x) res += a[x];
		return res;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}bit2;

int get(int l, int r) {
	return rd() % (r - l + 1) + l;
}

int main() {
	int C = 188;  
	int tar = 410;  
	while (scanf("%d", &n) != EOF) {
		cnt = 0; 
		int pre = 0, nx = C; bit2.init(); bit.init(); 
		for (int i = 1, x; i <= n; ++i) {  
			scanf("%d", &x); a[i] = x;  	
			int f = bit.query(a[i] - 1); 
			if (x > pre) {
				int num = n - x + 1 - bit2.query(x, n);
				if (x <= nx && f + 1 - cnt <= 280 && cnt + num >= tar) {
					out(1); 
					pre = x;
					if (cnt >= 188) nx += 215;
					else nx += 245;  
				} else out(0);
			} else out(0);
			bit.update(a[i], f + 1);
			bit2.update(a[i], 1); 
		}
	//	cout << cnt << endl;
	//	cout << bit.query(n) << endl;
	}
	return 0;
}
