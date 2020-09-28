#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));

int main() {
	string s = "", t = "";
	for (int i = 0; i < 100; ++i) {
		s += rnd() % 2 + '0';
		t += rnd() % 2 + '0';
	}
	if (s > t) swap(s, t);
	cout << s << "\n";
	cout << t << "\n";
	return 0;
}
