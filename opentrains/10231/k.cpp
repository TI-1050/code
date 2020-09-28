#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define D 10

struct node {
	int id;
	vector<int> v;
	bool operator < (const node &other) const {
		return v < other.v;
	}

	bool operator == (const node &other) const {
		for (int i = 0, len = v.size(); i < len; ++i) {
			if (v[i] != other.v[i]) {
				return false;
			}
		}
		return true;
	}
} b[N]; 

int n, d;
vector<int> a[N];

void Init(vector<int> &v) {
	int G = 0;
	for (auto it : v) {
		G = __gcd(G, it);
	}
	if (G == 0) return ;
	for (auto it : v) {
		it /= G;
	}
}
 
void sub(vector<int> x, vector<int> y, vector<int> &res) {
	int lcm = x[0] * y[0] / __gcd(x[0], y[0]);
	for ()
}

int main() {
	while (~scanf("%d %d", &n, &d)) {
		for (int i = 1; i <= n; ++i) {
			a[i].clear();
			for (int j = 1, x; j <= d; ++j) {
				scanf("%d", &x);
				a[i].push_back(x);			
			}
			Init(a[i]);
		}

	}
	return 0;
}
