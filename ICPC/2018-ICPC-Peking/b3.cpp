#include <bits/stdc++.h>
using namespace std;
using pSI = pair<string, int>;
#define fi first
#define se second
int num[1100];
bool isnum(string &s) {
	int len = s.size();
	if (len == 1) {
		return isdigit(s[0]);
	} 
	if (s[0] == '0') return false;
	for (int i = 0; i < len; ++i)
		if (!isdigit(s[i]))
			return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	string s, t, pres;
	int cnt = 0;
	vector <pSI> vec;
	bool flag = 0;
	while (getline(cin, s)) {
		++cnt; 
		stringstream ss(s);
		int cc = 0;
		while (ss >> t) {
			++cc;
			if (cc == 1) {
				if (cnt > 1 && isdigit(t[0]) && isdigit(pres.end()[-1])) {
					if (flag) {
						string tmp = vec.end()[-1].fi;
					   	tmp	= tmp + t;
						if (isnum(tmp)) {
							vec.end()[-1].fi += t;
							flag = 1;
						} else {
							vec.pop_back();
							flag = 0;
						}
					} else {
						flag = 0;
					}
				} else {
					if (isnum(t)) {
						vec.push_back(pSI(t, cnt));
						flag = 1;
					} else 
						flag = 0;
				}
			} else {
				if (isnum(t)) {
					vec.push_back(pSI(t, cnt));
					flag = 1;
				} else {
					flag = 0;
				}
			}
			pres = t;
		}		
	}
	memset(num, 0, sizeof num);
	int sze = vec.size();
	for (int i = 0; i < sze; ++i) {
		cout << vec[i].fi << " \n"[i == sze - 1];
		++num[vec[i].se];	
	}
	for (int i = 1; i <= cnt; ++i)
		cout << num[i] << "\n";
	return 0;
}
