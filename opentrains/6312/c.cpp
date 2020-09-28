#include <bits/stdc++.h>

using namespace std;

int vis[10];
vector<int> vec;

bool DFS(int now, int cur) {
	if (cur > 8) {
		return true;
	}
	for (int i = 0; i < 8; ++i) if (!vis[i]) {
		if ((now & 3) == ((i & 6) >> 1)) {
			vis[i] = 1;
			vec.push_back(i);
			if (DFS(i, cur + 1)) {
				return true;
			}
			vis[i] = 0;
			vec.pop_back();
		}
	}
	return false;
}

int main() {
	for (int i = 0; i < 8; ++i) {
		vec.clear();
		vec.push_back(i);
		if (DFS(i, 1)) {
			break;
		}
	}
	for (auto it : vec) {
		cout << it << endl;
	}
	return 0;
}
