#include <bits/stdc++.h>
using namespace std;

int main() {
	int x = 0, z = 1, *y = &x;
	*y = 2;
	y = &z;
	*y = 4;
	cout << x << endl;
	cout << z << endl;
}
