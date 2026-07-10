#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

vector<double> read_line()
{
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<double> v;
    double num;
    while (iss >> num)
        v.push_back(num);
    return v;
}

vector<double> gauss(vector<vector<double>> A, vector<double> b, int n)
{
    for (int k = 0; k < n; ++k)
    {
        int pivot = k;
        for (int i = k + 1; i < n; ++i)
            if (fabs(A[i][k]) > fabs(A[pivot][k]))
                pivot = i;
        swap(A[k], A[pivot]);
        swap(b[k], b[pivot]);

        for (int i = k + 1; i < n; ++i)
        {
            double f = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j)
                A[i][j] -= f * A[k][j];
            b[i] -= f * b[k];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double s = b[i];
        for (int j = i + 1; j < n; ++j)
            s -= A[i][j] * x[j];
        x[i] = s / A[i][i];
    }
    return x;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(5);

    vector<double> xi = read_line();
    vector<double> yi = read_line();
    int n;
    cin >> n;

    int m = xi.size();
    int ord = n + 1;
    vector<double> sum_x(2 * n + 1, 0.0);

    for (int k = 0; k <= 2 * n; ++k)
        for (int i = 0; i < m; ++i)
            sum_x[k] += pow(xi[i], k);

    vector<vector<double>> A(ord, vector<double>(ord));
    for (int i = 0; i < ord; ++i)
        for (int j = 0; j < ord; ++j)
            A[i][j] = sum_x[i + j];

    vector<double> b(ord, 0.0);
    for (int i = 0; i < ord; ++i)
        for (int j = 0; j < m; ++j)
            b[i] += yi[j] * pow(xi[j], i);

    vector<double> coeff = gauss(A, b, ord);

    cout << "A:\n";
    for (int i = 0; i < ord; ++i)
    {
        for (int j = 0; j < ord; ++j)
        {
            if (j) cout << ' ';
            cout << A[i][j];
        }
        cout << '\n';
    }

    cout << "b:\n";
    for (int i = 0; i < ord; ++i)
        cout << b[i] << '\n';

    cout << "x:\n";
    for (int i = 0; i < ord; ++i)
        cout << coeff[i] << '\n';

    return 0;
}