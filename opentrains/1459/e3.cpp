#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T>
bool uin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

int m[600][600];
int res[600];

int N, M;

void rec() {
    int v = -1;
    forn(i, N) {
        int d = 0;
        forn(j, N) d ^= m[i][j];
        if (d) {
            v = i;
            break;
        }
    }
    if (v == -1) return;
    vi n;
    forn(i, N) if (m[v][i]) {
        n.pb(i);
        m[v][i] = m[i][v] = 0;
    }
    forn(i, n.size()) forn(j, i) {
        m[n[i]][n[j]] ^= 1;
        m[n[j]][n[i]] ^= 1;
    }
    rec();
    int c[2] = {0, 0};
    forn(i, n.size()) c[res[n[i]]] ^= 1;
    res[v] = 0;
    while (c[res[v]]) ++res[v];
    forn(i, n.size()) forn(j, i) {
        m[n[i]][n[j]] ^= 1;
        m[n[j]][n[i]] ^= 1;
    }
    forn(i, n.size()) m[v][n[i]] = m[n[i]][v] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;

    while (cin >> N >> M) {
	
	
    forn(i, M) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        m[x][y] = m[y][x] = 1;
    }
    rec();
    forn(i, N) cout << (char)('A' + res[i]);
    cout << '\n';
	}
    return 0;
}

