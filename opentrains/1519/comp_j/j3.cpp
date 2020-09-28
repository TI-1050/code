#include <bits/stdc++.h>
using namespace std;
using pII = pair <int, int>;
#define fi first
#define se second
const int N = 2e3 + 10;
const int INF = 0x3f3f3f3f; 
int n, m, a[N], b[N];

bool ok(vector <int> &vec) {
	if (vec.size() <= 2) return true;
	for (int i = 1, sze = vec.size(); i < sze - 1; ++i) {
		if (!((vec[i] > vec[i - 1] && vec[i] > vec[i + 1]) || (vec[i] < vec[i - 1] && vec[i] < vec[i + 1])))
			return false;
	}
	return true;
}

bool find(vector <int> &vec) {
	int pos = 0, sze = vec.size();
	for (int i = 1; i <= m && pos < sze; ++i) {
		if (vec[pos] == b[i]) {
			++pos;
		}
	}
	return pos == sze;
}

int check(int x) {
	vector <int> vec;
	for (int i = 1; i <= n; ++i) {
		if ((x >> (i - 1)) & 1)	{
			vec.push_back(a[i]);
		}
	}
	if (!ok(vec)) return -1;
	if (!find(vec)) return -1;
	return vec.size();
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		scanf("%d", &m);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		int res = 0;
		for (int i = 0; i < 1 << n; ++i) {
			res = max(res, check(i));
		}
		cout << res << endl;
	}	
	return 0;
}
