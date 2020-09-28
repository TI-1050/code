#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int lena, lenb, len, p1, p2;
char a[N], b[N];
int res[N];

void find(int x, int y, int i) {
	if (x == 0) {
		if (y == 0) {res[i] = 0; res[i + 1] = 0; res[i + 2] = 0; res[i + 3] = 0;}
		else if (y == 1) {res[i] = 1; res[i + 1] = 1; res[i + 2] = 0; res[i + 3] = 0;}
		else if (y == 2) {res[i] = 0; res[i + 1] = 0; res[i + 2] = 1; res[i + 3] = 0; p2--;}
		else if (y == 3) {res[i] = 1; res[i + 1] = 1; res[i + 2] = 1; res[i + 3] = 0; p2--;}
		}
	else if (x == 1) {
		if (y == 0) {res[i] = 1; res[i + 1] = 0; res[i + 2] = 0; res[i + 3] = 0;}
		else if (y == 1) {res[i] = 0; res[i + 1] = 1; res[i + 2] = 1; res[i + 3] = 1;}
		else if (y == 2) {res[i] = 1; res[i + 1] = 0; res[i + 2] = 1; res[i + 3] = 0; p2--;}
		else if (y == 3) {res[i] = 0; res[i + 1] = 1; res[i + 2] = 0; res[i + 3] = 1;}
		}
	else if (x == 2) {
		if (y == 0) {res[i] = 0; res[i + 1] = 0; res[i + 2] = 1; res[i + 3] = 1;}
		else if (y == 1) {res[i] = 1; res[i + 1] = 1; res[i + 2] = 1; res[i + 3] = 1;}
		else if (y == 2) {res[i] = 0; res[i + 1] = 0; res[i + 2] = 0; res[i + 3] = 1;}
		else if (y == 3) {res[i] = 1; res[i + 1] = 1; res[i + 2] = 0; res[i + 3] = 1;}				
		}
	else if (x == 3) {
		if (y == 0) {res[i] = 1; res[i + 1] = 0; res[i + 2] = 1; res[i + 3] = 1;}
		else if (y == 1) {res[i] = 0; res[i + 1] = 1; res[i + 2] = 0; res[i + 3] = 0; p1--;}
		else if (y == 2) {res[i] = 1; res[i + 1] = 0; res[i + 2] = 0; res[i + 3] = 1;}
		else if (y == 3) {res[i] = 0; res[i + 1] = 1; res[i + 2] = 1; res[i + 3] = 0; p1--; p2--;}
		}		

	if (i + 3 > len) len = i + 3; 
}

int main() {
	while (scanf("%s%s", a + 1, b + 1) != EOF) {
		lena = strlen(a + 1), lenb = strlen(b + 1);
		reverse(a + 1, a + 1 + lena);
		reverse(b + 1, b + 1 + lenb);
		len = 0;
		while (len < lena || len < lenb) len += 4;
		for (int i = lena + 1; i <= len; ++i) a[i] = '0';
		for (int i = lenb + 1; i <= len; ++i) b[i] = '0';
		int x, y;
	   	p1 = 0, p2 = 0; 
		for (int i = 1; i <= len; i += 4) {
			x = p1; y = p2;
			p1 = 0; p2 = 0;
			if (a[i] == '1') x++;
			if (a[i + 1] == '1') x--, y++;
			if (a[i + 2] == '1') y -= 2;
			if (a[i + 3] == '1') x += 2, y += 2;
			if (b[i] == '1') x++;
			if (b[i + 1] == '1') x--, y++;
			if (b[i + 2] == '1') y -= 2;
			if (b[i + 3] == '1') x += 2, y += 2;
			
			//printf("%d %d\n", x, y);

			while (x < 0) x += 4, p1++;
			while (x >= 4) x -= 4, p1--;
			while (y < 0) y += 4, p2++;
			while (y >= 4) y -= 4, p2--;

			find(x, y, i);
		}
		//printf("%d %d\n", p1, p2);
		int i = len + 1;
		while (p1 != 0 || p2 != 0) {
			x = p1; y = p2;
			p1 = 0; p2 = 0;

			while (x < 0) x += 4, p1++;
			while (x >= 4) x -= 4, p1--;
			while (y < 0) y += 4, p2++;
			while (y >= 4) y -= 4, p2--;
			
			find(x, y, i);
			//printf("%d %d\n",i,len);
			i += 4;
		}
		//printf("%d\n", len);
		while (res[len] == 0 && len > 1) len--;
		for (int i = len; i > 0; --i) printf("%d", res[i]);
		printf("\n");
	}
	return 0;
}
