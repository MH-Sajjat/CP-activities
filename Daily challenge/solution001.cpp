#include <bits/stdc++.h>
using namespace std;

typedef long long          ll;
typedef long double        ld;
typedef unsigned long long ull;
typedef pair <int, int>    pii;
typedef pair <ll, ll>      pll;
typedef vector <int>       vi;
typedef vector <ll>        vll;

inline int Int() { int x; scanf("%d", &x); return x; }
inline ll Long() { ll x; scanf("%lld", &x); return x; }

int dx[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };

const int N      = (int) 5e5 + 5;
const int mxN    = (int) 1e6 + 6;
const int MOD    = (int) 1e9 + 7;
const int INF    = (int) 1e9 + 9;
const double EPS = (double) 1e-9;

#define debug(x) cerr << #x << " = " << x << '\n';
#define all(x)   x.begin(), x.end()
#define szof(x)  (int) x.size()
#define ff       first
#define ss       second
#define pb       push_back
#define mp       make_pair
#define PI       acos(-1.0)
#define TN       typename
#define nl       '\n'
#define Fast_IO  ios_base::sync_with_stdio(false); cin.tie(nullptr);

inline int add(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a < 0 ? a + mod : a; }
inline int mult(int a, int b, int mod) { return (ll) a * b % mod; }

template <TN T> inline void umin(T &x, T y) { x = x < y ? x : y; }
template <TN T> inline void umax(T &x, T y) { x = x > y ? x : y; }

template <TN T> T gcd(T a, T b) { return !b ? a : gcd(b, a % b); }
template <TN T> T lcm(T a, T b) { return a * (b / gcd(a, b)); }

ll nums[N];
const ll blk = 500;
ll invCount = 0;

struct Data1 {
    int l, r, id;
    bool operator < (Data1 a) {
        if (l / blk == a.l / blk) return (l / blk) & 1 ? r > a.r : r < a.r;
        return l / blk < a.l / blk;
    }
};

// bit
ll tree[N + 2];
void update(int idx, int val) {
    while (idx <= N) {
        tree[idx] += val;
        idx += (idx & -idx);
    }
}
ll query(int idx) {
    ll sum = 0;
    while (idx > 0) {
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}
ll query(int l, int r) {
    return query(r) - query(l - 1);
}

// add or remove
void add(int x) {
    x = nums[x];
    invCount += query(x + 1, N);
    update(x, 1);
}
void remove(int x) {
    x = nums[x];
    invCount -= query(x + 1, N);
    update(x, -1);
}
void add1(int x) {
    x = nums[x];
    invCount += query(x - 1);
    update(x, 1);
}
void remove1(int x) {
    x = nums[x];
    invCount -= query(x - 1);
    update(x, -1);
}

// mos algorithm
vll moAlgorithm(vector<Data1>& qry) {
    int m = szof(qry);
    sort(all(qry));

    int curL = 1, curR = 0;
    vll res(m + 2, 0);
    for (auto x : qry) {
        while (curL < x.l) remove1(curL++);
        while (curL > x.l) add1(--curL);
        while(curR > x.r) remove(curR--);
        while (curR < x.r) add(++curR);
        res[x.id] = invCount;
    }
    return res;
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    // Fast_IO
    int test = 1, tc = 0;
    while (test--) {
        int n = Int(), m = Int();
        vll v;
        for (int i = 1; i <= n; ++i) {
            nums[i] = Long();
            v.pb(nums[i]);
        }
        sort(all(v));
        v.erase(unique(all(v)), v.end());
        map<ll, ll> maP;
        ll state = 0;
        for (ll& x : v) maP[x] = ++state;
        for (int i = 1; i <= n; ++i) {
            nums[i] = maP[nums[i]];
        }

        vector<Data1> qry;
        for (int i = 1; i <= m; ++i) {
            Data1 dt;
            dt.l = Int(), dt.r = Int(), dt.id = i;
            qry.pb(dt);
        }
        vll res = moAlgorithm(qry);
        for (int i = 1; i <= m; ++i) printf("%lld\n", res[i]);

    }
    return 0;
}
