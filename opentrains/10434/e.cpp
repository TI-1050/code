#include <bits/stdc++.h>
using namespace std;

int main() {
	int _T; cin >> _T;
	while (_T--) {
		int y, z; scanf("%d", &y);
		if (abs(y) > 100) {
			if (y < 0) z = 1;
			else z = -1;
		} else {
			z = y;
		}
		printf("%d %d %d\n", 1, -(y + z), z * y);
	}
	return 0;
}
