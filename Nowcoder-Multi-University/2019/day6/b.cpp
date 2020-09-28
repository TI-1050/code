#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1010
char s[N];
int a[8];
vector <string> res;

string f(int x) {
	string res = "";
	if (!x) return "0";
	while (x) {
		int y = x % 16;
		if (y < 10) res += y + '0';
		else if (y == 10) res += 'a';
		else if (y == 11) res += 'b';
		else if (y == 12) res += 'c';
		else if (y == 13) res += 'd';
		else if (y == 14) res += 'e';
		else res += 'f';
		x /= 16;
	}	
	reverse(res.begin(), res.end());
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin >> T;
	for (int kase = 1; kase <= T; ++kase) {
		cout << "Case #" << kase << ": ";
		cin >> (s + 1);
		int len = 128;
		for (int i = 1; i <= len; i += 16) {
			int num = 0;
			for (int j = i; j < i + 16; ++j) {
				num = num * 2 + s[j] - '0';
			}
	//		cout << num << endl;
			a[i / 16] = num;
		}		
		res.clear(); 
		string str = f(a[0]);
		for (int i = 1; i < 8; ++i) {
			str += ":";
			str += f(a[i]);
		}
		res.push_back(str);
		string tmp = ""; 
		for (int i = 0; i < 8; ++i) {
			string now = tmp;
			now += ":";
			int j = i;
			for (; j < 8; ++j) {
				if (a[j])
					break;
			}
			for (int k = j; k < 8; ++k) {
				now += ":";
				now += f(a[k]); 
			}
			if (j >= 8) now += ":";
			if (j > i + 1) res.push_back(now);
			if (i) tmp += ":";
			tmp += f(a[i]);
		}
		sort(res.begin(), res.end(), [](string x, string y){
			if (x.length() != y.length()) 
				return x.length() < y.length();
			return x < y;		
		});
	//	cout << "####\n";
	//	for (auto it : res) cout << it << endl;
		cout << res[0] << "\n";
	}
	return 0;
}
