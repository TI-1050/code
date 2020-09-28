#include <bits/stdc++.h>

using namespace std;

typedef double db;

struct node {
	db x, y;

	node (){}

	node (db x, db y): x(x), y(y){}

	db operator ^ (const node &other) const {
		return x * other.y - y * other.x;	
	}

	node operator - (const node &other) const {
		return {x - other.x, y - other.y};
	}

	void input() {
		scanf("%lf %lf", &x, &y);
	}
}p[5];

db getArea(node a, node b) {
	return (a ^ b) / 2.0;
}

int main() {
	
	return 0;
}
