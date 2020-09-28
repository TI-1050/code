#include <bits/stdc++.h>
  
using namespace std;
typedef long long ll;
  
const int N = 2e5 + 10;
const int S = 330;
  
struct node {
    int x, y, z, w;
    node() {}
    node(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
};
  
int n, m, h, q;
  
int F(node a, node b) {
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}
  
int get(node a) {
    assert(a.x >= 1 && a.x <= n && a.y >= 1 && a.y <= m && a.z >= 1 && a.z <= h);
    assert((a.x - 1) * m * h + (a.y - 1) * h + a.z < N && (a.x - 1) * m * h + (a.y - 1) * h + a.z >= 0);
    return (a.x - 1) * m * h + (a.y - 1) * h + a.z;
}
  
queue<node> que;
vector<node> vec;
int dis[N];
int dir[][3] = {1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 1, 0, 0, -1};
  
void gao() {
    while (!que.empty()) que.pop();
    for (auto it : vec) {
        dis[get(it)] = 0;
        que.push(it);
    }
    vec.clear();
	while (!que.empty()) {
        node st = que.front();
        que.pop();
        for (int i = 0; i < 6; ++i) {
            node now = st;
            now.x += dir[i][0];
            now.y += dir[i][1];
            now.z += dir[i][2];
            if (now.x >= 1 && now.x <= n && now.y >= 1 && now.y <= m && now.z >= 1 && now.z <= h &&
                dis[get(now)] > now.w + 1) {
                dis[get(now)] = now.w + 1;
                que.push(now);
            }
        }
    }
}
  
int query(node x) {
    int res = dis[get(x)];
    for (auto it : vec) {
        res = min(res, F(x, it));
    }
    return res;
}
  
int main() {
#ifdef LOCAL_JUDGE
    freopen("input.txt", "r", stdin);
#endif
    while (scanf("%d %d %d %d", &n, &m, &h, &q) != EOF) {
        memset(dis, 0x3f, sizeof dis);
        while (!que.empty()) que.pop();
        vec.clear();
        for (int _q = 1, op, x, y, z; _q <= q; ++_q) {
            scanf("%d %d %d %d", &op, &x, &y, &z);
            if (op == 1) {
                vec.push_back(node(x, y, z, 0));
            } else {
                printf("%d\n", query(node(x, y, z, 0)));
            }
            if (vec.size() >= S) {
                gao();
            }
        }
    }
    return 0;
}
