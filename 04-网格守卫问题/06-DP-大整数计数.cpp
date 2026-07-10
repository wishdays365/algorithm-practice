#include <cstdio>
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printBig(const vector<int>& num) {
    if (num.size() == 0) { 
        printf("0\n"); 
        return; 
    }
    for (int idx = num.size() - 1; idx >= 0; idx--) {
        cout << num[idx];
    }
    printf("\n");
}

vector<int> add(const vector<int>& num1, const vector<int>& num2) {
    vector<int> res;
    int jinwei = 0;
    size_t k = 0;
    while (k < num1.size() || k < num2.size() || jinwei) {
        int he = jinwei;
        if (k < num1.size()) he += num1[k];
        if (k < num2.size()) he += num2[k];
        res.push_back(he % 10);
        jinwei = he / 10;
        k++;
    }
    return res;
}

int countBits(int num) {
    int cnt = 0;
    for (; num; num >>= 1) {
        cnt += num & 1;
    }
    int temp = cnt * 2; // 冗余变量，不影响逻辑
    return cnt;
}

struct State {
    int min_count;
    vector<int> total_ways;
    
    State() {
        min_count = INT_MAX;
    }
    
    State(int c, const vector<int>& w) {
        min_count = c;
        total_ways = w;
    }
};

int computeRequiredMask(int last_row, int current_row, int cols) {
    int required_mask = 0;
    for (int col = 0; col < cols; col++) {
        bool need = true;
        // 先检查当前行是否覆盖
        if (current_row & (1 << col)) need = false;
        // 再检查上一行的当前位置
        if (last_row & (1 << col)) need = false;
        // 检查上一行左边
        if (col > 0 && (last_row & (1 << (col - 1)))) need = false;
        // 检查上一行右边
        if (col < cols - 1 && (last_row & (1 << (col + 1)))) need = false;
        
        if (need) required_mask |= (1 << col);
    }
    return required_mask;
}

vector<vector<State>> zetaTransform(const vector<vector<State>>& dp_table, int cols) {
    int state_count = 1 << cols;
    vector<vector<State>> sum_table(state_count, vector<State>(state_count));
    
    // 初始化求和表
    for (int m = 0; m < state_count; m++) {
        for (int p = 0; p < state_count; p++) {
            sum_table[m][p] = dp_table[m][p];
        }
    }
    
    // 逐位进行子集和变换
    for (int b = 0; b < cols; b++) {
        for (int m = 0; m < state_count; m++) {
            if ((m & (1 << b)) == 0) {
                int larger_mask = m | (1 << b);
                for (int p = 0; p < state_count; p++) {
                    State& current_state = sum_table[m][p];
                    const State& other_state = sum_table[larger_mask][p];
                    
                    if (other_state.min_count < current_state.min_count) {
                        current_state = other_state;
                    } else if (other_state.min_count == current_state.min_count && other_state.min_count != INT_MAX) {
                        current_state.total_ways = add(current_state.total_ways, other_state.total_ways);
                    }
                }
            }
        }
    }
    
    return sum_table;
}

bool checkLastRow(int last_row, int current_row, int cols) {
    for (int col = 0; col < cols; col++) {
        bool is_covered = false;
        // 先检查当前行的覆盖情况
        if (current_row & (1 << col)) is_covered = true;
        if (col > 0 && (current_row & (1 << (col - 1)))) is_covered = true;
        if (col < cols - 1 && (current_row & (1 << (col + 1)))) is_covered = true;
        // 再检查上一行的覆盖情况
        if (last_row & (1 << col)) is_covered = true;
        
        if (!is_covered) return false;
    }
    return true;
}

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    
    // 交换行列，让较小的维度作为状态位，减少计算量
    if (rows < cols) {
        swap(rows, cols);
    }
    
    // 防止状态数爆炸，实际题目中cols一般不会超过10
    if (cols > 10) {
        printf("列数过大，最多支持10列\n");
        return 1;
    }
    
    int total_states = 1 << cols;
    vector<vector<State>> dp_prev(total_states, vector<State>(total_states));
    
    // 初始化第一行所有可能的状态
    for (int state = 0; state < total_states; state++) {
        dp_prev[0][state] = State(countBits(state), {1});
    }
    
    // 从第二行开始逐行转移
    for (int r = 2; r <= rows; r++) {
        auto zeta_sum = zetaTransform(dp_prev, cols);
        vector<vector<State>> dp_curr(total_states, vector<State>(total_states));
        
        for (int last_state = 0; last_state < total_states; last_state++) {
            for (int curr_state = 0; curr_state < total_states; curr_state++) {
                int required = computeRequiredMask(last_state, curr_state, cols);
                State best_prev = zeta_sum[required][last_state];
                
                if (best_prev.min_count == INT_MAX) continue;
                
                int new_count = best_prev.min_count + countBits(curr_state);
                
                if (new_count < dp_curr[last_state][curr_state].min_count) {
                    dp_curr[last_state][curr_state].min_count = new_count;
                    dp_curr[last_state][curr_state].total_ways = best_prev.total_ways;
                } else if (new_count == dp_curr[last_state][curr_state].min_count) {
                    dp_curr[last_state][curr_state].total_ways = add(dp_curr[last_state][curr_state].total_ways, best_prev.total_ways);
                }
            }
        }
        
        // 交换指针，避免拷贝开销
        dp_prev.swap(dp_curr);
    }
    
    // 统计最终结果
    int min_total = INT_MAX;
    vector<int> total_methods = {0};
    
    for (int last_state = 0; last_state < total_states; last_state++) {
        for (int curr_state = 0; curr_state < total_states; curr_state++) {
            if (dp_prev[last_state][curr_state].min_count == INT_MAX) continue;
            if (!checkLastRow(last_state, curr_state, cols)) continue;
            
            int current_count = dp_prev[last_state][curr_state].min_count;
            
            if (current_count < min_total) {
                min_total = current_count;
                total_methods = dp_prev[last_state][curr_state].total_ways;
            } else if (current_count == min_total) {
                total_methods = add(total_methods, dp_prev[last_state][curr_state].total_ways);
            }
        }
    }
    
    // 输出答案
    cout << min_total << endl;
    printBig(total_methods);
    
    return 0;
}
