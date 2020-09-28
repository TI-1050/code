#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <bitset>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N]; ll f[5]; char s[N];

int main() {
	char *t = "wrong";
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (s[i] == t[j]) {
					if (j == 0) f[j] += a[i];
					else f[j] += min(1ll * a[i], f[j - 1]);
					break;
				}
			}
		}
		printf("%lld\n", f[4]);
	}
	return 0;
}
