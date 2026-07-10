#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

typedef double real_type;
const real_type PRECISION_EPS = 1e-12;

std::vector<real_type> fetch_input_data() {
    std::vector<real_type> input_buffer;
    real_type num;
    while (std::cin >> num) {
        input_buffer.push_back(num);
    }
    return input_buffer;
}

int get_matrix_dimension(const std::vector<real_type>& input) {
    int total_elements = input.size();
    real_type discriminant = 1 + 4.0 * total_elements;
    real_type sqrt_disc = sqrt(discriminant);
    int dim = static_cast<int>((sqrt_disc - 1) / 2.0);
    
    if (dim * dim + dim != total_elements) {
        std::cerr << "输入格式错误：元素总数不匹配n阶线性方程组要求" << std::endl;
        exit(EXIT_FAILURE);
    }
    return dim;
}

std::vector<std::vector<real_type>> build_augmented_matrix(
    const std::vector<real_type>& input, 
    int dim
) {
    std::vector<std::vector<real_type>> aug_mat(dim, std::vector<real_type>(dim + 1));
    int data_ptr = 0;
    for (int row = 0; row < dim; ++row) {
        for (int col = 0; col < dim; ++col) {
            aug_mat[row][col] = input[data_ptr++];
        }
    }
    for (int row = 0; row < dim; ++row) {
        aug_mat[row][dim] = input[data_ptr++];
    }
    return aug_mat;
}

void column_pivot_gauss_eliminate(std::vector<std::vector<real_type>>& mat, int dim) {
    for (int cur_col = 0; cur_col < dim; ++cur_col) {
        int pivot_row_idx = cur_col;
        for (int row = cur_col; row < dim; ++row) {
            if (fabs(mat[row][cur_col]) > fabs(mat[pivot_row_idx][cur_col])) {
                pivot_row_idx = row;
            }
        }

        std::swap(mat[cur_col], mat[pivot_row_idx]);

        if (fabs(mat[cur_col][cur_col]) < PRECISION_EPS) {
            std::cerr << "求解失败：系数矩阵奇异，方程组无唯一解" << std::endl;
            exit(EXIT_FAILURE);
        }

        for (int row = cur_col + 1; row < dim; ++row) {
            real_type eliminate_ratio = mat[row][cur_col] / mat[cur_col][cur_col];
            for (int col = cur_col; col <= dim; ++col) {
                mat[row][col] -= eliminate_ratio * mat[cur_col][col];
            }
        }
    }
}

std::vector<real_type> back_substitution_solve(const std::vector<std::vector<real_type>>& mat, int dim) {
    std::vector<real_type> solution(dim);
    for (int i = dim - 1; i >= 0; --i) {
        real_type sum_val = 0.0;
        for (int j = i + 1; j < dim; ++j) {
            sum_val += mat[i][j] * solution[j];
        }
        solution[i] = (mat[i][dim] - sum_val) / mat[i][i];
        if (fabs(solution[i]) < PRECISION_EPS) {
            solution[i] = 0.0;
        }
    }
    return solution;
}

void format_print_result(const std::vector<real_type>& sol) {
    std::cout << std::fixed << std::setprecision(5);
    for (real_type val : sol) {
        std::cout << val << std::endl;
    }
}

int main() {
    std::vector<real_type> raw_input = fetch_input_data();
    int matrix_dim = get_matrix_dimension(raw_input);
    std::vector<std::vector<real_type>> aug_matrix = build_augmented_matrix(raw_input, matrix_dim);
    column_pivot_gauss_eliminate(aug_matrix, matrix_dim);
    std::vector<real_type> final_solution = back_substitution_solve(aug_matrix, matrix_dim);
    format_print_result(final_solution);
    return 0;
}