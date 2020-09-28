#include <bits/stdc++.h>
using namespace std;

#define db long double
const int N = 1e5 + 10;
int n, cnt, last;  
void out(int x) {
	cnt += x;
	printf("%d\n", x);
	fflush(stdout);
}

struct BIT { 
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
}bit;

db f[N], sumf[N];
void init() {
  f[1] = 1;
  sumf[1] = 1;
  for (int n = 2; n < N; ++n) {
    int k = lower_bound(f, f + n, f[n - 1] - 1) - f;

    f[n] = ((sumf[n - 1] - sumf[k - 1] + (n - k)) + k * f[n - 1]) / n;
    
    sumf[n] = sumf[n - 1] + f[n];
  }
  for (int i = 1; i < N; ++i) f[i] = sqrt(i); 
}

int main() {
	init();  
	while (scanf("%d", &n) != EOF) {
		cnt = 0; last = 0; bit.init();
		for (int i = 1; i <= n; ++i) bit.update(i, 1);
		for (int i = 1, x; i <= n; ++i) {  
			scanf("%d", &x); 
			if (x < last) {
				out(0);
				continue;
			}	
			
			int rem = bit.query(last + 1, n);
			int to = bit.query(x + 1, n);
			if (f[to] + 1 >= f[rem - 1]) {
				out(1);
				last = x;
			} else out(0);
			bit.update(x, -1);
		}
	//	cout << cnt << endl;
	}
	return 0;
}
