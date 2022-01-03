#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;
 
typedef long long          ll;
typedef long double        ld;
typedef unsigned long long ull;
typedef pair <int, int>    pii;
typedef pair <ll, ll>      pll;
typedef vector <int>       vi;
typedef vector <ll>        vll;
typedef tree <pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> pbds_set;
typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds_multiset;
 
inline int Int() { int x; scanf("%d", &x); return x; }
inline ll Long() { ll x; scanf("%lld", &x); return x; }
 
int dx[8] = { 0, -1, 0, 1, -1, -1, 1, 1 };
int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };
 
const int N      = (int) 2000001;
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
 
// inline int add(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a < 0 ? a + mod : a; }
inline int mult(int a, int b, int mod) { return (ll) a * b % mod; }
 
template <TN T> inline void umin(T &x, T y) { x = x < y ? x : y; }
template <TN T> inline void umax(T &x, T y) { x = x > y ? x : y; }
 
template <TN T> T gcd(T a, T b) { return !b ? a : gcd(b, a % b); }
template <TN T> T lcm(T a, T b) { return a * (b / gcd(a, b)); }
 
vector<int> graph[N + 2];
set<int> temp;
int ar[N + 2], br[N + 2];
ll final_ans = 0;
 
unordered_map<int, int> m;
 
pbds_set tre[N + 2];
int get(int x) { return m[x]; }
 
void add(int idx, int val, int node) {
    while (idx <= 200000) {
        tre[idx].insert({val , node});
        idx += (idx & -idx);
    }
}
void remove(int idx, int val, int node) {
    while (idx <= 200000) {
        tre[idx].erase({val, node});
        idx += (idx & -idx);
    }
}
void query(int idx, int val) {
    while (idx > 0) {
        final_ans += (ll) tre[idx].order_of_key({val, 0});
        idx -= (idx & -idx);
    }
}
 
void dfs(int u, int par = -1) {
    query(get(ar[u]) - 1 , get(br[u]));
    add(get(ar[u]) , get(br[u]) , u);
    for (auto v : graph[u]) {
        if (v != par) dfs(v, u);
    }
    remove(get(ar[u]) , get(br[u]) , u);
}
 
int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    // Fast_IO
    int test = 1, tc = 0;
    while (test--) {
        int n = Int();
        for (int i = 1; i < n; ++i) {
            int u = Int(), v = Int();
            graph[u].pb(v);
            graph[v].pb(u);
        }
        for (int i = 1; i <= n; ++i) {
            ar[i] = Int();
            temp.insert(ar[i]);
        }
        for (int i = 1; i <= n; ++i) {
            br[i] = Int();
            temp.insert(br[i]);
        }
        int cnt = 0;
        for (int x : temp) m[x] = ++cnt;
        dfs(1);
        printf("%lld\n", final_ans);
    }
    return 0;
}
