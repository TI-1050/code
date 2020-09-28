#include <bits/stdc++.h>
using namespace std;

int main() {
	set <int> se;
	for (int i = 1; i <= 10; ++i) se.insert(i);
	auto pos = se.lower_bound(2);
	cout << *next(pos) << endl;
	cout << *pos << endl;
	return 0;
}
