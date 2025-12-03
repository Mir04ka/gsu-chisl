#define K (0.01 * (14 + 21))
#define EPSILON 0.001
#include <cmath>
#include <iostream>

double matrix[3][3] = {{2 + K, 0.25, 0.75}, {0.25, 1.5 + K, 0.45}, {0.75, 0.45, 3 + K}};
// double matrix[3][3] = {{10, 2, 1}, {2, 12, 2}, {1, 2, 15}};
double matrixB[3] = {3 + K, 2.2 + K, 4.2 + K};
const double oneMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
double F_odds[4];

using namespace std;

double f(double x) {
    return F_odds[0] * x * x * x +
           F_odds[1] * x * x +
           F_odds[2] * x +
           F_odds[3];
}

double f1(double x) {
    return 3 * F_odds[0] * x * x +
           2 * F_odds[1] * x +
           F_odds[2];
}

double f2(double x) {
    return 6 * F_odds[0] * x +
           2 * F_odds[1];
}

void solve_vector(double A[3][3], double lambda, double out[3]) {
    double M[3][3];

    // (A - λI)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            M[i][j] = A[i][j] - (i == j ? lambda : 0);

    double a1 = M[0][0], b1 = M[0][1], c1 = M[0][2];
    double a2 = M[1][0], b2 = M[1][1], c2 = M[1][2];

    double det = a1*b2 - a2*b1;

    double x1, x2, x3 = 1;

    if (fabs(det) < 1e-12) {
        x2 = 1;
        x1 = (-c1 - b1*x2) / a1;
    } else {
        x1 = (-c1*b2 + c2*b1) / det;
        x2 = (-a1*c2 + a2*c1) / det;
    }

    double norm = sqrt(x1*x1 + x2*x2 + x3*x3);
    out[0] = x1 / norm;
    out[1] = x2 / norm;
    out[2] = x3 / norm;
}

void check_eigen(double A[3][3], double lambda, double v[3]) {
    double y[3] = {0};

    // y = A * v
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            y[i] += A[i][j] * v[j];

    cout << "\nПроверка для λ = " << lambda << ":\n";
    for (int i = 0; i < 3; i++) {
        double lv = lambda * v[i];
        double err = fabs(y[i] - lv);
        cout << "A*v[" << i << "] = " << y[i]
             << "    λ*v[" << i << "] = " << lv
             << "    |Δ| = " << err
             << (err < 0.02 ? "   OK" : "   FAIL") << "\n";
    }
}


double solve_newton(double from, double to, bool* solved) {
    *solved = true;
    double init_pribl;
    if (f(from) * f2(from) > 0) {
        init_pribl = from;
    }
    else if (f(to) * f2(to) > 0) {
        init_pribl = to;
    }
    else {
        *solved = false;
        return 0;
    }

    double current_x = init_pribl - f(init_pribl) / f1(init_pribl);
    double prev_x = init_pribl;
    for (int i = 1; i < 100; i++) {
        double eps = current_x - prev_x;
        if (eps < EPSILON) {
            *solved = f(current_x) < EPSILON;

            cout << "Найдено решение с точностью " << EPSILON << endl;

            if (*solved) {
                return current_x;
            }

            return 0;
        }

        prev_x = current_x;
        current_x = prev_x - f(prev_x) / f1(prev_x);
    }

    std::cout << "Достигнуто максимальное количество итераций! Ответ не найден";
    return 0;
}

void print_matrix(const std::string& label = "") {
    std::cout << "\n";
    if (!label.empty()) {
        std::cout << label << "\n";
    }
    for (auto & i : matrix) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }
}

void solve_danilevski() {
    double M2[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    M2[1][0] = - matrix[2][0]/matrix[2][1];
    M2[1][1] = 1/matrix[2][1];
    M2[1][2] = -matrix[2][2]/matrix[2][1];

    cout << "M2:\n";
    for (auto & i : M2) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double M2_inv[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    M2_inv[1][0] =  matrix[2][0];
    M2_inv[1][1] =  matrix[2][1];
    M2_inv[1][2] =  matrix[2][2];

    double temp[3][3] = {0};
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
                temp[i][j] += matrix[i][k] * M2[k][j];

    double C[3][3] = {0};
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
                C[i][j] += M2_inv[i][k] * temp[k][j];

    cout << "C:\n";
    for (auto & i : C) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double M1[3][3] = {0};
    M1[0][0] = 1/C[1][0];
    M1[0][1] = -C[1][1]/C[1][0];
    M1[0][2] = -C[1][2]/C[1][0];
    M1[1][1] = 1;
    M1[2][2] = 1;

    cout << "M1:\n";
    for (auto & i : M1) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double D[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                D[i][j] += C[i][k] * M1[k][j];
            }
        }
    }

    cout << "D:\n";
    for (auto & i : D) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double M1_inv[3][3] = {{C[1][0], C[1][1], C[1][2]},
                           {0, 1, 0},
                           {0, 0, 1}};

    double F[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                F[i][j] += M1_inv[i][k] * D[k][j];
            }
        }
    }

    cout << "F:\n";
    for (auto & i : F) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    cout << "\nХарактеристический полином:\n";
    cout << "λ³ + (" << -F[0][0] << ")λ² + (" << -F[0][1] << ")λ + (" << -F[0][2] << ") = 0\n";

    F_odds[0] = 1;
    F_odds[1] = -F[0][0];
    F_odds[2] = -F[0][1];
    F_odds[3] = -F[0][2];

    bool solved;
    double l1 = solve_newton(1.7, 1.8, &solved);
    if (!solved) {
        cout << "Can't find this root\n";
    }
    cout << "l1 = " << l1 << "\n";

    double l2 = solve_newton(1.9, 2.0, &solved);
    if (!solved) {
        cout << "Can't find this root\n";
    }
    cout << "l2 = " << l2 << "\n";

    double l3 = solve_newton(3.88, 3.89, &solved);
    if (!solved) {
        cout << "Can't find this root\n";
    }
    cout << "l3 = " << l3 << "\n";

    double A_orig[3][3];
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            A_orig[i][j] = matrix[i][j];

    double v1[3], v2[3], v3[3];

    solve_vector(A_orig, l1, v1);
    solve_vector(A_orig, l2, v2);
    solve_vector(A_orig, l3, v3);

    cout << "\nСобственные векторы:\n";
    cout << "v1 = (" << v1[0] << ", " << v1[1] << ", " << v1[2] << ")\n";
    cout << "v2 = (" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")\n";
    cout << "v3 = (" << v3[0] << ", " << v3[1] << ", " << v3[2] << ")\n";

    cout << "\nПроверка AX = λX\n";
    check_eigen(A_orig, l1, v1);
    check_eigen(A_orig, l2, v2);
    check_eigen(A_orig, l3, v3);
}

int main() {
    setlocale(LC_ALL, "Russian");

    solve_danilevski();

    return 0;
}