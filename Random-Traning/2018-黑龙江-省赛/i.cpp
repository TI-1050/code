#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 500010
int n;
ll dis[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(dis, 0x3f, sizeof dis);
		dis[1] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 2 * i; j <= n; j += i) {
				dis[j] = min(dis[j], dis[i] + 1ll * (j - i) * (j - i));
			}
		}
		for (int i = 1; i <= n; ++i) {
			printf("%lld%c", dis[i], " \n"[i == n]);
		}
	}
	return 0;
}
