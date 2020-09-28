#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	int d = 8, n = 400;
	cout << d << " " << n << " " << n << " " << n << endl;
	for (int i = 1; i <= 3; ++i) {
		vector <int> A;
		for (int i = 1; i <= n; ++i) {
			A.push_back(rnd() % 15 + 1);
		}
		sort(A.begin(), A.end());
		for (int i = 0; i < n; ++i) printf("%d%c", A[i], " \n"[i == n - 1]);
	}
	return 0;
}
