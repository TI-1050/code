#include <bits/stdc++.h>

using namespace std;

string a, b;
int vis[300];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(cin >> a >> b) {
		if(a == b) {
			cout << "Equal\n";
		} else {
			int len1 = a.size(), len2 = b.size(); 
			if(len1 != len2 || a[0] != b[0] || a[len1 - 1] != b[len2 - 1]) {
				cout << "No\n";
			} else {
				memset(vis, 0, sizeof vis);
				for (auto &it : a) {
					vis[it]++;
				}
				for (auto &it : b) {
					vis[it]--;
				}
				int flag = 1;
				for (int i = 0; i < 255; ++i) {
					if(vis[i] != 0) {
						flag =0;
					}
				}
				if(flag) {
					cout << "Yes\n";
				} else {
					cout << "No\n";
				}
			}
		}
	}
	return 0;
}
