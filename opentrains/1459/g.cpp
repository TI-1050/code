#include <bits/stdc++.h>
using namespace std;

int cnt;
string s[30];

bool query(string &s1, string &s2) {
	cnt += s1.size(); cnt += s2.size();
	assert(cnt <= 600000);
	cout << "? " << s1 << s2 << "\n";
	cout.flush();
	string tmp; cin >> tmp;
	return tmp == "YES";
}
struct node {
	string s;
	node() {}
	node(string s) : s(s) {}
	bool operator < (const node &other) const {
		return s.size() > other.s.size();
	}
};

int main() {
	string emstr = ""; cnt = 0;
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	for (int i = 0; i < 30; ++i) s[i] = "";
	int C = 26;
	priority_queue <node> pq;
	for (int i = 0; i < C; ++i) {
		while (1) {
			s[i] += 'a' + i;
			if (!query(s[i], emstr)) {
				s[i].pop_back(); 
				break;
			}
		}
		if (s[i] != "") pq.push(node(s[i]));
	}
	while (pq.size() >= 2) {
		string s1 = pq.top().s; pq.pop();
		string s2 = pq.top().s; pq.pop();
		string pre = "", suf = s2;
		for (auto it : s1) {
			while (1) {
				pre += it;
				if (query(pre, suf)) break; 
				pre.pop_back(); 
			//	assert(!suf.empty());
				if (!suf.empty()) {
					pre += suf[0];
					suf.erase(suf.begin());
				}	
			}
		}
		pre += suf;
		pq.push(node(pre));
	}
	cout << "! " << pq.top().s << "\n";
	cout.flush();
	return 0;
}
