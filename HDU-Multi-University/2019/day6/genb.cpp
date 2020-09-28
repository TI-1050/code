#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int T = 3; cout << T << endl;
	while (T--) {
		int n = 50000; cout << n << endl;
		vector <int> A, B;
		for (int i = 1; i <= n; ++i) A.push_back(i), B.push_back(i);
		random_shuffle(A.begin(), A.end());
		random_shuffle(B.begin(), B.end());
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", A[i - 1], " \n"[i == n]);
		}
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", B[i - 1], " \n"[i == n]);
		}
	}
	return 0;
}
