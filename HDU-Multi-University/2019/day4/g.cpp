#include <bits/stdc++.h>
using namespace std;

#define N 110
int a[N], b[N];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 16; ++i) {
            scanf("%d", a + i);
        }
        int zero = 0;
        int tot = 0;
        for (int i = 0; i < 16; ++i) {
            if (a[i] == 0) {
                zero = i;
            } else {
                b[++tot] = a[i];
            }
        }
        int res = 0;
        for (int i = 1; i <= 15; ++i) {
            for (int j = 1; j < i; ++j) {
                if (b[j] > b[i]) {
                    res++;
                }
            }
        }
        zero = zero / 4 + 1;
        if (res % 2 == (4 - zero) % 2) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}

