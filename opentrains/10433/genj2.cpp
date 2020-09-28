#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));

int main() {
	string s[2];
	cin >> s[0] >> s[1];
	int n = 100, k = 15, q = 100;
	cout << n << " " << k << " " << q << endl;
	vector <int> vec;
	for (int i = 0; i < n; ++i) vec.push_back(i);
	for (int i = 1; i <= q; ++i) {
		int p = rnd() % 2;
		string t = s[p];
		sort(vec.begin(), vec.end());
		shuffle(vec.begin(), vec.end(), rnd);
		for (int j = 0; j < k; ++j) {
			t[vec[j]] = ((t[vec[j]] - '0') ^ 1) + '0';
		}
		cout << t << endl;
	}
	return 0;
}
