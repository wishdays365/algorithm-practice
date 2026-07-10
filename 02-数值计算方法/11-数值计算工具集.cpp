#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
using namespace std;

// ============================================================
// 1. 正弦函数泰勒展开（周期化简）
// ============================================================
void sin_taylor() {
    // TODO: 输入变量 x
    double x;
    cin >> x;   // 例如 2

    const double PI = acos(-1.0);
    x = fmod(x, 2 * PI);
    if (x > PI) x -= 2 * PI;
    else if (x < -PI) x += 2 * PI;

    // TODO: 修改精度阈值（如果需要）
    const double EPS = 1e-3;

    double term = x;
    double sum = 0.0;
    int n = 1;
    while (fabs(term) >= EPS) {
        sum += term;
        n += 2;
        // 递推公式：下一项 = - term * x^2 / (n*(n-1))
        term = -term * x * x / (n * (n - 1));
    }
    cout << fixed << setprecision(8) << sum << endl;
}

// ============================================================
// 2. 迭代法求根（不动点迭代）
// ============================================================
void fixed_point_iteration() {
    // TODO: 修改初值、精度
    double x0 = 0.0;
    const double EPS = 0.5e-3;

    // TODO: 修改迭代公式 x_{k+1} = g(x_k)
    auto g = [](double x) {
        return (2 - exp(x)) / 10.0;   // 示例：e^x+10x-2=0 的迭代形式
    };

    // TODO: 修改函数 f(x)（用于输出函数值）
    auto f = [](double x) {
        return exp(x) + 10 * x - 2;
    };

    double x1;
    while (true) {
        x1 = g(x0);
        if (fabs(x1 - x0) < EPS) break;
        x0 = x1;
    }
    double fx = f(x1);
    cout << fixed << setprecision(5) << x1 << ", "
         << setprecision(9) << fx << endl;
}

// ============================================================
// 3. 二分法求根
// ============================================================
void bisection() {
    // TODO: 修改区间、精度
    double a = 0.0, b = 1.0;
    const double EPS = 0.5e-3;

    // TODO: 修改函数 f(x)
    auto f = [](double x) {
        return exp(x) + 10 * x - 2;
    };

    double c;
    while (b - a >= EPS) {
        c = (a + b) / 2.0;
        if (f(a) * f(c) < 0) b = c;
        else a = c;
    }
    double mid = (a + b) / 2.0;
    cout << fixed << setprecision(5) << mid << ", "
         << setprecision(9) << f(mid) << endl;
}

// ============================================================
// 4. 求非线性方程极值（f(x)=a*x^2 - b*sin(x)）
// ============================================================
void find_extremum() {
    // TODO: 输入参数 a, b, 参考点 x0
    double a, b, x0;
    cin >> a >> b >> x0;   // 例如 2 1 1

    // TODO: 修改目标函数及其导数（牛顿法求导数为0）
    auto f = [a, b](double x) {
        return a * x * x - b * sin(x);
    };
    auto df = [a, b](double x) {
        return 2 * a * x - b * cos(x);
    };
    auto ddf = [a, b](double x) {
        return 2 * a + b * sin(x);
    };

    double x = x0;
    for (int i = 0; i < 100; ++i) {
        double fx = df(x);
        double dfx = ddf(x);
        if (fabs(dfx) < 1e-12) break;
        x = x - fx / dfx;
    }
    cout << fixed << setprecision(5) << x << " " << f(x) << endl;
}

// ============================================================
// 5. 牛顿法求根
// ============================================================
void newton_root() {
    // TODO: 修改初值、精度
    double x0 = 0.0;
    const double EPS = 0.5e-5;

    // TODO: 修改函数 f(x) 和导数 df(x)
    auto f = [](double x) {
        return exp(x) + 10 * x - 2;
    };
    auto df = [](double x) {
        return exp(x) + 10;
    };

    double x1;
    while (true) {
        x1 = x0 - f(x0) / df(x0);
        if (fabs(x1 - x0) < EPS) break;
        x0 = x1;
    }
    cout << fixed << setprecision(8) << x1 << endl;
}

