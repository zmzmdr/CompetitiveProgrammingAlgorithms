#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
#define pii pair<int,int>
#define mp(x, y) make_pair(x,y)
#define what_is(x) cout << #x << " is " << x << endl;
#define rep(i, n) for(int i = 0; i < n; ++i)
using ll = long long;
gp_hash_table<string, int> H;
const ll N = 7e5;
const ll MOD = 666;
vector<int> a[2];

struct EulerPrime {
    vector<int> phi;
    vector<int> prime;
    unordered_set<int> vis;

    void init(int n) {
        phi.reserve(n);
        prime.reserve(n);
        phi[1] = 1;
        int p = 0;
        for (int i = 2; i < n; i++) {
            if (vis.count(i) == 0) {
                phi[i] = 2;
                prime.emplace_back(i);
            }
            for (auto j = 0; j < prime.size() && i * prime[j] < n; j++) {
                int tep = i * prime[j];
                vis.insert(tep);
                if (i % prime[j])
                    phi[tep] = phi[i] * 2;
                else if (i % (prime[j] * prime[j]) == 0)
                    phi[tep] = 0;
                else {
                    phi[tep] = phi[i] / 2;
                    break;
                }
            }
        }
    }
} slv;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    slv.init(1e6);
}
