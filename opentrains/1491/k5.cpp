#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
/* I got this from Ivan Katanic with permission to use it at UZI.
I modified it to support testcases.
Complexity O(n log^2 n). */
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<
typedef long long llint;
const int MAXN = 1100030;
const int N = 2e5 + 10;
int n, m;
char s[N], q[N]; 
namespace SuffixArray {
	int lcp[MAXN], A[MAXN];

	int tmp[MAXN], bc[MAXN];

	void build(char *s, int n) {
		REP(i, n) A[i] = i, bc[i] = s[i];

		for (int T = 1; ; T *= 2) {
			auto cmp = [&s, &T, &n] (const int &a, const int &b) {
				if (bc[a] != bc[b]) return bc[a] < bc[b];
				if (a+T >= n || b+T >= n) return a > b;
				return bc[a+T] < bc[b+T];
			};
			sort(A, A + n, cmp);
			tmp[A[0]] = 0;
			FOR(i, 1, n) tmp[A[i]] = tmp[A[i-1]] + cmp(A[i-1], A[i]);
			REP(i, n) bc[i] = tmp[i];
			if (bc[A[n-1]] == n-1) break;
		}
	}
};
int A[MAXN], B[MAXN];
int posA[MAXN], posB[MAXN];

vector<int> T[2*MAXN];

int count(int i, int lo, int hi, int a, int b, int c, int d) {
	if (lo >= b || hi <= a) return 0;
	if (lo >= a && hi <= b) {
		return
		upper_bound(T[i].begin(), T[i].end(), d-1) -
		lower_bound(T[i].begin(), T[i].end(), c);
	}

	return
	count(i*2, lo, (lo+hi)/2, a, b, c, d) +
	count(i*2+1, (lo+hi)/2, hi, a, b, c, d);
}


struct Hash {
	static ull base[N], B; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * B; 
	}
	ull a[N];  
	void gao(char *s) { 
		a[0] = s[0];
		for (int i = 1; s[i]; ++i) {
			a[i] = a[i - 1] * B + s[i] + 5; 
		}	
	}
	ull get(int l, int r) { 
		return a[r] - a[l - 1] * base[r - l + 1];  
	}
}hs, ht;
ull Hash::base[N] = {0}, Hash::B = 25165843; 


struct Hash2 {
	static ull base[N], B; 
	static void init() {
		base[0] = 1;
		for (int i = 1; i < N; ++i)
			base[i] = base[i - 1] * B; 
	}
	ull a[N];  
	void gao(char *s) { 
		a[0] = s[0];
		for (int i = 1; s[i]; ++i) {
			a[i] = a[i - 1] * B + s[i]; 
		}	
	}
	ull get(int l, int r) { 
		return a[r] - a[l - 1] * base[r - l + 1]; 
	}
}hs2, ht2;
ull Hash2::base[N] = {0}, Hash2::B = 233;  

//倍增求两个串的lcp
int gao2(int x, int y) {
	int res = 0;
	for (int i = 1 << 20; i >= 1; i >>= 1) {
		if (x + i - 1 < n && y + i - 1 < m && hs.get(x, x + i - 1) == ht.get(y, y + i - 1) && hs2.get(x, x + i - 1) == ht2.get(y, y + i - 1)) {
			x += i;
			y += i;
			res += i;
		}
	}
	return res; 
}

bool same(int l, int r, int L, int R) {
	for (int i = l, j = L; i <= r; ++i, ++j) {
		if (s[i] != q[j]) return 0;
	}
	return 1;
}

int gao3(int x, int y) {
	int res = 0;
	for (int i = 1 << 20; i >= 1; i >>= 1) {
		if (x + i - 1 < n && y + i - 1 < m && same(x, x + i - 1, y, y + i - 1)) {
			x += i;
			y += i;
			res += i;
		}
	}
	return res; 
}

int ok2(int x) {
	int y = 0;
	for (int j = 1; j <= 2; ++j) {
		int lcp = gao2(x, y); 
		x += lcp + 1, y += lcp + 1;
		if (j == 2) return y > m; 
		if (y >= m) return 1; 
	}
	return 0;
}


int ok3(int x) {
	int y = 0;
	for (int j = 1; j <= 2; ++j) {
		int lcp = gao3(x, y); 
		x += lcp + 1, y += lcp + 1;
		if (j == 2) return y > m; 
		if (y >= m) return 1; 
	}
	return 0;
}

ll get2() {
	ll res = 0;	
	for (int i = 0; i + m - 1 < n; ++i) {
			res += ok2(i);
		}
	return res;
}

