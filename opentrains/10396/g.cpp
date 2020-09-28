#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, A, B, a[N];

int main() {
	while (scanf("%d%d%d", &n, &A, &B) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		priority_queue <int> pq;
		for (int i = 1; i <= n; ++i) pq.push(a[i] % ((A + B)));
		int cnt = 1;
		while (!pq.empty()) {
			int num = pq.top(); pq.pop();
			if (cnt & 1) {
				if (num < A)
					break;
				num -= A;
				pq.push(num);
			} else {
				if (num < B) 
					break;
				num -= B;
				pq.push(num);
			}
			cnt ^= 1;
		}
		if (cnt == 1) puts("Marichka");
		else puts("Zenyk");
	}
	return 0;
}
