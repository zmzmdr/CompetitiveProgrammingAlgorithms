/**
 * http://acm.hdu.edu.cn/showproblem.php?pid=5443
 * template problem, for testing
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 51234;
const int maxLog = 20;

/**
 * RMQ(Range Maximum Queries), also named ST(Sparse Table)
 * min's, max's parameter L, R indicated [L, R]
 */
template<typename T>
struct RMQ {
    T mn[N][maxLog], mx[N][maxLog];
    int n;

    void init(const std::vector<T> &A) {
        n = A.size();
        for (int i = 0; i < n; i++) mx[i][0] = mn[i][0] = A[i];
        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
                mx[i][j] = std::max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            }
    }

    std::tuple<int, int, int> normal(int L, int R) {
        if (L > R) std::swap(L, R);
        R = std::min(n - 1, R);
        L = std::max(0, L);
        int k = 0;
        while ((1 << (k + 1)) <= R - L + 1) k++;
        return std::make_tuple(L, R, k);
    }

    T max(int L, int R) {
        std::tuple<int, int, int> interval = this->normal(L, R);
        L = std::get<0>(interval);
        R = std::get<1>(interval);
        int k = std::get<2>(interval);
        return std::max(mx[L][k], mx[R - (1 << k) + 1][k]);
    }

    T min(int L, int R) {
        std::tuple<int, int, int> interval = this->normal(L, R);
        L = std::get<0>(interval);
        R = std::get<1>(interval);
        int k = std::get<2>(interval);
        return std::min(mn[L][k], mn[R - (1 << k) + 1][k]);
    }
};

RMQ<int> rmq;

int main() {
    int T, n, m;
    while (cin >> T) {
        while (T--) {
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; i++) cin >> a[i];
            rmq.init(a);

            cin >> m;
            while (m--) {
                int L, R;
                cin >> L >> R;
                L--;
                R--;
                cout << rmq.max(L, R) << endl;
            }
        }
    }

    return 0;
}


