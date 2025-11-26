#define K (0.01 * (14 + 21))
#include <iostream>

// double matrix[3][3] = {{2 + K, 0.25, 0.75}, {0.25, 1.5 + K, 0.45}, {0.75, 0.45, 3 + K}};
double matrix[3][3] = {{10, 2, 1}, {2, 12, 2}, {1, 2, 15}};
double matrixB[3] = {3 + K, 2.2 + K, 4.2 + K};
const double oneMatrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

using namespace std;

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
}

int main() {
    setlocale(LC_ALL, "Russian");

    solve_danilevski();

    return 0;
}