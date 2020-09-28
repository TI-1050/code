#include <bits/stdc++.h>

using namespace std;

int n;
map<int, int> dis;
map<int, int> pre;

void BFS() {
	deque<int> q;
	dis[n] = 0;
	q.push_back(n);
	while (!q.empty()) {
		int x = q.front();
		q.pop_front();
		if (x == 1) {
			return ;
		}
		int tmp = x + 1;
		if (dis.find(tmp) == dis.end() || dis[tmp] > dis[x] + 1) {
			q.push_back(tmp);
			dis[tmp] = dis[x] + 1;
			pre[tmp] = x;
			if (tmp == 1) {
				return ;
			}
		}
		if (x % 2 == 0) {
			tmp = x / 2;
			if (dis.find(tmp) == dis.end() || dis[tmp] > dis[x]) {
				q.push_front(tmp);
				dis[tmp] = dis[x];
				pre[tmp] = x;
				if (tmp == 1) {
					return ;
				}
			}
		}
		if (x % 3 == 0) {
			tmp = x / 3;
			if (dis.find(tmp) == dis.end() || dis[tmp] > dis[x]) {
				q.push_front(tmp);
				dis[tmp] = dis[x];
				pre[tmp] = x;
				if (tmp == 1) {
					return ;
				}
			}
		}
	}
}

int main() {
	while (~scanf("%d", &n)) {
		dis.clear();
		pre.clear();
		BFS();
		vector<int>ans;
		printf("%d\n", dis[1]);
		int now = 1;
		while (now != n)  {
			ans.push_back(now);
			now = pre[now];	
		}
		ans.push_back(now);
		reverse(ans.begin(), ans.end());
		for (int i = 0, len = ans.size(); i < len; ++i) {
			printf("%d%c", ans[i], " \n"[i == len - 1]);
		}
	}
	return 0;
}
