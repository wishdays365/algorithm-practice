#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 高精度大整数，用于存储超大方案数
struct BigNum {
    vector<int> digits;

    BigNum() {
        digits.push_back(0);
    }

    BigNum(long long num) {
        if (num == 0) {
            digits.push_back(0);
            return;
        }
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    void add(const BigNum& other) {
        int carry = 0;
        int max_size = max(digits.size(), other.digits.size());

        for (int i = 0; i < max_size || carry; ++i) {
            if (i >= digits.size())
                digits.push_back(0);

            int sum = digits[i] + carry;
            if (i < other.digits.size())
                sum += other.digits[i];

            digits[i] = sum % 10;
            carry = sum / 10;
        }
    }

    void print() const {
        for (int i = digits.size() - 1; i >= 0; --i)
            cout << digits[i];
        cout << endl;
    }
};

// 全局搜索状态
int row_cnt, col_cnt;
int total_grid;
int block_num;

vector<vector<unsigned long long>> cover_mask;
vector<vector<unsigned long long>> must_place;
vector<int> max_cover_suffix;
vector<vector<unsigned long long>> cover_state;

int min_guard = 1e9;
BigNum total_solution(0);

// 分支限界核心搜索
void dfs_search(int pos, int used, int left_uncover) {
    // 全部覆盖完成
    if (left_uncover <= 0) {
        if (used < min_guard) {
            min_guard = used;
            total_solution = BigNum(1);
        } else if (used == min_guard) {
            total_solution.add(BigNum(1));
        }
        return;
    }

    // 边界剪枝
    if (pos >= total_grid || used >= min_guard)
        return;

    int best_single = max_cover_suffix[pos];
    if (best_single == 0)
        return;

    // 下界估计：不可能更优则剪枝
    int lower_bound = used + (left_uncover + best_single - 1) / best_single;
    if (lower_bound > min_guard)
        return;

    // 选择1：在当前位置放置守卫
    int new_cover = 0;
    for (int i = 0; i < block_num; ++i) {
        unsigned long long add = cover_mask[pos][i] & (~cover_state[pos][i]);
        new_cover += __builtin_popcountll(add);
        cover_state[pos+1][i] = cover_state[pos][i] | cover_mask[pos][i];
    }
    dfs_search(pos + 1, used + 1, left_uncover - new_cover);

    // 选择2：不放置，检查是否允许跳过
    bool allow_skip = true;
    for (int i = 0; i < block_num; ++i) {
        if ((must_place[pos][i] & cover_state[pos][i]) != must_place[pos][i]) {
            allow_skip = false;
            break;
        }
    }

    if (allow_skip) {
        for (int i = 0; i < block_num; ++i) {
            cover_state[pos+1][i] = cover_state[pos][i];
        }
        dfs_search(pos + 1, used, left_uncover);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> row_cnt >> col_cnt;

    // 行列优化，减少状态规模
    if (row_cnt < col_cnt)
        swap(row_cnt, col_cnt);

    total_grid = row_cnt * col_cnt;
    block_num = (total_grid + 63) >> 6;

    cover_mask.resize(total_grid, vector<unsigned long long>(block_num, 0));
    vector<int> single_cover(total_grid, 0);

    // 坐标转编号
    auto get_id = [&](int r, int c) {
        return r * col_cnt + c;
    };

    // 预处理每个位置的覆盖范围
    for (int r = 0; r < row_cnt; ++r) {
        for (int c = 0; c < col_cnt; ++c) {
            int idx = get_id(r, c);
            auto add_cover = [&](int nr, int nc) {
                if (nr < 0 || nr >= row_cnt || nc < 0 || nc >= col_cnt)
                    return;
                int x = get_id(nr, nc);
                if (!(cover_mask[idx][x >> 6] & (1ULL << (x & 63)))) {
                    cover_mask[idx][x >> 6] |= (1ULL << (x & 63));
                    single_cover[idx]++;
                }
            };

            add_cover(r, c);
            add_cover(r-1, c);
            add_cover(r+1, c);
            add_cover(r, c-1);
            add_cover(r, c+1);
        }
    }

    // 后缀最大覆盖数（剪枝用）
    max_cover_suffix.resize(total_grid + 1, 0);
    for (int i = total_grid - 1; i >= 0; --i) {
        max_cover_suffix[i] = max(max_cover_suffix[i+1], single_cover[i]);
    }

    // 预处理必须放置的条件
    must_place.resize(total_grid, vector<unsigned long long>(block_num, 0));
    for (int i = 0; i < total_grid; ++i) {
        int last_pos = -1;
        for (int j = total_grid - 1; j >= 0; --j) {
            if (cover_mask[i][j >> 6] & (1ULL << (j & 63))) {
                last_pos = j;
                break;
            }
        }
        if (last_pos != -1) {
            must_place[last_pos][i >> 6] |= (1ULL << (i & 63));
        }
    }

    // 初始化覆盖状态
    cover_state.resize(total_grid + 1, vector<unsigned long long>(block_num, 0));

    // 开始搜索
    dfs_search(0, 0, total_grid);

    // 输出结果
    cout << min_guard << endl;
    total_solution.print();

    return 0;
}
/* */