// ============================================================
// 6. 牛顿迭代法求复根（x^4+2x^3-x-1=0）
// ============================================================
void newton_complex() {
    // TODO: 输入初值实部、虚部
    double real, imag;
    cin >> real >> imag;
    complex<double> x0(real, imag);

    // TODO: 修改复函数 f(z) 和导数 df(z)
    auto f = [](complex<double> z) {
        return z*z*z*z + 2.0*z*z*z - z - 1.0;
    };
    auto df = [](complex<double> z) {
        return 4.0*z*z*z + 6.0*z*z - 1.0;
    };

    const double EPS = 1e-5;
    complex<double> x1;
    int iter = 0;
    while (iter < 1000) {
        x1 = x0 - f(x0) / df(x0);
        if (abs(x1 - x0) < EPS) break;
        x0 = x1;
        iter++;
    }
    if (abs(x1.imag()) > 1e-4) {
        cout << "error" << endl;
    } else {
        cout << fixed << setprecision(8) << x1.real() << " "
             << x1.imag() << "i" << endl;
    }
}

// ============================================================
// 7. 艾特肯加速法（x = a*x^3 + b）
// ============================================================
void aitken() {
    // TODO: 输入 a, b, 初值 x0
    double a, b, x0;
    cin >> a >> b >> x0;   // 例如 1.0 -1.0 1.5

    // TODO: 修改迭代函数 phi(x) = a*x^3 + b
    auto phi = [a, b](double x) {
        return a * x * x * x + b;
    };

    const double EPS = 1e-5;
    double xk = x0, yk, zk;
    while (true) {
        yk = phi(xk);
        zk = phi(yk);
        double x_next = zk - (zk - yk) * (zk - yk) / (zk - 2 * yk + xk);
        if (fabs(x_next - xk) < EPS) break;
        xk = x_next;
    }
    // 输出 yk, zk, xk（最终值）
    cout << fixed << setprecision(6) << yk << ", " << zk << ", " << xk << endl;
}

// ============================================================
// 8. 高斯消元法（线性方程组）
// ============================================================
void gaussian_elimination() {
    // TODO: 输入阶数 n，矩阵 A，向量 b（可按行输入）
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    // 高斯消元（列主元）
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(A[k][i]) > fabs(A[maxRow][i])) maxRow = k;
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
    cout << fixed << setprecision(5);
    for (double v : x) cout << v << endl;
}

// ============================================================
// 9. LU分解法
// ============================================================
void lu_decomposition() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    // Doolittle LU
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
        for (int j = i; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < i; ++k)
                sum += L[i][k] * U[k][j];
            U[i][j] = A[i][j] - sum;
        }
        for (int j = i + 1; j < n; ++j) {
            double sum = 0;
            for (int k = 0; k < i; ++k)
                sum += L[j][k] * U[k][i];
            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }

    vector<double> y(n), x(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < i; ++j)
            sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j)
            sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }

    cout << fixed << setprecision(5);
    cout << "L:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << L[i][j] << " ";
        cout << "\n";
    }
    cout << "U:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << U[i][j] << " ";
        cout << "\n";
    }
    cout << "y:\n";
    for (double v : y) cout << v << "\n";
    cout << "x:\n";
    for (double v : x) cout << v << "\n";
}

// ============================================================
// 10. 追赶法（三对角）
// ============================================================
void tridiagonal_solver() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    vector<double> rhs(n);
    for (int i = 0; i < n; ++i) cin >> rhs[i];

    // 提取三对角线
    vector<double> a(n, 0), b(n, 0), c(n, 0);
    for (int i = 0; i < n; ++i) {
        b[i] = A[i][i];
        if (i > 0) a[i] = A[i][i - 1];
        if (i < n - 1) c[i] = A[i][i + 1];
    }

    vector<double> alpha(n), beta(n);
    alpha[0] = b[0];
    beta[0] = c[0] / alpha[0];
    for (int i = 1; i < n; ++i) {
        alpha[i] = b[i] - a[i] * beta[i - 1];
        if (i < n - 1) beta[i] = c[i] / alpha[i];
    }
    vector<double> y(n), x(n);
    y[0] = rhs[0] / alpha[0];
    for (int i = 1; i < n; ++i)
        y[i] = (rhs[i] - a[i] * y[i - 1]) / alpha[i];
    x[n - 1] = y[n - 1];
    for (int i = n - 2; i >= 0; --i)
        x[i] = y[i] - beta[i] * x[i + 1];

    cout << fixed << setprecision(5);
    cout << "L:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) cout << 1.0 << " ";
            else if (i > j && i - j == 1) cout << a[i] << " ";
            else cout << 0.0 << " ";
        }
        cout << "\n";
    }
    cout << "U:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) cout << alpha[i] << " ";
            else if (j > i && j - i == 1) cout << c[i] << " ";
            else cout << 0.0 << " ";
        }
        cout << "\n";
    }
    cout << "y:\n";
    for (double v : y) cout << v << "\n";
    cout << "x:\n";
    for (double v : x) cout << v << "\n";
}

