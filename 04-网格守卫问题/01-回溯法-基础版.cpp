
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 高精度加法
vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    size_t i = 0;
    while (i < a.size() || i < b.size() || carry) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        res.push_back(sum % 10);
        carry = sum / 10;
        ++i;
    }
    return res;
}

void printBig(const vector<int>& v) {
    if (v.empty()) { cout << 0 << endl; return; }
    for (int i = v.size()-1; i >= 0; --i) cout << v[i];
    cout << endl;
}

int countBits(int x) {
    int c = 0;
    while (x) { c += x & 1; x >>= 1; }
    return c;
}

struct State {
    int minCnt;
    vector<int> ways;
    State() : minCnt(INT_MAX) {}
    State(int c, const vector<int>& w) : minCnt(c), ways(w) {}
};

int computeRequiredMask(int prev, int curr, int n) {
    int req = 0;
    for (int j = 0; j < n; ++j) {
        bool needPrevPrev = true;
        if (prev & (1<<j)) needPrevPrev = false;
        if (j>0 && (prev & (1<<(j-1)))) needPrevPrev = false;
        if (j<n-1 && (prev & (1<<(j+1)))) needPrevPrev = false;
        if (curr & (1<<j)) needPrevPrev = false;
        if (needPrevPrev) req |= (1<<j);
    }
    return req;
}

vector<vector<State>> zetaTransform(const vector<vector<State>>& dp, int n) {
    int S = 1 << n;
    vector<vector<State>> sum(S, vector<State>(S));
    for (int prev=0; prev<S; ++prev)
        for (int mask=0; mask<S; ++mask)
            sum[mask][prev] = dp[mask][prev];
    for (int bit=0; bit<n; ++bit) {
        for (int mask=0; mask<S; ++mask) {
            if (!(mask & (1<<bit))) {
                int bigger = mask | (1<<bit);
                for (int prev=0; prev<S; ++prev) {
                    State& cur = sum[mask][prev];
                    const State& other = sum[bigger][prev];
                    if (other.minCnt < cur.minCnt) {
                        cur = other;
                    } else if (other.minCnt == cur.minCnt && other.minCnt != INT_MAX) {
                        cur.ways = add(cur.ways, other.ways);
                    }
                }
            }
        }
    }
    return sum;
}

bool checkLastRow(int prev, int curr, int n) {
    int full = (1<<n)-1;
    for (int j=0; j<n; ++j) {
        bool covered = false;
        if (prev & (1<<j)) covered = true;
        if (curr & (1<<j)) covered = true;
        if (j>0 && (curr & (1<<(j-1)))) covered = true;
        if (j<n-1 && (curr & (1<<(j+1)))) covered = true;
        if (!covered) return false;
    }
    return true;
}

int main() {
    int m, n;
    cin >> m >> n;
    if (m < n) swap(m, n);   // 让 n 为较小维度
    int S = 1 << n;
    vector<vector<State>> dp(S, vector<State>(S));
    // 初始化第一行
    for (int s=0; s<S; ++s) {
        dp[0][s] = State(countBits(s), {1});
    }
    // 逐行转移
    for (int row=2; row<=m; ++row) {
        auto sum = zetaTransform(dp, n);
        vector<vector<State>> ndp(S, vector<State>(S));
        for (int prev=0; prev<S; ++prev) {
            for (int curr=0; curr<S; ++curr) {
                int req = computeRequiredMask(prev, curr, n);
                State best = sum[req][prev];
                if (best.minCnt == INT_MAX) continue;
                int newCnt = best.minCnt + countBits(curr);
                if (newCnt < ndp[prev][curr].minCnt) {
                    ndp[prev][curr].minCnt = newCnt;
                    ndp[prev][curr].ways = best.ways;
                } else if (newCnt == ndp[prev][curr].minCnt) {
                    ndp[prev][curr].ways = add(ndp[prev][curr].ways, best.ways);
                }
            }
        }
        dp = move(ndp);
    }
    // 收集最终答案
    int bestCnt = INT_MAX;
    vector<int> totalWays = {0};
    for (int prev=0; prev<S; ++prev) {
        for (int curr=0; curr<S; ++curr) {
            if (dp[prev][curr].minCnt == INT_MAX) continue;
            if (!checkLastRow(prev, curr, n)) continue;
            int curCnt = dp[prev][curr].minCnt;
            if (curCnt < bestCnt) {
                bestCnt = curCnt;
                totalWays = dp[prev][curr].ways;
            } else if (curCnt == bestCnt) {
                totalWays = add(totalWays, dp[prev][curr].ways);
            }
        }
    }
    cout << bestCnt << endl;
    printBig(totalWays);
    return 0;
}