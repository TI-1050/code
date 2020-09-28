#include <bits/stdc++.h>
using namespace std;

string s[20];
map <string, int> mp;

bool ok1() {
	set <string> se;
	for (int i = 0; i < 14; ++i) {
		if (mp.find(s[i]) != mp.end()) {
			if (se.find(s[i]) != se.end()) {
				return false;
			}
			se.insert(s[i]);
		}
	}
	if (se.size() != 7) {
		return false;
	}
	se.clear();
	for (int i = 0; i < 14; ++i) {
		if (s[i][0] == '1' || s[i][0] == '9') {
			se.insert(s[i]);
		}	
	}
	return (int)se.size() == 6;
}

bool ok2() {
	for (int i = 0; i < 14; ++i) {
		if (mp.find(s[i]) != mp.end()) {
			return false;
		}
		if (i && s[i][1] != s[i - 1][1]) {
			return false;
		}
	}
	int cnt[10] = {0};
	for (int i = 0; i < 14; ++i) {
		++cnt[s[i][0] - '0'];
	}
	if (cnt[1] >= 3 && cnt[9] >= 3 && cnt[2] >= 1 && cnt[8] >= 1) {
		return true;
	}
	return false;
}

int main() {
	mp["dong"] = 1;
	mp["nan"] = 2;
	mp["xi"] = 3;
	mp["bei"] = 4;
	mp["zhong"] = 5;
	mp["fa"] = 6;
	mp["bai"] = 7;
	for (int i = 0; i < 14; ++i) {
		cin >> s[i];
	}
	if (ok1()) {
		cout << "shisanyao!\n";
	} else if (ok2()) {
		cout << "jiulianbaodeng!\n";
	} else {
		cout << "I dont know!\n";
	}
	return 0;
}
