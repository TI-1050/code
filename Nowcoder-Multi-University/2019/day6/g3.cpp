#include <bits/stdc++.h>
using namespace std;

//返回值[1, 7],表示星期一~星期天
int getweek2(int y, int m, int d) {
    int ans;
    if (m == 1 || m == 2) m += 12, y--;
    if ((y < 1752) || (y == 1752 && m < 9) || (y == 1752 && m == 9 && d < 3)) {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7;
    } else {
        ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    }
    ans = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    return ans + 1;
}

//返回值[0, 6]表示星期天~星期六
int getweek(int y, int m, int d) {
	if (m < 3) {
		y -= 1;
		m += 12;
	}
	//据说是1582年10月4日及之前要这么算，但是好像是错的，直接用下面那个就可以
//	if ((y < 1582) || (y == 1582 && m < 10) || (y == 1582 && m == 10 && d <= 4)) {
//		int c = y / 100;
//		y = y - 100 * c;
//		return ((y + y / 4 + c / 4 - 2 * c + (13 * (m + 1)) / 5 + d + 2) % 7 + 7) % 7;
//	}
	int c = y / 100;
	y = y - 100 * c;
	return ((y + y / 4 + c / 4 - 2 * c + (13 * (m + 1)) / 5 + d - 1) % 7 + 7) % 7; 
}

int main() {
	int y, m, d;
	while (cin >> y >> m >> d) {
		cout << getweek(y, m, d) << endl;
		cout << getweek2(y, m, d) << endl;
	}
	return 0;
}

