#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 250010
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a; 
}
struct frac{
    ll x,y;
	inline void sim() {
		ll g = gcd(abs(x), abs(y));
		x /= g;
		y /= g;
		if (x * y < 0) {
			x = -abs(x);
			y = abs(y);
		} else {
			x = abs(x);
			y = abs(y);
		}
	}
	frac() {}
	frac(ll x, ll y) : x(x), y(y) {sim();}
    frac operator+(const frac &u){
        ll p, q; 
        p = x * u.y + y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator-(const frac &u){
        ll p, q;
        p = x * u.y - y * u.x;
        q = u.y * y;
        ll d = gcd(p, q);
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator*(const frac &u){
        ll p, q;
        p = u.x * x;
        q = u.y * y;
        ll d = gcd(p, q); 
        p /= d; q /= d;
        return (frac){p, q};
    }
    frac operator/(const frac &u){
        ll p, q;
        p = u.y * x;
        q = u.x * y;
        ll d = gcd(p,q);
        p /= d; q /= d;
        return (frac){p,q};
    }
	bool operator < (const frac &other) const {
		return x * other.y < y * other.x;
	}
	bool operator > (const frac &other) const {
		return x * other.y > y * other.x;
	}
	bool operator != (const frac &other) const {
		return x * other.y != y * other.x;
	}
	bool operator <= (const frac &other) const {
		return x * other.y <= y * other.x;
	}
	bool operator >= (const frac &other) const {
		return x * other.y >= y * other.x;
	}
	bool operator == (const frac &other) const {
		return x * other.y == y * other.x;
	}
	void sqr() {
		*this = (*this) * (*this);
	}
    void print(){
		sim();
		printf("%lld/%lld\n", abs(x), abs(y));
    }
};
struct node {
	ll a, b; 
	frac x;
	node() {}
	void scan() {
		scanf("%lld%lld", &a, &b);  
		x = frac(a, b);
	}
	bool operator < (const node &other) const {
		return x < other.x;
	}
	bool operator > (const node &other) const {
		return x > other.x;
	}
}a[N];
int n;
frac res, one, zero;
ll sum[2];
priority_queue <node, vector <node>, less <node>> A;
priority_queue <node, vector <node>, greater <node>> B;

frac getres() {
	frac res = frac(1e9, 1);
	if (sum[0] == sum[1]) {
		res = min(res, frac(sum[0], 1));
	} 
	if (!A.empty()) {
		node tmp = A.top(); 
		sum[0] -= tmp.a;
		frac x = frac(sum[1] - sum[0] + tmp.b, tmp.a + tmp.b);
		if (x >= zero && x <= one) {
			res = min(res, x * frac(tmp.a, 1) + frac(sum[0], 1));
		}
		sum[0] += tmp.a;
	}
	if (!B.empty()) {
		node tmp = B.top();
		sum[1] -= tmp.b;
		frac x = frac(sum[1] - sum[0] + tmp.b, tmp.a + tmp.b);
		if (x >= zero && x <= one) {
			res = min(res, x * frac(tmp.a, 1) + frac(sum[0], 1));
		}
		sum[1] += tmp.b;
	}
	return res;
}

int main() {
	one = frac(1, 1), zero = frac(0, 1);  
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) a[i].scan(); 
		while (!A.empty()) A.pop();
		while (!B.empty()) B.pop();
		sum[0] = sum[1] = 0; 
		for (int i = 1; i <= n; ++i) {
			A.push(a[i]);
			sum[0] += a[i].a; 	
			if (i == 1) {
				res = frac(a[i].a * a[i].b, a[i].a + a[i].b); 
			} else {
				res = frac(1e9, 1);
				if (sum[0] == sum[1]) {
					res = frac(sum[0], 1);
				} else if (sum[0] < sum[1]) {
					while (sum[0] < sum[1]) {
						res = min(res, getres());
						node tmp = B.top(); B.pop();
						sum[1] -= tmp.b;
						sum[0] += tmp.a;
						A.push(tmp);	
					}
					res = min(res, getres());
				} else {
					while (sum[0] > sum[1]) {
						res = min(res, getres());
						node tmp = A.top(); A.pop();
						sum[0] -= tmp.a;
						sum[1] += tmp.b;
						B.push(tmp);
					}
					res = min(res, getres());
				}
			}
			res.print();
		}
	}
	return 0;
}
