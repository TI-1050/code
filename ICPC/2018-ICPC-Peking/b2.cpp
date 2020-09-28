#include <bits/stdc++.h>
using namespace std;
using pSI = pair<string, int>;
#define fi first
#define se second
const int N = 2e5 + 10;
int vis[N], num[N], pos, len;
string s, t;
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

pSI get() {
	pSI tmp = pSI("", -1);
	while (pos < len && t[pos] == ' ') ++pos;
	while (pos < len && t[pos] != ' ') {
		if (tmp.se == -1) tmp.se = vis[pos];
		tmp.fi += t[pos];
		++pos; 
	}
	return tmp;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(vis, 0, sizeof vis);
	memset(num, 0, sizeof num);
	s = t = "";
	int pre = -1; t = "";
	int n = 0;
	while (getline(cin, s)) {
		++n;
		if (!t.empty() && isdigit(t.end()[-1]) && isdigit(s[0])) {
			t += s;
		} else {
			t += " ";
			t += s;
			++pre;
		}
		int len = t.size();
		for (int i = pre + 1; i < len; ++i) vis[i] = n;
	   	pre = len - 1;	
	} 
	len = t.size();
	pos = 0;
	vector <string> vec;
	while (1) {
		pSI tmp = get();
		if (tmp.se == -1) break;
		if (isnum(tmp.fi)) {
			++num[tmp.se];
			vec.push_back(tmp.fi);
		}
	}
	int sze = vec.size();
	for (int i = 0; i < sze; ++i)
		cout << vec[i] << " \n"[i == sze - 1];
	for (int i = 1; i <= n; ++i)
		cout << num[i] << "\n";
	return 0;
}
