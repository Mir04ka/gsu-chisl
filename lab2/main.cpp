#define K (0.01 * (14 + 21))
#define EPSILON 0.000001
#include <iostream>
#include <string>
#include <cmath>

int a, b;
double matrix[3][4] = {{2 + K, 0.25, 0.75, 3 + K}, {0.25, 1.5 + K, 0.45, 2.2 + K}, {0.75, 0.45, 3 + K, 4.2 + K}};
double init_matrix[3][4];

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

void solve_gauss() {
    // Проверка, что элемент 1 1 не равен нулю
    if (matrix[0][0] == 0) {
        std::cout << "a11 is zero!";
        return;
    }

    // Делим все элементы первой строки на первый элемент
    for (int i = 3; i >= 0; i--) {
        matrix[0][i] = matrix[0][i] / matrix[0][0];
    }
    print_matrix();

    // Прибавляем к строкам 2 и 3 первой строки, умноженной на первый элемент строки с минусом
    for (int i = 1; i < 3; i++) {
        double kf = -matrix[i][0];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = matrix[i][j] + matrix[0][j] * kf;
        }
    }
    print_matrix();

    // Проверка, что элемент 2 2 не равен нулю
    if (matrix[1][1] == 0) {
        std::cout << "a22 is zero!";
        return;
    }

    // Делим все элементы второй строки на элемент 2 2
    double temp = matrix[1][1];
    for (int i = 3; i >= 0; i--) {
        matrix[1][i] = matrix[1][i] / temp;
    }
    print_matrix();

    // Прибавляем к 3 строке вторую, умноженную на второй элемент строки с минусом
    double kf = -matrix[2][1];
    for (int j = 0; j < 4; j++) {
        matrix[2][j] = matrix[2][j] + matrix[1][j] * kf;
    }
    print_matrix();

    // Проверка, что элемент 3 3 не равен нулю
    if (matrix[2][2] == 0) {
        std::cout << "a33 is zero!";
        return;
    }

    // Делим все элементы второй строки на элемент 2 2
    temp = matrix[2][2];
    for (int i = 3; i >= 0; i--) {
        matrix[2][i] = matrix[2][i] / temp;
    }
    print_matrix();

    // Вычисляем неизвестные
    double x3 = matrix[2][3];
    double x2 = matrix[1][3] - matrix[1][2] * x3;
    double x1 = matrix[0][3] - matrix[0][2] * x3 - matrix[0][1] * x2;

    std::cout << "\n";
    printf("x1 = %.6lf \n", x1);
    printf("x2 = %.6lf \n", x2);
    printf("x3 = %.6lf \n", x3);

    // Проверка
    for (auto & i : init_matrix) {
        double res = i[0] * x1 + i[1] * x2 + i[2] * x3;
        std::cout << "\n";
        printf("Expected: %.6lf Result: %.6lf Status: %s", i[3], res, fabs(res - i[3]) < EPSILON ? "OK" : "WRONG");
    }
}

int main() {
    std::copy(&matrix[0][0], &matrix[0][0]+3*4,&init_matrix[0][0]);
    print_matrix("Initial matrix");

    solve_gauss();

    return 0;
}