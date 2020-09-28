#include <bits/stdc++.h>
using namespace std;

#define N 1100
int used[N], pre[N];
int n, Max, flag;
vector <int> res;

void DFS(int x, int len) {
	if (len > Max) {
		Max = len;
		res.clear();
		int it = x;
		while (it != -1) {
			res.push_back(it);
			it = pre[it];
		}
	}
	for (int i = n - 1; i >= 0; --i) {
		int f = x ^ (1 << i);
		if (!used[f]) {
			for (int j = n - 1; j >= 0; --j) {
				++used[x ^ (1 << j)];
			}
			pre[f] = x;
			DFS(f, len + 1);
			for (int j = n - 1; j >= 0; --j) {
				--used[x ^ (1 << j)];
			}
		}
	}
}

void out(int x) {
	for (int i = n - 1; i >= 0; --i) {
		putchar(((x >> i) & 1) + '0');
	}
	puts("");
}

int main() {
	while (scanf("%d", &n) != EOF) {
		switch(n) {
		//	case 1 :
		//		puts("2\n0\n1");
		//		break;	
		//	case 2 :
		//		puts("3");
		//		for (auto it : {"00", "01", "11"}) {
		//			puts(it);
		//		}
		//		break;
		//	case 3 :
		//		puts("5");
		//		for (auto it : {"000", "001", "011", "111", "110"}) {
		//			puts(it);
		//		}
		//		break;
		//	case 4 :
		//		puts("8");
		//		for (auto it : {"0000", "0001", "0011", "0111", "0110", "1110", "1100", "1101"}) {
		//			puts(it);
		//		}
		//		break;
			default :
				Max = 0;
				memset(pre, -1, sizeof pre);
				memset(used, 0, sizeof used); 
				used[0] = 1;
				DFS(0, 1);
				reverse(res.begin(), res.end());
				cout << Max << "\n";
				for (auto it : res) {
					out(it);
				}
				break;
		}
	}
	return 0;
}
