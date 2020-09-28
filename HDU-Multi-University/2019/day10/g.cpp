#include <bits/stdc++.h>
using namespace std;

typedef double db;
const int N = 1e4 + 10;
const db eps = 1e-8;
inline int sgn(db x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}
struct Point {
	db x, y;
	Point() {}
	Point(db x, db y) : x(x), y(y) {}
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator == (const Point &b) const {
		return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
	}	
	bool operator < (const Point &b) const {
		return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
	}
	db operator ^ (const Point &b) const {
		return x * b.y - y * b.x;
	}
	db operator * (const Point &b) const {
		return x * b.x + y * b.y;
	}
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
	db distance(Point p) {
		return hypot(x - p.x, y - p.y);
	}
};

struct Line {
	Point s, e;
	void input() {
		s.input();
		e.input();
		if (e < s) swap(s, e);
	}
	bool operator < (const Line &other) const {
		if (!(s == other.s)) return s < other.s;
		return e < other.e;
	}
	db length() {
		return s.distance(e);
	}
	db dis_point_to_line(Point p) {
		return fabs((p - s) ^ (e - s)) / length();
	}
	db dis_point_to_seg(Point p) {
		if (sgn((p - s) * (e - s)) < 0 || sgn((p - e) * (s - e)) < 0) 
		   return min(p.distance(s), p.distance(e));	
		return dis_point_to_line(p);
	}
	db dis_seg_to_seg(Line v) {
		return min(min(dis_point_to_seg(v.s), dis_point_to_seg(v.e)), min(v.dis_point_to_seg(s), v.dis_point_to_seg(e)));
	}
};
int n;
Line a[N];

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) a[i].input();
		sort(a + 1, a + 1 + n);		
		db ans = 1e18;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				if (sgn(a[j].s.x - a[i].e.x - ans) > 0) break;
				ans = min(ans, a[i].dis_seg_to_seg(a[j]));
			}
		}
		printf("%.16f\n", ans);
	}
	return 0;
}
