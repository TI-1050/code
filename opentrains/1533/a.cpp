#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define pii pair <int, int>
#define fi first
#define se second
int n;
char s[110], t[110]; 
vector <pii> ss, tt;  

//1 数字
//2 字符
void work(char *s, vector <pii> &vec) {
	vec.clear();
	int len = strlen(s);
	bool F = 0;
	int tot = 0;
	for (int i = 0; i < len; ++i) {
		if (isdigit(s[i])) {
			F = 1;
			tot = tot * 10 + s[i] - '0';  
		} else {
			if (F) {
				vec.push_back(pii(1, tot));
			}
			F = 0;
			tot = 0;
			vec.push_back(pii(2, s[i]));   
		}
	} 
	if (F) vec.push_back(pii(1, tot));
}

bool cmp(vector <pii> &a, vector <pii> &b) {
	if (a == b) return 1;
	int szea = (int)a.size(), szeb = (int)b.size();
	int sze = min(szea, szeb);
	for (int i = 0; i < sze; ++i) {
		if (a[i].fi != b[i].fi) {
			if (a[i].fi < b[i].fi) {
				return 1; 
			} else {
				return 0;	
			}
		} else {
			if (a[i].se != b[i].se) {
				return a[i].se < b[i].se;
			}
		}
	}
	return szea < szeb;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		scanf("%s", s);
		work(s, ss);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", t);
			work(t, tt);
			puts(cmp(ss, tt) ? "+" : "-");
		}
	}
	return 0;
}
