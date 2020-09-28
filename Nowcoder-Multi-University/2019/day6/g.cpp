#include <bits/stdc++.h>
using namespace std;
 
#define N 100010
#define M 2000010
 
struct Edge {
    int year, month, day;
    Edge() {}
    Edge(int year, int month, int day) : year(year), month(month), day(day) {}
} edge[M << 1];
 
 
int n;
int a[N], b[N];
char str[N];
vector<Edge> G[M];
int mark[100][100];
 
void Init() {
    memset(mark, 0, sizeof mark);
    for (int i = 0; i < N; ++i) {
        G[i].clear();
    }
}
 
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
 
void addedge(int u, int year = -1, int month = -1, int day = -1) {
    G[u].emplace_back(year, month, day);
}
 
void addedges() {
    int len = strlen(str + 1);
    for (int i = 1; i <= len; ++i) {
        mark[i][str[i] - 'A'] = 1;
    }
    int yearVal = 0, monthVal = 0, dayVal = 0;
    yearVal = ((((str[1] - 'A') * 10) + (str[2] - 'A')) * 10 + (str[3] - 'A')) * 10 + (str[4] - 'A');
    monthVal = (str[6] - 'A') * 10 + (str[7] - 'A');
    dayVal = (str[9] - 'A') * 10 + str[10];
    addedge(yearVal, yearVal, monthVal, dayVal);
    addedge(monthVal, yearVal, monthVal, dayVal);
    addedge(dayVal, yearVal, monthVal, dayVal);
    addedge(str[1] - 'A', yearVal, monthVal, dayVal);
    addedge(str[6] - 'A', yearVal, monthVal, dayVal);
    addedge(str[9] - 'A', yearVal, monthVal, dayVal);
}
 
bool check() {
    for (int i = 1; i <= 10; ++i) {
        b[a[i]] = 'A' - 1 + i;
    }
    for (int i = 0; i < 10; ++i) {
        //y1在1-9之间
        if (mark[1][i] && a[i] >= 1 && a[i] <= 9) {
 
        } else if (mark[1][i]) {
            return false;
        }
        //m1在0-1之间
        if (mark[6][i] && a[i] >= 0 && a[i] <= 1) {
 
        } else if (mark[6][i]){
            return false;
        }
        //d1在0-3之间
        if (mark[9][i] && a[i] >= 0 && a[i] <= 3) {
 
        } else if (mark[9][i]){
            return false;
        }
    }
    //1
    int u = b[1];
    for (auto item: G[u]) {
        int year = item.year;
        int month = item.month;
        //y1是1
        if (year / 1000 == u) {
            int y2 = year / 100 % 10;
            if (a[y2] >= 6 && a[y2] <= 9) {
 
            } else {
                return false;
            }
        }
        //m1是1
        if (month / 10 == u) {
            int m2 = month % 10;
            if (a[m2] >= 0 && a[m2] <= 2) {
 
            } else {
                return false;
            }
        }
    }
    //d1是3
    u = b[3];
    for (auto item : G[u]) {
        int day = item.day;
        if (day / 10 == u) {
            int d2 = day % 10;
            if (a[d2] >= 0 && a[d2] <= 1) {
 
            } else {
                return false;
            }
        }
    }
    //d=31
    u = b[3] * 10 + b[1];
    for (auto item : G[u]) {
        int year = item.year;
        int month = item.month;
        int day = item.day;
        if (day == u) {
            month = a[month / 10] * 10 + a[month % 10];
            if (month == 2 || month == 4 || month == 6 || month == 9 || month == 11) {
                return false;
            }
        }
    }
    //d=30
    u = b[3] * 10 + b[0];
    for (auto item : G[u]) {
        int year = item.year;
        int month = item.month;
        int day = item.day;
        if (day == u) {
            month = a[month / 10] * 10 + a[month % 10];
            if (month == 2) {
                return false;
            }
        }
    }
    //d=29
    u = b[2] * 10 + b[9];
    for (auto item : G[u]) {
        int year = item.year;
        int month = item.month;
        int day = item.day;
        if (day == u) {
            month = a[month / 10] * 10 + a[month % 10];
            year = a[year / 1000] * 1000 + a[year / 100 % 10] * 100 + a[year / 10 % 10] * 10 + a[year / 10];
            if (month == 2 && !isLeap(year)) {
                return false;
            }
        }
    }
    return true;
}
 
void solve() {
    for (int i = 0; i <= 9; ++i) {
        a[i + 1] = i;
    }
    do {
        if (check()) {
            for (int i = 1; i <= 10; ++i) {
                printf("%d", a[i]);
            }
            puts("");
            return;
        }
    } while (next_permutation(a + 1, a + 1 + 10));
    puts("Impossible");
}
 
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        printf("Case #%d: ", cas);
        scanf("%d", &n);
        Init();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", str + 1);
            addedges();
        }
        solve();
    }
    return 0;
}
