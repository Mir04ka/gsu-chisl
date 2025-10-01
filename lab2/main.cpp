#define K (0.01 * (14 + 21))
#include <iostream>
#include <string>

int a, b;
double matrix[3][4] = {{2 + K, 0.25, 0.75, 3 + K}, {0.25, 1.5 + K, 0.45, 2.2 + K}, {0.75, 0.45, 3 + K, 4.2 + K}};

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

    //TODO переписать все так, чтобы работало с любыми матрицами(масштабировалось)

    // Делим все элементы второй строки на элемент 2 2
    double temp = matrix[1][1];
    for (int i = 3; i >= 0; i--) {
        matrix[1][i] = matrix[1][i] / temp;
    }
    print_matrix();

    // Прибавляем к строкам 1 и 3 вторую строку, умноженную на первый элемент строки с минусом
    for (int i = 1; i < 3; i++) {
        double kf = -matrix[i][0];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = matrix[i][j] + matrix[0][j] * kf;
        }
    }
    print_matrix();
}

int main() {
    print_matrix("Initial matrix");

    solve_gauss();

    return 0;
}