#include <bits/stdc++.h>

using namespace std;

#define N 5010

int n;
int arr[N];
map<pair<int,int>, int> mp;

int main() {
	while (~scanf("%d", &n)) {
		mp.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
		}
		sort(arr + 1, arr + 1 + n);
		int ans = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				auto it = mp.find({j, arr[i] - arr[j]});
				if (it != mp.end()) {
					mp[pair<int,int> (i, arr[i] - arr[j])] = it->second + 1;;
				} else {
					mp[pair<int,int>(i, arr[i] - arr[j])] = 2;
				}
				ans = max(ans, mp[pair<int,int>(i, arr[i] - arr[j])]);

			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
