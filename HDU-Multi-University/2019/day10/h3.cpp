#include <bits/stdc++.h>
using namespace std;
namespace fastIO
{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    //fread->read
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
            //{printf("IO error!\n");system("pause");for (;;);exit(0);}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(double &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (ch=='.'){
            double tmp=1; ch=nc();
            for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
        }
        if (sign)x=-x;
    }
    inline void read(char *s){
        char ch=nc();
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
        *s=0;
    }
    inline void read(char &c){
        for (c=nc();blank(c);c=nc());
        if (IOerror){c=-1;return;}
    }
    //getchar->read
    //fwrite->write
    struct Ostream_fwrite{
        char *buf,*p1,*pend;
        Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
        void out(char ch){
            if (p1==pend){
                fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
            }
            *p1++=ch;
        }
        void print(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(int x){
            static char s[15],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void print(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1);
        }
        void println(ll x){
            static char s[25],*s1;s1=s;
            if (!x)*s1++='0';if (x<0)out('-'),x=-x;
            while(x)*s1++=x%10+'0',x/=10;
            while(s1--!=s)out(*s1); out('\n');
        }
        void flush(){if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}
        ~Ostream_fwrite(){flush();}
    }Ostream;
    inline void print(int x){Ostream.print(x);}
    inline void println(int x){Ostream.println(x);}
    inline void print(char x){Ostream.out(x);}
    inline void println(char x){Ostream.out(x);Ostream.out('\n');}
    inline void print(ll x){Ostream.print(x);}
    inline void println(ll x){Ostream.println(x);}
    inline void flush(){Ostream.flush();}
    //puts->write
    char Out[OUT_SIZE],*o=Out;
};
using namespace fastIO;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

//选了a
struct node1 {
	int a, b;
	
	node1() {}

	node1(int a, int b): a(a), b(b) {}

	bool operator < (const node1 &other) const {
		if (b != other.b) return b < other.b;
		else return a < other.a;
	}
};

//没选a按照a
struct node2 {
	int a, b;

	node2() {}

	node2(int a, int b): a(a), b(b){}

	bool operator < (const node2 &other) const {
		if (a != other.a) return a < other.a;
		else return b < other.b;
	}
};


//没选a按照a+b
struct node3 {
	int a, b;
	
	node3() {}

	node3(int a, int b): a(a), b(b){}

	bool operator < (const node3 &other) const {
		if (a + b != other.a + other.b) return a + b < other.a + other.b;
		else return a < other.a;
	}
};

int n;
int f[N << 1];
multiset<node1> s1, s5;
multiset<node2> s2, s4;
multiset<node3> s3;
//s1 选了a按照b排序　s2 没选　按照a排序　s3 没选　按照a+b排序　s4　选了a 按照a排序　s5 选了a, b按照b排序
int main() {
	int _T; read(_T);
	while (_T--) {
		read(n);
		s1.clear();
		s2.clear();
		s3.clear();
		s4.clear();
		s5.clear();
		for (int i = 1, a, b; i <= n; ++i) {
			read(a); read(b);
			s2.insert(node2(a, b));
			s3.insert(node3(a, b));
		}
		f[0] = 0ll;
		for (int i = 1; i <= n * 2; ++i) {
			int res1 = f[i - 1], res2 = f[i - 1], res3 = f[i - 1], res4 = f[i - 1];
			//选一个没选过的a 
			if (!s2.empty()) {
				res1 = res1 + (*s2.rbegin()).a;
			} else {
				res1 = -INF;
			}
			//选一个选过的b
			if (!s1.empty()) {
				res2 = res2 + (*s1.rbegin()).b;
			} else {
				res2 = -INF;
			}
			//退一个a选一个a+b
			if (!s4.empty() && !s3.empty()) {
				res3 = res3 - (*s4.begin()).a + (*s3.rbegin()).a + (*s3.rbegin()).b;
			} else {
				res3 = -INF;
			}
			//退一个b选一个a+b
			if (!s5.empty() && !s3.empty()) {
				res4 = res4 - (*s5.begin()).b + (*s3.rbegin()).a + (*s3.rbegin()).b;
			} else {
				res4 = -INF;
			}

			if (res1 >= res2 && res1 >= res3 && res1 >= res4) {
				f[i] = res1;
				auto p1 = s2.end(); p1--;
				int a = (*p1).a, b = (*p1).b;
				s1.insert(node1(a, b));
				s4.insert(node2(a, b));
				s2.erase(p1);
				s3.erase(s3.lower_bound(node3(a, b)));
			} else if (res2 >= res1 && res2 >= res3 && res2 >= res4) {
				f[i] = res2;
				auto p = s1.end(); p--;
				int a = (*p).a, b = (*p).b;
				s1.erase(p);
				s4.erase(s4.lower_bound(node2(a, b)));
				s5.insert(node1(a, b));
			} else if (res3 >= res1 && res3 >= res2 && res3 >= res4) {
				f[i] = res3;
				auto p1 = s4.begin();
				auto p2 = s3.end(); p2--;
				int a1 = (*p1).a, b1 = (*p1).b, a2 = (*p2).a, b2 = (*p2).b;
				s4.erase(p1);
				s1.erase(s1.lower_bound(node1(a1, b1)));
				s2.erase(s2.lower_bound(node2(a2, b2)));
				s3.erase(p2);
				s2.insert(node2(a1, b1));
				s3.insert(node3(a1, b1));
				s5.insert(node1(a2, b2));
			} else if (res4 >= res1 && res4 >= res2 && res4 >= res3) {
				f[i] = res4;
				auto p1 = s5.begin();
				auto p2 = s3.end(); p2--;
				int a1 = (*p1).a, b1 = (*p1).b, a2 = (*p2).a, b2 = (*p2).b;
				s1.insert(node1(a1, b1));
				s2.erase(s2.lower_bound(node2(a2, b2)));
				s3.erase(p2);
				s4.insert(node2(a1, b1));
				s5.erase(p1);
				s5.insert(node1(a2, b2));
			}
		}
		for (int i = 1; i <= n * 2; ++i) {
			print(f[i]);
			print(" \n"[i == n * 2]);
		}
	}
	flush();
	return 0;
}
