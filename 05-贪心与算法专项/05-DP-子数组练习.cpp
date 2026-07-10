#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// =========================================================================
// 【第一部分：手动填写可变位】 —— 特殊矩阵与边界条件设定区
// =========================================================================

// 1. 大型稀疏矩阵的对角线参数设定 (用于 Gauss-Seidel 法)
// [填写指导] 题目描述“对角线元素为4，其余两条对角线元素为-1”
const double GS_MAIN_DIAG = 4.0;
const double GS_SUB_DIAG = -1.0;
const double GS_SUPER_DIAG = -1.0;

// =========================================================================
// 【第二部分：算法核心库】 —— 矩阵高级解法与高阶插值
// =========================================================================

/* ------------------ (一) 线性方程组：矩阵分解与迭代解法 ------------------ */

// 算法 7：LU 分解法求解 Ax = b
void LUDecomposition(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    
    // Doolittle 分解 (L对角线为1)
    for (int i = 0; i < n; i++) L[i][i] = 1.0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) { // 求 U
            double sum = 0.0;
            for (int k = 0; k < i; k++) sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }
        for (int j = i + 1; j < n; j++) { // 求 L
            double sum = 0.0;
            for (int k = 0; k < i; k++) sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
    
    // 解 Ly = b
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int k = 0; k < i; k++) sum += L[i][k] * y[k];
        y[i] = b[i] - sum;
    }
    
    // 解 Ux = y
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int k = i + 1; k < n; k++) sum += U[i][k] * x[k];
        x[i] = (y[i] - sum) / U[i][i];
    }
    
    // [格式输出指导] 根据题目需要逐个打印 L, U, y, x
    cout << "L:" << endl;
    for(int i=0; i<n; i++) { for(int j=0; j<n; j++) cout << fixed << setprecision(5) << L[i][j] << " "; cout << endl; }
    cout << "U:" << endl;
    for(int i=0; i<n; i++) { for(int j=0; j<n; j++) cout << fixed << setprecision(5) << U[i][j] << " "; cout << endl; }
    cout << "y:" << endl;
    for(int i=0; i<n; i++) cout << fixed << setprecision(5) << y[i] << endl;
    cout << "x:" << endl;
    for(int i=0; i<n; i++) cout << fixed << setprecision(5) << x[i] << endl;
}

// 算法 8：平方根法 (Cholesky分解) 求解 Ax = b
void CholeskyMethod(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    
    for (int j = 0; j < n; j++) {
        double sum1 = 0.0;
        for (int k = 0; k < j; k++) sum1 += L[j][k] * L[j][k];
        L[j][j] = sqrt(A[j][j] - sum1);
        
        for (int i = j + 1; i < n; i++) {
            double sum2 = 0.0;
            for (int k = 0; k < j; k++) sum2 += L[i][k] * L[j][k];
            L[i][j] = (A[i][j] - sum2) / L[j][j];
        }
    }
    
    // 解 Ly = b
    vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int k = 0; k < i; k++) sum += L[i][k] * y[k];
        y[i] = (b[i] - sum) / L[i][i];
    }
    
    // 解 L^T x = y
    vector<double> x(n, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int k = i + 1; k < n; k++) sum += L[k][i] * x[k];
        x[i] = (y[i] - sum) / L[i][i];
    }
    
    // 输出
    cout << "L:" << endl;
    for(int i=0; i<n; i++) { for(int j=0; j<n; j++) cout << fixed << setprecision(5) << L[i][j] << " "; cout << endl; }
    cout << "y:" << endl;
    for(int i=0; i<n; i++) cout << fixed << setprecision(5) << y[i] << endl;
    cout << "x:" << endl;
    for(int i=0; i<n; i++) cout << fixed << setprecision(5) << x[i] << endl;
}

// 算法 9：追赶法 (Thomas Algorithm) 求解三对角线性方程组
void ThomasAlgorithm(const vector<vector<double>>& A, const vector<double>& b) {
    int n = A.size();
    vector<double> sub(n, 0.0), main_diag(n, 0.0), super(n, 0.0);
    
    // 提取三对角线
    for(int i=0; i<n; i++) {
        main_diag[i] = A[i][i];
        if(i > 0) sub[i] = A[i][i-1];
        if(i < n-1) super[i] = A[i][i+1];
    }
    
    vector<double> c_star(n, 0.0), d_star(n, 0.0), x(n, 0.0);
    c_star[0] = super[0] / main_diag[0];
    d_star[0] = b[0] / main_diag[0];
    
    // 追的过程
    for (int i = 1; i < n; i++) {
        double m = main_diag[i] - sub[i] * c_star[i - 1];
        if (i < n - 1) c_star[i] = super[i] / m;
        d_star[i] = (b[i] - sub[i] * d_star[i - 1]) / m;
    }
    
    // 赶的过程
    x[n - 1] = d_star[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i + 1];
    }
    
    cout << "x:" << endl;
    for(int i=0; i<n; i++) cout << fixed << setprecision(5) << x[i] << endl;
}

