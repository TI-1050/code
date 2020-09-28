#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 310010
#define ALP 26

struct Manacher {
	int len;
	char Ma[N << 1];
	int Mp[N << 1];
	void init(int len) {
		this->len = len;
	}
	void work(char *s) {
		int l = 0;
		Ma[l++] = '$';
		Ma[l++] = '#';
		for (int i = 0; i < len; ++i) {
			Ma[l++] = s[i];
			Ma[l++] = '#';
		}
		Ma[l] = 0;
		int mx = 0, id = 0;
		for (int i = 0; i < l; ++i) {
			Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
			while (Ma[i + Mp[i]] == Ma[i - Mp[i]]) Mp[i]++;
			if (i + Mp[i] > mx) {
				mx = i + Mp[i];
				id = i;
			}
		}
	}
	bool check(int l, int r) {
		int il = (l + 1) * 2, ir = (r + 1) * 2;
		int mid = (il + ir) / 2;
		int len = (r - l + 2) / 2;
		return (Mp[mid] / 2) >= len;		
	}
}man;

struct PAM{         
	// 每个节点代表一个回文串
    int Next[N][ALP]; // next指针,参照Trie树
    int fail[N];      // fail失配后缀链接
    int cnt[N];       // 此回文串出现个数
    int num[N];       // 以节点i结尾的回文串个数
    int len[N];       // 节点i的回文串长度
    int s[N];         // 存放添加的字符
    int last;         //指向上一个字符所在的节点，方便下一次add
    int n;            // 已添加字符个数
    int p;            // 节点个数
 
    int newnode(int w){ // 初始化节点，w=长度
        for(int i=0;i<ALP;i++)
            Next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }
    void init(){
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; 		 // 开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }
    int get_fail(int x){ // 和KMP一样，失配后找一个尽量最长的
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    bool add(int c){
		bool F = 0;
        c -= 'a';
        s[++n] = c;
		//通过上一个回文串找这个回文串的匹配位置
		int cur = get_fail(last);
		//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
		if(!Next[cur][c]){
            int now = newnode(len[cur]+2);//新建节点
			//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            fail[now] = Next[get_fail(fail[cur])][c];
            Next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
			F = 1;
		}
        last = Next[cur][c];
        cnt[last]++;
		return F;
		//那么此时的p - 2就表示加入这个字符后共有多少个本质不同的回文串
    }
    void count(){
        // 最后统计一遍每个节点出现个数
        // 父亲累加儿子的cnt,类似SAM中parent树
        // 满足parent拓扑关系
        for(int i=p-1;i>=0;i--)
            cnt[fail[i]] += cnt[i];
    }
}pam; 
char s[N];
int f[N], g[N]; 
int res[N], len;

int main() {
	while (scanf("%s", s) != EOF) {
		len = strlen(s);
		man.init(len); man.work(s); 
		pam.init();   
		for (int i = 0; i <= len; ++i) res[i] = 0;
		for (int i = 0; i < len; ++i) {
			if (pam.add(s[i])) {  
				g[i] = 1;
			} else {
				g[i] = 0;
			}
			f[i] = pam.last; 
		}
		pam.count(); 
		for (int i = 0; i < len; ++i) { 
			if (g[i] == 0) continue;
			int Len = pam.len[f[i]];
			int l = i - Len + 1;
			int r = i;
			int mid = (l + r) >> 1; 
			if (man.check(l, mid)) {
				res[Len] += pam.cnt[f[i]];
			}
		}
		for (int i = 1; i <= len; ++i) printf("%d%c", res[i], " \n"[i == len]);
	}
	return 0;
}

