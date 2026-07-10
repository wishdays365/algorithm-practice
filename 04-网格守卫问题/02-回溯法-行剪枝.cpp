#include <iostream>
#include <vector>

using namespace std;

int m, n;
int min_guards = 1e9; // 记录最少哨兵数量
int best_count = 0;   // 记录最优解的个数

// 监视计数矩阵，covered[r][c] > 0 表示该点已被监视
vector<vector<int>> covered;

// 改变哨兵对格点的影响 (is_add = true 表示放置，false 表示撤销)
void toggle_guard(int r, int c, bool is_add) {
    int delta = is_add ? 1 : -1;
    covered[r][c] += delta;
    if (r > 0) covered[r - 1][c] += delta;
    if (r < m - 1) covered[r + 1][c] += delta;
    if (c > 0) covered[r][c - 1] += delta;
    if (c < n - 1) covered[r][c + 1] += delta;
}

// 检查第 r 行是否已经全部被监视
bool is_row_covered(int r) {
    if (r < 0) return true;
    for (int c = 0; c < n; ++c) {
        if (covered[r][c] == 0) return false;
    }
    return true;
}

// 回溯搜索函数
void backtrack(int r, int c, int current_count) {
    // 剪枝 1：当前哨兵数已超过已知最优解
    if (current_count > min_guards) return;

    // 当一行结束，准备跳到下一行开头
    if (c == n) {
        // 剪枝 2：当离开第 r 行时，第 r-1 行必须全部被监视
        if (r > 0 && !is_row_covered(r - 1)) return;
        
        r++;
        c = 0;
    }

    // 终点：所有行都处理完毕
    if (r == m) {
        // 最终检查：最后一行（第 m-1 行）是否也全部被监视
        if (is_row_covered(m - 1)) {
            if (current_count < min_guards) {
                min_guards = current_count;
                best_count = 1; // 刷新最优解个数
            } else if (current_count == min_guards) {
                best_count++;   // 累加最优解个数
            }
        }
        return;
    }

    // 分支 1：在当前位置 (r, c) 放置哨兵
    toggle_guard(r, c, true);
    backtrack(r, c + 1, current_count + 1);
    toggle_guard(r, c, false); // 回溯

    // 分支 2：不放置哨兵
    // 可选剪枝 3：如果当前是第 r 行，且上一行对应的 (r-1, c) 在之后再也无法被监视到，则当前位置必须放，不能跳过
    if (r > 0 && covered[r - 1][c] == 0) {
        // 如果上面那个格点没被监视，且当前是最后一次能救它的机会（因为下一行影响不到 r-1），则必须放
        // 此时不放置的分支直接不走，强制走放置分支
        return;
    }
    backtrack(r, c + 1, current_count);
}

int main() {
    // 提高输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (cin >> m >> n) {
        covered.assign(m, vector<int>(n, 0));
        
        // 从 (0, 0) 开始搜索，初始哨兵数为 0
        backtrack(0, 0, 0);

        cout << min_guards << endl;
        cout << best_count << endl;
    }
    return 0;
}
