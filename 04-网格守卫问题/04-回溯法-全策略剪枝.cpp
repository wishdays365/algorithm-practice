#include <iostream>
#include <vector>

// 全局变量：存储网格参数与搜索状态
int grid_rows, grid_cols;
int total_cell;
int min_guard_num;
long long solution_count;

std::vector<int> cell_cover_times;
std::vector<std::vector<int>> guard_effect;
std::vector<std::vector<int>> cell_guards;
std::vector<int> suffix_max_cover;
int no_cover_cell;

// 放置守卫：更新覆盖状态
void place_guard(int pos) {
    for (int cell : guard_effect[pos]) {
        if (cell_cover_times[cell] == 0)
            no_cover_cell--;
        cell_cover_times[cell]++;
    }
}

// 移除守卫：恢复覆盖状态
void cancel_guard(int pos) {
    for (int cell : guard_effect[pos]) {
        cell_cover_times[cell]--;
        if (cell_cover_times[cell] == 0)
            no_cover_cell++;
    }
}

// 判断当前位置是否必须放置守卫
bool check_must_place(int pos) {
    if (cell_cover_times[pos] > 0)
        return false;
    for (int g : cell_guards[pos]) {
        if (g >= pos)
            return false;
    }
    return true;
}

// 判断剩余位置无法完成全覆盖，直接剪枝
bool check_unreachable(int pos) {
    for (int i = 0; i < total_cell; i++) {
        if (cell_cover_times[i] > 0)
            continue;
        bool flag = false;
        for (int g : cell_guards[i]) {
            if (g >= pos) {
                flag = true;
                break;
            }
        }
        if (!flag)
            return true;
    }
    return false;
}

// 回溯搜索核心函数
void backtrack(int curr_pos, int used_guard) {
    // 基础剪枝：超过最优解直接返回
    if (used_guard > min_guard_num)
        return;

    // 所有格子已覆盖，更新最优解
    if (no_cover_cell == 0) {
        if (used_guard < min_guard_num) {
            min_guard_num = used_guard;
            solution_count = 1;
        } else if (used_guard == min_guard_num) {
            solution_count++;
        }
        return;
    }

    // 达到当前最优解数量，无需继续
    if (used_guard == min_guard_num)
        return;
    // 遍历完所有位置
    if (curr_pos == total_cell)
        return;
    // 无法覆盖所有格子，剪枝
    if (check_unreachable(curr_pos))
        return;
    // 后缀最大覆盖不足，剪枝
    if (no_cover_cell > suffix_max_cover[curr_pos])
        return;

    // 启发式剪枝：估算最小需要守卫数
    int need_guard = (no_cover_cell + 4) / 5;
    if (used_guard + need_guard > min_guard_num)
        return;

    // 剩余位置最多覆盖数不足，剪枝
    int left_pos = total_cell - curr_pos;
    if (left_pos * 5 < no_cover_cell)
        return;

    // 必须放置守卫的情况
    if (check_must_place(curr_pos)) {
        place_guard(curr_pos);
        backtrack(curr_pos + 1, used_guard + 1);
        cancel_guard(curr_pos);
        return;
    }

    // 计算当前守卫能新增覆盖的格子数
    int add_cover = 0;
    for (int cell : guard_effect[curr_pos]) {
        if (cell_cover_times[cell] == 0)
            add_cover++;
    }

    // 无增益，直接跳过
    if (add_cover == 0) {
        backtrack(curr_pos + 1, used_guard);
        return;
    }

    // 高收益优先放置，优化搜索顺序
    if (add_cover >= 3) {
        place_guard(curr_pos);
        backtrack(curr_pos + 1, used_guard + 1);
        cancel_guard(curr_pos);
        backtrack(curr_pos + 1, used_guard);
    } else {
        backtrack(curr_pos + 1, used_guard);
        place_guard(curr_pos);
        backtrack(curr_pos + 1, used_guard + 1);
        cancel_guard(curr_pos);
    }
}

int main() {
    // 输入网格尺寸
    std::cin >> grid_rows >> grid_cols;
    total_cell = grid_rows * grid_cols;

    // 初始化数组
    guard_effect.resize(total_cell);
    cell_guards.resize(total_cell);

    // 预处理每个守卫的覆盖范围（自身+上下左右）
    for (int r = 0; r < grid_rows; r++) {
        for (int c = 0; c < grid_cols; c++) {
            int idx = r * grid_cols + c;
            guard_effect[idx].push_back(idx);
            // 上
            if (r > 0)
                guard_effect[idx].push_back((r - 1) * grid_cols + c);
            // 下
            if (r + 1 < grid_rows)
                guard_effect[idx].push_back((r + 1) * grid_cols + c);
            // 左
            if (c > 0)
                guard_effect[idx].push_back(r * grid_cols + c - 1);
            // 右
            if (c + 1 < grid_cols)
                guard_effect[idx].push_back(r * grid_cols + c + 1);
        }
    }

    // 预处理每个格子被哪些守卫覆盖
    for (int i = 0; i < total_cell; i++) {
        for (int cell : guard_effect[i]) {
            cell_guards[cell].push_back(i);
        }
    }

    // 预处理后缀最大覆盖数，用于剪枝
    suffix_max_cover.assign(total_cell + 1, 0);
    for (int i = total_cell - 1; i >= 0; i--) {
        suffix_max_cover[i] = suffix_max_cover[i + 1] + (int)guard_effect[i].size();
    }

    // 初始化搜索状态
    cell_cover_times.assign(total_cell, 0);
    no_cover_cell = total_cell;
    min_guard_num = total_cell + 1;
    solution_count = 0;

    // 开始搜索
    backtrack(0, 0);

    // 输出结果
    std::cout << min_guard_num << '\n';
    std::cout << solution_count << '\n';

    return 0;
}
