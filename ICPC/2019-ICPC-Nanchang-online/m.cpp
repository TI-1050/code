#include <bits/stdc++.h>
using namespace std;

#define N 100010
vector < vector <int> > vec; 
char s[N];
int n;

bool ok() {
	int last = n + 1;
	for (int sze = strlen(s + 1), i = sze; i >= 1; --i) {
		vector <int> &v = vec[s[i]];
		if (v.empty()) {
			return false;
		}
		auto pos = lower_bound(v.begin(), v.end(), last); 
		if (pos == v.begin()) {
			return false;
		}
		last = v[pos - v.begin() - 1];
	}
	return true;
}

int main() {
	vec.clear();
	vec.resize(300);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1, sze = strlen(s + 1); i <= sze; ++i) {
		vec[s[i]].push_back(i);
	}
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%s", s + 1);
		puts(ok() ? "YES" : "NO");
	}
	return 0;
}