// 算法 10：高斯消元法求矩阵逆
void MatrixInverse(vector<vector<double>> A) {
    int n = A.size();
    // 构造增广矩阵 [A | I]
    vector<vector<double>> aug(n, vector<double>(2 * n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug[i][j] = A[i][j];
        aug[i][i + n] = 1.0;
    }
    
    // Gauss-Jordan 消元
    for (int i = 0; i < n; i++) {
        double pivot = aug[i][i];
        for (int j = 0; j < 2 * n; j++) aug[i][j] /= pivot; // 归一化当前行
        
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = aug[k][i];
                for (int j = 0; j < 2 * n; j++) aug[k][j] -= factor * aug[i][j];
            }
        }
    }
    
    // 输出逆矩阵部分
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << fixed << setprecision(5) << aug[i][j + n] << " ";
        cout << endl;
    }
}


/* ------------------ (二) 复杂插值法 ------------------ */

// 算法 11：第一类边界条件的三次样条插值 (计算二阶导数值 M_i)
void CubicSpline(const vector<double>& x, const vector<double>& y, double dy0, double dyn, double target_x) {
    int n = x.size() - 1;
    vector<double> h(n), lambda(n), mu(n), d(n+1), M(n+1);
    
    for (int i = 0; i < n; i++) h[i] = x[i+1] - x[i];
    
    // 构造方程组参数
    for (int i = 1; i < n; i++) {
        lambda[i] = h[i] / (h[i-1] + h[i]);
        mu[i] = h[i-1] / (h[i-1] + h[i]);
        // 差商计算
        d[i] = 6.0 * ((y[i+1] - y[i])/h[i] - (y[i] - y[i-1])/h[i-1]) / (h[i-1] + h[i]);
    }
    
    // 边界条件处理 (第一类边界)
    lambda[0] = 1.0; 
    d[0] = 6.0 * ((y[1] - y[0])/h[0] - dy0) / h[0];
    mu[n] = 1.0; 
    d[n] = 6.0 * (dyn - (y[n] - y[n-1])/h[n-1]) / h[n-1];
    
    // 构造追赶法求解 M_i 的矩阵参数 (略去构建过程，直接追赶求解)
    vector<double> c_star(n+1, 0.0), d_star(n+1, 0.0);
    c_star[0] = lambda[0] / 2.0;
    d_star[0] = d[0] / 2.0;
    
    for (int i = 1; i <= n; i++) {
        double diag = 2.0;
        double sub = (i == n) ? mu[n] : mu[i];
        double super = (i == n) ? 0.0 : lambda[i];
        
        double m = diag - sub * c_star[i-1];
        if (i < n) c_star[i] = super / m;
        d_star[i] = (d[i] - sub * d_star[i-1]) / m;
    }
    
    M[n] = d_star[n];
    for (int i = n - 1; i >= 0; i--) M[i] = d_star[i] - c_star[i] * M[i+1];
    
    // 打印结点处的二阶导数值 M
    for (int i = 0; i <= n; i++) cout << fixed << setprecision(5) << M[i] << endl;
    
    // 计算插值点 target_x 所在区间并求值
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (target_x >= x[i] && target_x <= x[i+1]) { k = i; break; }
    }
    
    double val = M[k] * pow(x[k+1] - target_x, 3) / (6.0 * h[k]) +
                 M[k+1] * pow(target_x - x[k], 3) / (6.0 * h[k]) +
                 (y[k] - M[k]*h[k]*h[k]/6.0) * (x[k+1] - target_x) / h[k] +
                 (y[k+1] - M[k+1]*h[k]*h[k]/6.0) * (target_x - x[k]) / h[k];
                 
    cout << fixed << setprecision(5) << val << endl;
}

// =========================================================================
// 【第三部分：主函数调用测试】
// =========================================================================
int main() {
    // 示例：矩阵求逆调用
    // vector<vector<double>> A = {
    //     {2.0, 1.0, 5.0},
    //     {4.0, 1.0, 12.0},
    //     {-2.0, -4.0, 5.0}
    // };
    // MatrixInverse(A);
    
    return 0;
}