#include <bits/stdc++.h>
using namespace std;

int main() {
	string s = "abc";
	s.insert(s.begin(), 'A');
	s.erase(s.begin());
	cout << s << endl;
}
