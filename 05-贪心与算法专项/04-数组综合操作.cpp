#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// =========================================================================
// 【第一部分：手动填写可变位】 —— 数学公式定义区
// 说明：当题目给出的方程改变时，你只需要修改这里的 return 语句，算法部分无需变动。
// =========================================================================

// 1. 原函数 f(x)
// 对应题目：二分法求根、牛顿法求根、计算 f(x) 的输出值
double f(double x) {
    // [填写指导] 将方程化为 f(x) = 0 的形式。
    // [示例] 题目要求求 e^x + 10x - 2 = 0
    return exp(x) + 10.0 * x - 2.0; 
}

// 2. 原函数的导数 f'(x)
// 对应题目：牛顿法求近似根 (牛顿法公式需要用到一阶导数)
double df(double x) {
    // [填写指导] 手动对 f(x) 求导后写在这里。
    // [示例] f(x) = e^x + 10x - 2，求导得 f'(x) = e^x + 10
    return exp(x) + 10.0;
}

// 3. 迭代函数 g(x)
// 对应题目：迭代法求近似根、艾特肯法求解方程的根
double g(double x) {
    // [填写指导] 题目会给出 x_{k+1} = g(x_k) 的形式，将等号右边的式子填入。
    // [示例 1] 题目：迭代过程 x_{k+1} = (2 - e^{x_k}) / 10
    return (2.0 - exp(x)) / 10.0;
    
    // [示例 2] 题目：艾特肯法，迭代公式 x = ax^3 + b (若a=1, b=-1)
    // return 1.0 * pow(x, 3) - 1.0; 
}

// 4. 极值优化函数 f_opt(x) 及其一阶、二阶导数
// 对应题目：求非线性方程极值 (已知 f(x) = a*x^2 - b*sin(x))
// 注意：这里的 a 和 b 可以作为全局变量或参数传入
double a_opt = 2.0, b_opt = 1.0; // [根据输入修改]
double f_opt(double x) { return a_opt * x * x - b_opt * sin(x); }
double df_opt(double x) { return 2.0 * a_opt * x - b_opt * cos(x); } // 一阶导
double ddf_opt(double x) { return 2.0 * a_opt + b_opt * sin(x); }    // 二阶导


// =========================================================================
// 【第二部分：算法核心库】 —— 对应各类解法，直接调用即可
// =========================================================================

// 算法 1：简单迭代法求近似根
// eps: 容差限制
void FixedPointIteration(double x0, double eps) {
    double x_k = x0;
    double x_next;
    while (true) {
        x_next = g(x_k);
        // 如果题目要求根据误差停止 (题目示例为固定次数或精度)
        if (abs(x_next - x_k) <= eps) break; 
        x_k = x_next;
    }
    cout << fixed << setprecision(5) << x_next << ", " 
         << setprecision(9) << f(x_next) << endl;
}

// 算法 2：二分法求近似根
void BisectionMethod(double left, double right, double eps) {
    double mid;
    // 题目要求区间长度小于特定值时停止
    while ((right - left) >= eps) {
        mid = (left + right) / 2.0;
        if (f(mid) == 0.0) break;
        if (f(left) * f(mid) < 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    mid = (left + right) / 2.0;
    cout << fixed << setprecision(5) << mid << ", " 
         << setprecision(9) << f(mid) << endl;
}

// 算法 3：牛顿法求近似根
void NewtonMethod(double x0, double eps) {
    double x_k = x0;
    double x_next;
    while (true) {
        x_next = x_k - f(x_k) / df(x_k);
        if (abs(x_next - x_k) <= eps) break;
        x_k = x_next;
    }
    cout << fixed << setprecision(8) << x_next << endl;
}

// 算法 4：求函数极值 (利用牛顿法求一阶导数的根 df(x) = 0)
void FindExtremum(double x0, double eps) {
    double x_k = x0;
    double x_next;
    while (true) {
        // 求极值即求 df_opt(x) = 0 的根，迭代公式为 x - f'(x)/f''(x)
        x_next = x_k - df_opt(x_k) / ddf_opt(x_k);
        if (abs(x_next - x_k) <= eps) break;
        x_k = x_next;
    }
    cout << fixed << setprecision(5) << x_next << " " << f_opt(x_next) << endl;
}

// 算法 5：艾特肯 (Aitken) 加速法
void AitkenMethod(double x0, double eps) {
    double x_k = x0;
    double y_k, z_k, x_next;
    while (true) {
        y_k = g(x_k);
        z_k = g(y_k);
        // Aitken 加速公式
        x_next = x_k - pow(y_k - x_k, 2) / (z_k - 2 * y_k + x_k);
        if (abs(x_next - x_k) < eps) {
            // 根据题目输出格式要求
            cout << fixed << setprecision(6) << y_k << ", " << z_k << ", " << x_next << endl;
            break;
        }
        x_k = x_next;
    }
}

// 算法 6：拉格朗日插值多项式求值
double LagrangeInterpolation(const vector<double>& x_nodes, const vector<double>& y_nodes, double target_x) {
    double result = 0.0;
    int n = x_nodes.size();
    for (int i = 0; i < n; i++) {
        double term = y_nodes[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term = term * (target_x - x_nodes[j]) / (x_nodes[i] - x_nodes[j]);
            }
        }
        result += term;
    }
    return result;
}

// =========================================================================
// 【第三部分：主函数调用测试】
// =========================================================================
int main() {
    // 示例调用：你可以根据题目输入形式，用 cin 读取参数，然后调用对应的函数
    
    /* ---- 测试：迭代法求近似根 ---- */
    // cin >> x0;
    // FixedPointIteration(0.0, 0.5e-3); 

    /* ---- 测试：二分法求近似根 ---- */
    // BisectionMethod(0.0, 1.0, 0.5e-3);

    /* ---- 测试：牛顿法求近似根 ---- */
    // NewtonMethod(0.0, 0.5e-5);

    /* ---- 测试：极值点计算 ---- */
    // FindExtremum(1.0, 1e-4);

    return 0;
}