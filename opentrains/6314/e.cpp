#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
const int N = 1e6 + 10; 
int nx[2][N], sta[2][N];
string s, t;
vector <int> vec[2];
bool same(string &s, int l, int r) {
	int num = -1;
	for (int i = l, tmp = 0, f = 0; i <= r; ++i) {
		if (isdigit(s[i])) {
			f = 1;
			tmp = tmp * 10 + s[i] - '0';
		} else {
			if (f == 1) {
				if (num == -1) num = tmp;
				else if (tmp != num) return 0;
				f = 0;
				tmp = 0;
			}
		}
	}
	return 1;
}
bool ok(int *nx, string &s, int l, int r) { 
	if (s[l] == '[' || (s[l] == 's' && s[l + 1] == 'o')) return 1;
   	if (s[l] == 's') {
		return same(s, l, r);
	}
	int ql = -1, qr = r - 1, mid = -1;
	for (int i = l; i <= r; ++i) {
		if (s[i] == '(') {
			ql = i + 1;
			break; 
		}
	}	
	for (int i = ql; i <= r; ++i) {
		if (s[i] == '[' || s[i] == '(') {
			mid = nx[i] + 1;
			break;
		}
	}
	return ok(nx, s, ql, mid - 1) && ok(nx, s, mid + 1, qr);	
}
void pre(string s, int *nx) {
	*sta[0] = *sta[1] = 0; 
	for (int i = s.size() - 1; i >= 0; --i) {
		if (s[i] == ')') sta[0][++*sta[0]] = i;
		else if (s[i] == ']') sta[1][++*sta[1]] = i;
		else if (s[i] == '(') {
			nx[i] = sta[0][*sta[0]];
			--*sta[0];
		} else if (s[i] == '[') {
			nx[i] = sta[1][*sta[1]];
			--*sta[1]; 
		}
	}
}
vector <int> get(string &s, int l, int r, int op) {
	vector <int> vec;
	int num = 0, f = 0;
	for (int i = l; i <= r; ++i) {
		if (isdigit(s[i])) {
			num = num * 10 + s[i] - '0';
			f = 1;
		} else if (f == 1) {
			vec.push_back(num);
			num = 0;
			f = 0;
		}
	}	
	if (f == 1) vec.push_back(num);
	if (op) sort(vec.begin(), vec.end());
	return vec; 
}
vector <int> gao(int *nx, string &s, int l, int r) {
	if (s[l] == '[') return get(s, l, r, 0);
	if (s[l] == 's' && s[l + 1] == 'o') return get(s, l, r, 1);
	if (s[l] == 's') {
		int ql = -1, qr = r - 1; 
		for (int i = l; i <= r; ++i) if (s[i] == '(') {
			ql = i + 1;
			break;
		}
		return gao(nx, s, ql, qr);
	} else {
		int ql = -1, qr = r - 1, mid = -1;
		for (int i = l; i <= r; ++i) {
			if (s[i] == '(') {
				ql = i + 1;
				break; 
			}
		}	
		for (int i = ql; i <= r; ++i) {
			if (s[i] == '[' || s[i] == '(') {
				mid = nx[i] + 1;
				break;
			}
		}
		vector <int> vecl(gao(nx, s, ql, mid - 1)), vecr(gao(nx, s, mid + 1, qr));
		for (auto &it : vecr) vecl.push_back(it);
		return vecl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	while (cin >> s >> t) {
		pre(s, nx[0]);
		pre(t, nx[1]);
		if (!ok(nx[0], s, 0, s.size() - 1) || !ok(nx[1], t, 0, t.size() - 1)) cout << "not equal" << endl;
		else {
			vec[0] = gao(nx[0], s, 0, s.size() - 1);
			vec[1] = gao(nx[1], t, 0, t.size() - 1);
		//	for (int &it : vec[0]) cout << it << " "; cout << endl;
		//	for (int &it : vec[1]) cout << it << " "; cout << endl;
			if (vec[0] == vec[1]) cout << "equal" << endl;
			else cout << "not equal" << endl;
		}
	}
	return 0;
}
