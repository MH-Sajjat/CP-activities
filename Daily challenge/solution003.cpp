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

const int N      = (int) 2e5 + 5;
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

inline int add(int a, int b, int mod) {
    a += b; return a >= mod ? a - mod : a < 0 ? a + mod : a;
}
inline int mult(int a, int b, int mod) { return (ll) a * b % mod; }

template <TN T> inline void umin(T &x, T y) { x = x < y ? x : y; }
template <TN T> inline void umax(T &x, T y) { x = x > y ? x : y; }

template <TN T> inline T gcd(T a, T b) { return !b ? a : gcd(b, a % b); }
template <TN T> inline T lcm(T a, T b) { return a * (b / gcd(a, b)); }

class Hashing {
    int power(ll base, ll exp, const int mod) {
        int res = 1;
        base %= mod;
        if (base < 0) base += mod;
        while (exp) {
            if (exp & 1) res = (1LL * res * base) % mod;
            base = (1LL * base * base) % mod;
            exp >>= 1;
        }
        return res;
    }
    int get(char ch) { return ch - 'a' + 1; }

    const int MOD1 = 127657753, MOD2 = 987654319;
    const int BASE1 = 100003, BASE2 = 100103;
    const int inveMod1 = power(BASE1, MOD1 - 2, MOD1);
    const int inveMod2 = power(BASE2, MOD2 - 2, MOD2);
    vector<pii> pw, invPw;
    vector<pii> hash;
    int n;
    vi s;

    void build() {
        hash.pb({0, 0});
        for (int i = 0; i < n; ++i) {
            pii p;
            p.ff = add(hash[i].ff, mult(get(s[i]), pw[i].ff, MOD1), MOD1);
            p.ss = add(hash[i].ss, mult(get(s[i]), pw[i].ss, MOD2), MOD2);
            hash.pb(p);
        }
    }

public:
    Hashing(vi& _s) {
        s = _s;
        n = szof(s);
        pw.assign(n + 2, {1, 1});
        invPw.assign(n + 2, {1, 1});
        for (int i = 1; i <= n; ++i) {
            pw[i].ff = mult(pw[i - 1].ff, BASE1, MOD1);
            pw[i].ss = mult(pw[i - 1].ss, BASE2, MOD2);
            invPw[i].ff = mult(invPw[i - 1].ff, inveMod1, MOD1);
            invPw[i].ss = mult(invPw[i - 1].ss, inveMod2, MOD2);
        }
        build();
    }

    pii getHash(int l, int r) {
        pii p;
        p.ff = mult(add(hash[r].ff, -hash[l - 1].ff, MOD1), invPw[l - 1].ff, MOD1);
        p.ss = mult(add(hash[r].ss, -hash[l - 1].ss, MOD2), invPw[l - 1].ss, MOD2);
        return p;
    }
};

class Bit {
    vector<int> tree;

public:
    Bit() {
        tree.assign(N + 2, 0);
    }
    void update(int idx, int val) {
        while (idx <= N) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }
    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    // Fast_IO
    int test = Int(), tc = 0;
    while (test--) {
        int n = Int();
        vi nums(n, 0);
        vll rotate(n, 0);

        for (auto& x : nums) {
            x = Int();
        }
        vi tempt = nums;
        sort(all(tempt));
        tempt.erase(unique(all(tempt)), tempt.end());
        for (auto& x : nums) {
            x = lower_bound(all(tempt), x) - tempt.begin();
            x++;
        }
        ll numInv = 0;
        Bit ds;
        for (auto x : nums) {
            numInv += ds.query(x + 1, N);
            ds.update(x, 1);
        }
        rotate[0] = numInv;
        for (int i = 1; i < n; ++i) {
            numInv -= ds.query(nums[i - 1] - 1);
            numInv += ds.query(nums[i - 1] + 1, N);
            rotate[i] = numInv;
        }
        ll mx = rotate[0];
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (rotate[i] > mx) {
                mx = rotate[i];
                k = i;
            }
        }
        vi v = nums;
        for (auto x : v) nums.pb(x);
        Hashing ds1(nums);
        for (int i = k + 1; i < n; ++i) {
            if (rotate[i] == mx) {
                int same = 0;
                int l = 1, r = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (ds1.getHash(k + 1, k + mid) == ds1.getHash(i + 1, i + mid)) {
                        same = mid;
                        l = mid + 1;
                    } else r = mid - 1;
                }
                if (same < n) {
                    if (nums[k + same] > nums[i + same]) {
                        k = i;
                    }
                }
            }
        }
        cout << k << " " << rotate[k] << nl;
    }
    return 0;
}