ll get3() {
	ll res = 0;	
	for (int i = 0; i + m - 1 < n; ++i) {
			res += ok3(i);
		}
	return res;
}

void checks(char *s) {
	for (int i = 0; s[i]; ++i)
		assert(s[i] >= 'a' && s[i] <= 'z');
}

void gogogo() {
	scanf("%s", s); n = strlen(s); hs.gao(s); hs2.gao(s); 
	int N = strlen(s); 

	int off = 1;
	while (off <= N + 1) off *= 2;

	SuffixArray::build(s, N);
	REP(i, N) A[i + 1] = SuffixArray::A[i];
	A[0] = N;

	reverse(s, s + N);
	SuffixArray::build(s, N);
	B[0] = 0;
	REP(i, N) B[i + 1] = N - SuffixArray::A[i];
	reverse(s, s + N);

	REP(i, N + 1) posB[B[i]] = i;
	REP(i, N + 1) posA[A[i]] = i;

	REP(i, N) T[off + posA[i+1]].push_back(posB[i]);
	for (int i = off-1; i > 0; --i) {
		T[i].resize(T[i*2].size() + T[i*2+1].size());
		merge(T[i*2].begin(), T[i*2].end(),
			T[i*2+1].begin(), T[i*2+1].end(),
			T[i].begin());
	}


	int Q;
	scanf("%d", &Q);
	int testf = 1;
	REP(i, Q) {
		int a1[N + 10], a2[N + 10];
		scanf("%s", q); m = strlen(q); ht.gao(q); ht2.gao(q); 
		int M = strlen(q);

		a1[M] = 0, a2[M] = N;
		for (int i = M-1; i >= 0; --i) {
			if (a1[i+1] > a2[i+1]) {
				a1[i] = a1[i+1], a2[i] = a2[i+1];
				continue;
			}

			int lo = 0, hi = N + 1;
			while (lo < hi) {
				int mid = (lo + hi) / 2;
				if (A[mid] == N ||
					s[A[mid]] < q[i] ||
					(s[A[mid]] == q[i] && a1[i+1] > posA[A[mid] + 1])) lo = mid + 1;
					else hi = mid;
			}
			a1[i] = lo;

			lo = 0, hi = N;
			while (lo < hi) {
				int mid = (lo + hi + 1) / 2;
				if (A[mid] < N &&
					(s[A[mid]] > q[i] ||
						(q[i] == s[A[mid]] && a2[i+1] < posA[A[mid] + 1]))) hi = mid - 1;
					else lo = mid;
			}

			a2[i] = lo;
		}

		llint ans = 0;
		int b1 = 0, b2 = N;
		for (int i = 0; i < M; ++i) {
			if (b1 > b2) break;

			if (a1[i+1] <= a2[i+1]) {
				ans += count(1, 0, off, a1[i+1], a2[i+1]+1, b1, b2 + 1);
			}

			int lo = 0, hi = N + 1;
			while (lo < hi) {
				int mid = (lo + hi) / 2;
				if (B[mid] == 0 ||
					s[B[mid]-1] < q[i] ||
					(s[B[mid]-1] == q[i] && b1 > posB[B[mid] - 1])) lo = mid + 1;
					else hi = mid;
			}
			int nb1 = lo;

			lo = 0, hi = N;
			while (lo < hi) {
				int mid = (lo + hi + 1) / 2;
				if (B[mid] > 0 &&
					(s[B[mid]-1] > q[i] ||
						(q[i] == s[B[mid]-1] && b2 < posB[B[mid] - 1]))) hi = mid - 1;
					else lo = mid;
			}

			b1 = nb1;
			b2 = lo;
		}

		if (b1 <= b2) {
			ans -= (b2 - b1 + 1) * llint(M - 1); 
		}	
			
		ll bk = get2();
		assert(bk == ans);
	//	if (bk > ans && testf) {
	//		--testf; 
	//		assert(get3() == ans);
	//	}
	//	if (bk > ans && testf) {
	//		--testf;
	//		int bbk = 0;
	//		for (int i = 0; i + m - 1 < n; ++i) {
	//			int cnt = 0;
	//			for (int j = 0; j < m; ++j) {
	//				if (s[i + j] != q[j])
	//					++cnt;
	//			}
	//			if (cnt <= 1) ++bbk;
	//		}	
	//		assert(bbk == ans);
	//	}
		printf(INT64 "\n", ans);

	}
	REP (i, 2 * off + 5) T[i].clear();
}


int main() {
	Hash::init(); Hash2::init();
	int T; scanf("%d", &T);
	while (T--) gogogo(); 
	return 0;
}