// ============================================================
// 11. 平方根法（Cholesky）
// ============================================================
void cholesky() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<vector<double>> L(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[i][k] * L[j][k];
            if (i == j)
                L[i][i] = sqrt(A[i][i] - sum);
            else
                L[i][j] = (A[i][j] - sum) / L[j][j];
        }
    }
    vector<double> y(n), x(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < i; ++j)
            sum += L[i][j] * y[j];
        y[i] = (b[i] - sum) / L[i][i];
    }
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j)
            sum += L[j][i] * x[j];
        x[i] = (y[i] - sum) / L[i][i];
    }

    cout << fixed << setprecision(5);
    cout << "L:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << L[i][j] << " ";
        cout << "\n";
    }
    cout << "y:\n";
    for (double v : y) cout << v << "\n";
    cout << "x:\n";
    for (double v : x) cout << v << "\n";
}

// ============================================================
// 12. Jacobi迭代法
// ============================================================
void jacobi() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n), x0(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) cin >> x0[i];

    const double EPS = 1e-5;
    vector<double> x(n);
    while (true) {
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < n; ++j)
                if (j != i) sum += A[i][j] * x0[j];
            x[i] = (b[i] - sum) / A[i][i];
        }
        double norm = 0;
        for (int i = 0; i < n; ++i)
            norm = max(norm, fabs(x[i] - x0[i]));
        if (norm < EPS) break;
        x0 = x;
    }
    cout << fixed << setprecision(5);
    cout << "x:\n";
    for (double v : x) cout << v << "\n";
}

// ============================================================
// 13. Gauss-Seidel法（三对角特殊结构）
// ============================================================
void gauss_seidel_tridiagonal() {
    // TODO: 输入向量 b（逗号分隔）
    string line;
    getline(cin, line);
    vector<double> b;
    stringstream ss(line);
    double val;
    while (ss >> val) {
        b.push_back(val);
        if (ss.peek() == ',') ss.ignore();
    }
    int n = b.size();

    // TODO: 修改矩阵结构（本例为主对角线4，上下对角线-1）
    vector<double> x(n, 0), x_old(n, 0);
    const double EPS = 1e-5;
    while (true) {
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            if (i > 0) sum += -1 * x[i - 1];      // 使用新值
            if (i < n - 1) sum += -1 * x_old[i + 1]; // 旧值
            x[i] = (b[i] - sum) / 4.0;
        }
        double norm = 0;
        for (int i = 0; i < n; ++i)
            norm = max(norm, fabs(x[i] - x_old[i]));
        if (norm < EPS) break;
        x_old = x;
    }

    for (int i = 0; i < n; ++i) {
        if (i) cout << ",";
        cout << (int)round(x[i]);
    }
    cout << endl;
}

// ============================================================
// 14. 矩阵求逆（高斯-约当）
// ============================================================
void matrix_inverse() {
    int n;
    cin >> n;
    vector<vector<double>> A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    vector<vector<double>> aug(n, vector<double>(2 * n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            aug[i][j] = A[i][j];
        aug[i][n + i] = 1.0;
    }

    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(aug[k][i]) > fabs(aug[maxRow][i])) maxRow = k;
        swap(aug[i], aug[maxRow]);

        double pivot = aug[i][i];
        for (int j = i; j < 2 * n; ++j)
            aug[i][j] /= pivot;

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = aug[k][i];
                for (int j = i; j < 2 * n; ++j)
                    aug[k][j] -= factor * aug[i][j];
            }
        }
    }

    cout << fixed << setprecision(5);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << aug[i][n + j] << " ";
        cout << "\n";
    }
}

