#include <bits/stdc++.h>
using namespace std;

struct E {
	int x[2], y[2];
	bool cover(E other) {
		if (other.x[1] <= x[1] && other.y[1] <= y[1] && other.x[0] >= x[0] && other.y[0] >= y[0])
			return true;
		return false;
	}
	bool div(E other) {
		if (other.y[0] > y[1] || other.x[0] > x[1])
			return true;
		return false;
	}
}A, B;

int main() {
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%d%d%d%d", &A.x[0], &A.y[0], &A.x[1], &A.y[1]);
		scanf("%d%d%d%d", &B.x[0], &B.y[0], &B.x[1], &B.y[1]);
		if (A.cover(B)) puts("B in A");
		else if (B.cover(A)) puts("A in B");
		else if (A.div(B) || B.div(A)) puts("Separate");
		else puts("Intersect"); 
	}
	return 0;
}
