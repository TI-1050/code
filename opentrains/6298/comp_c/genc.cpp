#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int main() {
	int t = 42;
	cout << t << endl;
	for (int i = 1; i <= t; ++i) 
		cout << rnd() % 10000000 + 2 << endl;
}
