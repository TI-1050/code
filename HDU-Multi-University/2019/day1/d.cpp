#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
#define db double
int n;
int l[N], s[N], v[N];
db f[N];

template <class T> 
inline void read(T &x) {
	x = 0; char ch;
	while (!isdigit(ch = getchar()));
	while (isdigit(ch)) {
		x = x * 10 - '0' + ch;
		ch = getchar();
	}
}

int main() {
	while (scanf("%d", &n) != EOF) {
		ll sum = 0;
		for (int i = n; i >= 0; --i) read(l[i]), sum += l[i];
		for (int i = n; i >= 0; --i) read(s[i]);
		for (int i = n; i >= 0; --i) read(v[i]);
		db ans = 0; 
		sum -= l[n]; 
		for (int i = 0; i <= n; ++i) {
			ans = max(ans, (sum + s[i]) * 1.0 / v[i]);
			sum -= l[i];
		}
		printf("%.15f\n", ans);
	}
	return 0;
}
