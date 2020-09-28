#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int N = 1e5 + 10;

char s[N];
vector<pii> v;

void no() {
	puts("impossible");
}

int main() {
	while (scanf("%s", s + 1) != EOF) {
		int len = strlen(s + 1);
		if (len >= 3) {
			if (s[len] == 'L' && s[len - 1] == 'R' && s[len - 2] == 'L') { no(); continue;}
			if (s[len] == 'R' && s[len - 1] == 'L' && s[len - 2] == 'R') { no(); continue;}
			if (s[len] == 'D' && s[len - 1] == 'U' && s[len - 2] == 'D') { no(); continue;}
			if (s[len] == 'U' && s[len - 1] == 'D' && s[len - 2] == 'U') { no(); continue;}
		}
		bool F = true;
		for (int i = 2; i <= len; ++i) {
			if (s[i] == s[i - 1]) {
				no();
				F = false;
			}
		}
		if (!F) continue;
		int x = 0, y = 0, dis = 1;
		v.clear();
		for (int i = len; i >= 1; --i) {
			if (s[i] == 'U') {
				y -= dis;
				if (i >= 2) {
					if (s[i - 1] == 'D') {
						v.push_back(pii(x, y - 1));
					} else if (s[i - 1] == 'L') {
						v.push_back(pii(x - 1, y));
					} else if (s[i - 1] == 'R') {
						v.push_back(pii(x + 1, y));
					}
				}
			} else if (s[i] == 'D') {
				y += dis;
				if (i >= 2) {
					if (s[i - 1] == 'U') {
						v.push_back(pii(x, y + 1));
					} else if (s[i - 1] == 'L') {
						v.push_back(pii(x - 1, y));
					} else if (s[i - 1] == 'R') {
						v.push_back(pii(x + 1, y));
					}
				}
			} else if (s[i] == 'L') {
				x += dis;
				if (i >= 2) {
					if (s[i - 1] == 'U') {
						v.push_back(pii(x, y + 1));
					} else if (s[i - 1] == 'D') {
						v.push_back(pii(x, y - 1));
					} else if (s[i - 1] == 'R') {
						v.push_back(pii(x + 1, y));
					} 
				}
			} else if (s[i] == 'R') {
				x -= dis;
				if (i >= 2) {
					if (s[i - 1] == 'U') {
						v.push_back(pii(x, y + 1));
					} else if (s[i - 1] == 'D') {
						v.push_back(pii(x, y - 1));
					} else if (s[i - 1] == 'L') {
						v.push_back(pii(x - 1, y));
					}
				}
			}
			dis <<= 1;
		}
		printf("%d %d\n",x, y);
		printf("%d\n", (int)v.size());
		for (auto it : v) {
			printf("%d %d\n", it.first, it.second);
		}
	}	
	return 0;
}
