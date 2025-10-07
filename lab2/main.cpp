#define K (0.01 * (14 + 21))
#define EPSILON 0.000001
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>

double matrix[3][4] = {{2.04, 0.25, 0.75, 35.12}, {0.25, 1.54, 0.45, 22.04}, {0.75, 0.45, 3.04, 37.08}};
// double matrix[3][4] = {{2 + K, 0.25, 0.75, 3 + K}, {0.25, 1.5 + K, 0.45, 2.2 + K}, {0.75, 0.45, 3 + K, 4.2 + K}};
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

void solve_sqrt() {
    double temp_matrix[3][4] = {0};
    memset(matrix, 0, sizeof(matrix));

    matrix[0][3] = init_matrix[0][3];
    matrix[1][3] = init_matrix[1][3];
    matrix[2][3] = init_matrix[2][3];

    matrix[0][0] = sqrt(init_matrix[0][0]);
    matrix[0][1] = init_matrix[0][1] / matrix[0][0];
    matrix[0][2] = init_matrix[0][2] / matrix[0][0];

    matrix[1][1] = sqrt(init_matrix[1][1] - matrix[0][1] * matrix[0][1]);
    matrix[1][2] = (init_matrix[1][2] - matrix[0][1] * matrix[0][2]) / matrix[1][1];

    matrix[2][2] = sqrt(init_matrix[2][2] - matrix[0][2] * matrix[0][2] - matrix[1][2] * matrix[1][2]);

    print_matrix();

    temp_matrix[0][0] = matrix[0][0];
    temp_matrix[1][1] = matrix[1][1];
    temp_matrix[2][2] = matrix[2][2];
    temp_matrix[1][0] = matrix[0][1];
    temp_matrix[2][0] = matrix[0][2];
    temp_matrix[2][1] = matrix[1][2];

    std::cout << "\n";
    for (auto & i : temp_matrix) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double y1 = matrix[0][3] / matrix[0][0];
    double y2 = (matrix[1][3] - matrix[0][1] * y1) / matrix[1][1];
    double y3 = (matrix[2][3] - matrix[0][2] * y1 - matrix[1][2] * y2) / matrix[2][2];

    std::cout << "\n";
    printf("y1 = %.6lf \n", y1);
    printf("y2 = %.6lf \n", y2);
    printf("y3 = %.6lf \n", y3);

    temp_matrix[0][3] = y1;
    temp_matrix[1][3] = y2;
    temp_matrix[2][3] = y3;

    std::cout << "\n";
    for (auto & i : temp_matrix) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double x3 = temp_matrix[2][3] / temp_matrix[2][2];
    double x2 = (temp_matrix[1][3] - x3 * temp_matrix[2][1]) / temp_matrix[1][1];
    double x1 = (temp_matrix[0][3] - x3 * temp_matrix[2][0] - x2 * temp_matrix[1][0]) / temp_matrix[0][0];

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

void solve_holecki() {
    // Проверки главных миноров
    if (matrix[0][0] == 0) {
        std::cout << "Minor1 == 0";
        return;
    }
    if (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] == 0) {
        std::cout << "Major2 == 0";
        return;
    }
    double minor3 =
        matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
        matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
        matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);

    if (minor3 == 0) {
        std::cout << "Major3 == 0";
        return;
    }

    double B[3][3], C[3][3];
    C[0][0] = 1.0;
    C[1][1] = 1.0;
    C[2][2] = 1.0;

    B[0][0] = matrix[0][0];
    C[0][1] = matrix[0][1] / B[0][0];
    C[0][2] = matrix[0][2] / B[0][0];

    B[1][0] = matrix[1][0];
    B[1][1] = matrix[1][1] - B[1][0] * C[0][1];
    C[1][2] = (matrix[1][2] - B[1][0] * C[0][2]) / B[1][1];

    B[2][0] = matrix[2][0];
    B[2][1] = matrix[2][1] - B[2][0] * C[0][1];
    B[2][2] = matrix[2][2] - B[2][0] * C[0][2] - B[2][1] * C[1][2];

    std::cout << "\n";
    for (auto & i : B) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    std::cout << "\n";
    for (auto & i : C) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    // Прверка произведения матриц
    double checkout[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                checkout[i][j] += B[i][k] * C[k][j];
            }
        }
    }

    bool success = true;
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%6.3lf ", checkout[i][j]);
            if (fabs(checkout[i][j] - matrix[i][j]) > EPSILON) {
                success = false;
            }
        }
        std::cout << "\n";
    }
    if (success) {
        std::cout << "\nMatrix is OK\n";
    }
    else {
        std::cout << "Matrix missmatch";
        return;
    }

    double y1 = matrix[0][3] / B[0][0];
    double y2 = (matrix[1][3] - y1 * matrix[1][0]) / B[1][1];
    double y3 = (matrix[2][3] - y1 * matrix[2][0] - y2 * matrix[2][1]) / B[2][2];

    std::cout << "\n";
    printf("y1 = %.6lf \n", y1);
    printf("y2 = %.6lf \n", y2);
    printf("y3 = %.6lf \n", y3);
}

int main() {
    std::copy(&matrix[0][0], &matrix[0][0]+3*4,&init_matrix[0][0]);
    print_matrix("Initial matrix");

    // solve_gauss();
    // solve_sqrt();
    solve_holecki();

    return 0;
}