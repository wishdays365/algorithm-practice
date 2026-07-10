#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    vector<double> all_data;
    double num;
    while (cin >> num) {
        all_data.push_back(num);
    }

    int m = all_data.size();
    int n = (sqrt(1 + 4 * m) - 1) / 2;

    vector<double> A(all_data.begin(), all_data.begin() + n * n);
    vector<double> b(all_data.begin() + n * n, all_data.end());

    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
    }

    for (int k = 0; k < n; ++k) {
        for (int j = k; j < n; ++j) {
            double sum = 0.0;
            for (int s = 0; s < k; ++s) {
                sum += L[k][s] * U[s][j];
            }
            U[k][j] = A[k * n + j] - sum;
        }

        for (int i = k + 1; i < n; ++i) {
            double sum = 0.0;
            for (int s = 0; s < k; ++s) {
                sum += L[i][s] * U[s][k];
            }
            L[i][k] = (A[i * n + k] - sum) / U[k][k];
        }
    }

    vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int s = 0; s < i; ++s) {
            sum += L[i][s] * y[s];
        }
        y[i] = b[i] - sum;
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int s = i + 1; s < n; ++s) {
            sum += U[i][s] * x[s];
        }
        x[i] = (y[i] - sum) / U[i][i];
        if (fabs(x[i]) < 1e-12) {
            x[i] = 0.0;
        }
    }

    cout << fixed << setprecision(5);

    cout << "L:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << L[i][j];
            if (j != n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "U:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << U[i][j];
            if (j != n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    cout << "y:" << endl;
    for (double yi : y) {
        cout << yi << endl;
    }

    cout << "x:" << endl;
    for (double xi : x) {
        cout << xi << endl;
    }

    return 0;
}