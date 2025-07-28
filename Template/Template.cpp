#include <bits/stdc++.h>

#ifdef USE_ORDERED_STATISTICS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
#endif

#define all(v) (v).begin(), (v).end()
#define sz(v) (int)v.size()
#define eq(a, b) (fabs(a - b) < EPS)
#define md(a, b) ((a) % b + b) % b
#define mod(a) md(a, MOD)
#define srt(a) sort(all(a))
// sort(all(v), [](int a, int b){ return a > b; });

#define mem(a, h) memset(a, (h), sizeof(a))
#define f first
#define s second
#define forn(i, n) for (int i = 0; i < (n); i++)
#define forb(i, a, b) for (int i = a; i < (b); i++)

#define fastIO() cout.tie(0), cin.tie(0)->sync_with_stdio(0);

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

const int tam = 100010;
const int MOD = 1000000007;
const int MOD1 = 998244353;
const double EPS = 1e-9;
const double PI = acos(-1);
const int INFI = 1e9 + 5;
const ll INFL = 1e18 + 5;

int main() {
    fastIO();
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // Codear
}
