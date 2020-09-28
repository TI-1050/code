#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int random(int l, int r) { return rnd() % (r - l + 1) + l; }
int main() {
	int n = random(10, 30), m = random(1, 5), k = random(1, 3);
	return 0;
}