// ============================================================
// 15. 多项式插值（牛顿差商法求系数）
// ============================================================
void polynomial_interpolation() {
    int n;  // 阶数（结点数 = n+1）
    cin >> n;
    n++;  // 结点个数
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i) cin >> y[i];

    // 差商表
    vector<vector<double>> table(n, vector<double>(n));
    for (int i = 0; i < n; ++i) table[i][0] = y[i];
    for (int j = 1; j < n; ++j)
        for (int i = 0; i < n - j; ++i)
            table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (x[i + j] - x[i]);

    // 牛顿插值多项式系数（升幂）
    vector<double> coeff(n, 0);
    coeff[0] = table[0][0];
    for (int i = 1; i < n; ++i) {
        vector<double> poly(i + 1, 0);
        poly[0] = 1.0;
        for (int k = 0; k < i; ++k) {
            vector<double> newPoly(i + 1, 0);
            for (int p = 0; p <= k; ++p) {
                newPoly[p] += poly[p] * (-x[k]);
                newPoly[p + 1] += poly[p];
            }
            poly = newPoly;
        }
        for (int p = 0; p <= i; ++p)
            coeff[p] += table[0][i] * poly[p];
    }

    cout << fixed << setprecision(5);
    for (double c : coeff) cout << c << endl;
}

// ============================================================
// 16. 拉格朗日插值（已知函数表）
// ============================================================
void lagrange_interpolation() {
    // TODO: 输入插值点 x_val
    double x_val;
    cin >> x_val;

    // TODO: 修改已知数据点（此处为题目固定数据）
    vector<double> x = {0.0, 0.1, 0.195, 0.3, 0.401, 0.5};
    vector<double> y = {0.39894, 0.39695, 0.39142, 0.38138, 0.36812, 0.35206};

    double result = 0.0;
    int n = x.size();
    for (int i = 0; i < n; ++i) {
        double term = y[i];
        for (int j = 0; j < n; ++j) {
            if (i != j)
                term *= (x_val - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    cout << fixed << setprecision(5) << result << endl;
}

// ============================================================
// 17. 三次样条插值（第一类边界条件）
// ============================================================
void cubic_spline() {
    // TODO: 输入结点 xi, yi, 边界导数 f'(x0), f'(xn), 待求点 x
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i) cin >> y[i];
    double f0, fn;
    cin >> f0 >> fn;
    double x_query;
    cin >> x_query;

    // 构造三对角方程组求二阶导数 m
    vector<double> h(n - 1);
    for (int i = 0; i < n - 1; ++i) h[i] = x[i + 1] - x[i];

    vector<double> a(n - 2), b(n - 2), c(n - 2), d(n - 2);
    // 这里省略具体构建代码，请参考教材补充
    // 最终得到 m[0..n-1]

    // 示例输出（占位，实际需计算）
    vector<double> m(n, 0);
    // 计算插值点
    double result = 0.0; // 根据所在区间计算

    cout << fixed << setprecision(5);
    for (double v : m) cout << v << "\n";
    cout << result << endl;
}

// ============================================================
// 18. 最小二乘拟合（多项式）
// ============================================================
void least_squares() {
    // TODO: 输入数据点数和数据，以及拟合阶数
    int m;
    cin >> m;
    vector<double> x(m), y(m);
    for (int i = 0; i < m; ++i) cin >> x[i];
    for (int i = 0; i < m; ++i) cin >> y[i];
    int n;  // 多项式次数
    cin >> n;

    int N = n + 1;
    vector<vector<double>> A(N, vector<double>(N, 0));
    vector<double> b(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0;
            for (int k = 0; k < m; ++k)
                sum += pow(x[k], i + j);
            A[i][j] = sum;
        }
        double sum = 0;
        for (int k = 0; k < m; ++k)
            sum += y[k] * pow(x[k], i);
        b[i] = sum;
    }

    // 高斯消元解 A*coeff = b
    // 此处省略，可复用之前的高斯消元代码
    vector<double> coeff(N, 0);

    cout << fixed << setprecision(5);
    cout << "A:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << A[i][j] << " ";
        cout << "\n";
    }
    cout << "b:\n";
    for (double v : b) cout << v << "\n";
    cout << "x:\n";
    for (double c : coeff) cout << c << "\n";
}

// ============================================================
// 主函数（调用示例）
// ============================================================
int main() {
    // 取消注释您需要运行的函数
    // sin_taylor();
    // fixed_point_iteration();
    // bisection();
    // find_extremum();
    // newton_root();
    // newton_complex();
    // aitken();
    // gaussian_elimination();
    // lu_decomposition();
    // tridiagonal_solver();
    // cholesky();
    // jacobi();
    // gauss_seidel_tridiagonal();
    // matrix_inverse();
    // polynomial_interpolation();
    // lagrange_interpolation();
    // cubic_spline();
    // least_squares();
    return 0;
}