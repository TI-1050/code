#include <bits/stdc++.h>
using namespace std;

#define N 300010
char s[N];
vector <int> vec, res;

void add(int x) {
	for (int i = 0; i < 8; ++i) {
		vec.push_back((x >> i) & 1); 
	}
}

void work() {
	while (!vec.empty()) {
		int tot = 0;
		for (int i = 0; i < 6; ++i) {
			tot = tot * 2 + vec.back();
			vec.pop_back();
		}
		res.push_back(tot);
	}
}

int main() {
	scanf("%s", s + 1); 
	{
		vec.clear(); res.clear();
		for (int i = 1, sze = strlen(s + 1); i <= sze; ++i) {
			add(s[i]);
		}
	//	for (int i = 0, sze = vec.size(); i < sze; ++i) {
	//		printf("%d%c", vec[i], " \n"[i == sze - 1]);
	//	}
		reverse(vec.begin(), vec.end());
		work();
		for (int i = 0, sze = (int)res.size(); i < sze; ++i) {
			printf("%d ", res[i]);
		}
	}
	return 0;
}
