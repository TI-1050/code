#include <bits/stdc++.h>

using namespace std;

const int N = 210;

int n, m, k;
char G[N][N];
int c[N];
vector<int> vec1, vec2;

bool gao1() {
	memset(c, 0, sizeof c);
	for (int j = 1; j <= m; ++j) {
		for (int i = 1; i <= n; ++i) {
			c[j] += G[i][j] - '0';
		}
	}
	vec1.clear();
	vec1.push_back(0);
	int res = 0;
	for (int j = 1; j <= m; ++j) {
		res += c[j];
		if (res == k) {
			vec1.push_back(j);
			res = 0;
		}
		if (res > k) {
			return false;
		}
	}
	return res == 0;
}

bool gao2() {
	memset(c, 0, sizeof c);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			c[i] += G[i][j] - '0';
		}
	}
	vec2.clear();
	vec2.push_back(0);
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		res += c[i];
		if (res == k) {
			vec2.push_back(i);
			res = 0;
		} else if (res > k) {
			return false;
		}
	}
	return res == 0;
}

map<int, int> mp;

bool check() {
	mp.clear();
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (G[i][j] == '1') {
				int y = lower_bound(vec1.begin(), vec1.end(), j) - vec1.begin();
				int x = lower_bound(vec2.begin(), vec2.end(), i) - vec2.begin();
				if (mp.count(x * 1000 + y)) return false; 
				mp[x * 1000 + y] = 1;
			}
		}
	}
	return true;
}

int main() {
	int cnt = 0;
	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				scanf(" %c", G[i] + j);
		}
		if (gao1() && gao2()) {
			if (!check()) {
				puts("NO");
				continue;
			}
			puts("YES");
			for (int i = 1; i < k; ++i) {
				printf("%d%c", vec2[i], " \n"[i == k - 1]);
			}
			for (int i = 1; i < k; ++i) {
				printf("%d%c", vec1[i], " \n"[i == k - 1]);
			}
		} else {
			puts("NO");
		}
	}
	return 0;
}
