#include <bits/stdc++.h>
using namespace std;

#define debug(...) { printf("#  "); printf(__VA_ARGS__); puts(""); }
#define ll long long
#define MAXN 9999  
#define MAXSIZE 10  
#define DLEN 4  
  
class BigNum {   
	private:   
	    int a[100010];    //可以控制大数的位数   
	    int len;       //大数长度  
	public:   
	    BigNum(){ len = 1;memset(a,0,sizeof(a)); }   //构造函数  
	    BigNum(const int);       //将一个int类型的变量转化为大数  
	    BigNum(const char*);     //将一个字符串类型的变量转化为大数  
	    BigNum(const BigNum &);  //拷贝构造函数  
	    BigNum &operator=(const BigNum &);   //重载赋值运算符，大数之间进行赋值运算  
	  
	    friend istream& operator>>(istream&,  BigNum&);   //重载输入运算符  
	    friend ostream& operator<<(ostream&,  BigNum&);   //重载输出运算符  
	  
	    BigNum operator+(const BigNum &) const;   //重载加法运算符，两个大数之间的相加运算   
	    BigNum operator-(const BigNum &) const;   //重载减法运算符，两个大数之间的相减运算   
	    BigNum operator*(const BigNum &) const;   //重载乘法运算符，两个大数之间的相乘运算   
	    BigNum operator/(const int   &) const;    //重载除法运算符，大数对一个整数进行相除运算  
	  
	    BigNum operator^(const int  &) const;    //大数的n次方运算  
	    ll    operator%(const ll  &) const;    //大数对一个int类型的变量进行取模运算      
	    bool   operator>(const BigNum & T)const;   //大数和另一个大数的大小比较  
	    bool   operator>(const int & t)const;      //大数和一个int类型的变量的大小比较  
	  
	    void print();       //输出大数  
};   
BigNum::BigNum(const int b)     //将一个int类型的变量转化为大数  
{   
    int c,d = b;  
    len = 0;  
    memset(a,0,sizeof(a));  
    while(d > MAXN)  
    {  
        c = d - (d / (MAXN + 1)) * (MAXN + 1);   
        d = d / (MAXN + 1);  
        a[len++] = c;  
    }  
    a[len++] = d;  
}  
BigNum::BigNum(const char*s)     //将一个字符串类型的变量转化为大数  
{  
    int t,k,index,l,i;  
    memset(a,0,sizeof(a));  
    l=strlen(s);     
    len=l/DLEN;  
    if(l%DLEN)  
        len++;  
    index=0;  
    for(i=l-1;i>=0;i-=DLEN)  
    {  
        t=0;  
        k=i-DLEN+1;  
        if(k<0)  
            k=0;  
        for(int j=k;j<=i;j++)  
            t=t*10+s[j]-'0';  
        a[index++]=t;  
    }  
}  
BigNum::BigNum(const BigNum & T) : len(T.len)  //拷贝构造函数  
{   
    int i;   
    memset(a,0,sizeof(a));   
    for(i = 0 ; i < len ; i++)  
        a[i] = T.a[i];   
}   
BigNum & BigNum::operator=(const BigNum & n)   //重载赋值运算符，大数之间进行赋值运算  
{  
    int i;  
    len = n.len;  
    memset(a,0,sizeof(a));   
    for(i = 0 ; i < len ; i++)   
        a[i] = n.a[i];   
    return *this;   
}  
istream& operator>>(istream & in,  BigNum & b)   //重载输入运算符  
{  
    char ch[MAXSIZE*4];  
    int i = -1;  
    in>>ch;  
    int l=strlen(ch);  
    int count=0,sum=0;  
    for(i=l-1;i>=0;)  
    {  
        sum = 0;  
        int t=1;  
        for(int j=0;j<4&&i>=0;j++,i--,t*=10)  
        {  
	            sum+=(ch[i]-'0')*t;  
	        }  
	        b.a[count]=sum;  
	        count++;  
	    }  
	    b.len =count++;  
	    return in;  
}  
ostream& operator<<(ostream& out,  BigNum& b)   //重载输出运算符  
{  
    int i;    
    cout << b.a[b.len - 1];   
    for(i = b.len - 2 ; i >= 0 ; i--)  
    {   
        cout.width(DLEN);   
        cout.fill('0');   
        cout << b.a[i];   
    }   
    return out;  
}   
BigNum BigNum::operator+(const BigNum & T) const   //两个大数之间的相加运算  
{  
    BigNum t(*this);  
    int i,big;      //位数     
    big = T.len > len ? T.len : len;   
    for(i = 0 ; i < big ; i++)   
    {   
        t.a[i] +=T.a[i];   
        if(t.a[i] > MAXN)   
        {   
            t.a[i + 1]++;   
            t.a[i] -=MAXN+1;   
        }   
    }   
    if(t.a[big] != 0)  
        t.len = big + 1;   
    else  
        t.len = big;     
    return t;  
}  
BigNum BigNum::operator-(const BigNum & T) const   //两个大数之间的相减运算   
{    
    int i,j,big;  
    bool flag;  
    BigNum t1,t2;  
    if(*this>T)  
    {  
        t1=*this;  
        t2=T;  
        flag=0;  
    }  
    else  
    {  
        t1=T;  
        t2=*this;  
        flag=1;  
    }  
    big=t1.len;  
    for(i = 0 ; i < big ; i++)  
    {  
        if(t1.a[i] < t2.a[i])  
        {   
            j = i + 1;   
            while(t1.a[j] == 0)  
                j++;   
            t1.a[j--]--;   
            while(j > i)  
                t1.a[j--] += MAXN;  
            t1.a[i] += MAXN + 1 - t2.a[i];   
        }   
        else  
            t1.a[i] -= t2.a[i];  
    }  
    t1.len = big;  
    while(t1.a[t1.len - 1] == 0 && t1.len > 1)  
    {  
        t1.len--;   
        big--;  
    }  
    if(flag)  
        t1.a[big-1]=0-t1.a[big-1];  
    return t1;   
}   
BigNum BigNum::operator*(const BigNum & T) const   //两个大数之间的相乘运算   
{   
    BigNum ret;   
    int i,j,up;   
    int temp,temp1;     
    for(i = 0 ; i < len ; i++)  
    {   
        up = 0;   
        for(j = 0 ; j < T.len ; j++)  
        {   
            temp = a[i] * T.a[j] + ret.a[i + j] + up;   
            if(temp > MAXN)  
            {   
                temp1 = temp - temp / (MAXN + 1) * (MAXN + 1);   
                up = temp / (MAXN + 1);   
                ret.a[i + j] = temp1;   
            }   
            else  
            {   
                up = 0;   
                ret.a[i + j] = temp;   
            }   
        }   
        if(up != 0)   
            ret.a[i + j] = up;   
    }   
    ret.len = i + j;   
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)  
        ret.len--;   
    return ret;   
}   
BigNum BigNum::operator/(const int & b) const   //大数对一个整数进行相除运算  
{   
    BigNum ret;   
    int i,down = 0;     
    for(i = len - 1 ; i >= 0 ; i--)  
    {   
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;   
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;   
    }   
    ret.len = len;   
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)  
        ret.len--;   
    return ret;   
}  
ll BigNum::operator %(const ll & b) const    //大数对一个int类型的变量进行取模运算      
{  
    int i; ll d=0;  
    for (i = len-1; i>=0; i--)  
    {  
        d = ((d * (MAXN+1))% b + a[i])% b;    
    }  
    return d;  
}  
BigNum BigNum::operator^(const int & n) const    //大数的n次方运算  
{  
    BigNum t,ret(1);  
    int i;  
    if(n<0)  
        exit(-1);  
    if(n==0)  
        return 1;  
    if(n==1)  
        return *this;  
    int m=n;  
    while(m>1)  
    {  
        t=*this;  
        for( i=1;i<<1<=m;i<<=1)  
        {  
            t=t*t;  
        }  
        m-=i;  
        ret=ret*t;  
        if(m==1)  
            ret=ret*(*this);  
    }  
    return ret;  
}  
bool BigNum::operator>(const BigNum & T) const   //大数和另一个大数的大小比较  
{   
    int ln;   
    if(len > T.len)  
        return true;   
    else if(len == T.len)  
    {   
        ln = len - 1;   
        while(a[ln] == T.a[ln] && ln >= 0)  
            ln--;   
        if(ln >= 0 && a[ln] > T.a[ln])  
            return true;   
        else  
            return false;   
    }   
    else  
        return false;   
}  
bool BigNum::operator >(const int & t) const    //大数和一个int类型的变量的大小比较  
{  
    BigNum b(t);  
    return *this>b;  
}  
void BigNum::print()    //输出大数  
{   
    int i;     
    cout << a[len - 1];   
    for(i = len - 2 ; i >= 0 ; i--)  
    {   
        cout.width(DLEN);   
        cout.fill('0');   
        cout << a[i];   
    }   
    cout << endl;  
} 


