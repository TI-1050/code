#include <bits/stdc++.h>
using namespace std;

#define N 1000010
int n, q, c[N]; 
int pos[N][30], p[N][30];

void work(int x, int num)
{
    for (int i = 0; i < 30; ++i) 
    {
        pos[x][i] = pos[x - 1][i];
        p[x][i] = p[x - 1][i];
    }
    int tmp = num;
    int id = x;
    for (int i = 29; i >= 0; --i)
    {
        if ((tmp >> i) & 1)
        {
            if (!p[x][i])
            {
                p[x][i] = tmp;
                pos[x][i] = id;
                return; 
            }
            if (pos[x][i] < id)  
            {
                swap(tmp, p[x][i]);
                swap(id, pos[x][i]); 
            }
            tmp ^= p[x][i];
        }
    }
}

int ask(int l, int r)
{
    int res = 0;
    for (int i = 29; i >= 0; --i) if (pos[r][i] >= l && (res ^ p[r][i]) > res)
        res ^= p[r][i];
    return res;
}

int main() {
	int T; scanf("%d", &T);
    while (T--) {
		scanf("%d%d", &n, &q);
        for (int i = 0; i < 30; ++i) pos[0][i] = p[0][i] = 0;
        for (int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			work(i, x); 
		}
		int last = 0;
		int op, l, r, x;
		while (q--) {
			scanf("%d", &op);
			switch(op) {
				case 0:
					scanf("%d%d", &l, &r);
					l = (l ^ last) % n + 1;
					r = (r ^ last) % n + 1;
					if (l > r) swap(l, r);
					printf("%d\n", last = ask(l, r));
					break;
				case 1 :
					scanf("%d", &x);
					x ^= last;
					work(++n, x);
					break;
			}
		}
    }
    return 0;
}