#define N 1000010
ll x[1000], a, b;
char s[N];
ll mod;
int len;

ll eular(ll n) {
	ll ans = n;
	for (int i = 2; 1ll * i * i <= n; ++i) {
		if (n % i == 0) {
			ans -= ans / i;
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1) ans -= ans / n;
	return ans;
}

struct node {
	ll a[2][2];
	node() {
		memset(a, 0, sizeof a);
	}
	node operator * (const node &other) const {
		node res = node();
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					res.a[i][j] = (res.a[i][j] + a[i][k] * other.a[k][j] % mod) % mod;
		return res;
	}
}base, res;

void qmod(node base, ll n) {
	while (n) {
		if (n & 1) res = res * base;
		base = base * base;
		n >>= 1;	
	}
}

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	while (scanf("%lld%lld%lld%lld", x, x + 1, &a, &b) != EOF) {
		scanf("%s%lld", s + 1, &mod);
		len = strlen(s + 1);
		base = node();
		base.a[0][0] = a; 
		base.a[1][0] = b;
		base.a[0][1] = 1;
		if (len <= 8) {
			ll n = 0;
			for (int i = 1; i <= len; ++i) {
				n = n * 10 + s[i] - '0';
			}
			--n;
			res.a[0][0] = x[1]; res.a[0][1] = x[0];
			qmod(base, n);
			printf("%lld\n", res.a[0][0]);
		} else {
			int Phi = eular(mod);
			int st = 0;
			BigNum a(s + 1), one("1");   
			for (int i = 0; ; ++i) {
				if (gcd(a % mod, mod) == 1) {
					st = i;
					break;  
				}	
				a = a - one; 
			}
			a = a - one;
		    ll n = a % Phi;
			if (st == 0) {
				x[2] = x[0], x[3] = x[1];
			} else if (st == 1) {
				x[2] = x[1];
				res.a[0][0] = x[1], res.a[0][1] = x[0];
				qmod(base, st);
				x[3] = res.a[0][0];
			} else {
				res.a[0][0] = x[1], res.a[0][1] = x[0];
				qmod(base, st - 1);  x[2] = res.a[0][0];
				res.a[0][0] = x[1], res.a[0][1] = x[0];
				qmod(base, st); x[3] = res.a[0][0];
			}
			res.a[0][0] = x[3], res.a[0][1] = x[2];
			qmod(base, n);
			printf("%lld\n", res.a[0][0]); 
		}
	}
	return 0;
}
