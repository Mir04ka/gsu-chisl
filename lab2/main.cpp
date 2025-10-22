#define K (0.01 * (14 + 21))
// #define K 0
#define EPSILON 0.000001
#define EPS 0.001
#include <cmath>
#include <iostream>
#include <string>
#include <cstring>

// double matrix[3][4] = {{2.04, 0.25, 0.75, 35.12}, {0.25, 1.54, 0.45, 22.04}, {0.75, 0.45, 3.04, 37.08}};
double matrix[3][4] = {{2 + K, 0.25, 0.75, 3 + K}, {0.25, 1.5 + K, 0.45, 2.2 + K}, {0.75, 0.45, 3 + K, 4.2 + K}};
double init_matrix[3][4];

double progon_matrix[3][4] = {{2 + K, 0.25, 0, 3 + K}, {0.25, 1.5 + K, 0.45, 2.2 + K}, {0, 0.45, 3 + K, 4.2 + K}};

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
    std::cout << "\nМетод Гаусса\n";

    double det = matrix[0][0];

    // Проверка, что элемент 1 1 не равен нулю
    if (matrix[0][0] == 0) {
        std::cout << "a11 is zero!";
        return;
    }

    // Делим все элементы первой строки на первый элемент
    for (int i = 3; i >= 0; i--) {
        matrix[0][i] = matrix[0][i] / matrix[0][0];
    }
    print_matrix("Делим все элементы первой строки на первый элемент");

    // Прибавляем к строкам 2 и 3 первой строки, умноженной на первый элемент строки с минусом
    for (int i = 1; i < 3; i++) {
        double kf = -matrix[i][0];
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = matrix[i][j] + matrix[0][j] * kf;
        }
    }
    print_matrix("Прибавляем к строкам 2 и 3 элементы первой строки, умноженные на первый элемент строки с минусом");

    det *= matrix[1][1];

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
    print_matrix("Делим все элементы второй строки на элемент 2 2");

    // Прибавляем к 3 строке вторую, умноженную на второй элемент строки с минусом
    double kf = -matrix[2][1];
    for (int j = 0; j < 4; j++) {
        matrix[2][j] = matrix[2][j] + matrix[1][j] * kf;
    }
    print_matrix("Прибавляем к 3 строке элементы второй, умноженные на элемент 2 2 с минусом");

    det *= matrix[2][2];

    // Проверка, что элемент 3 3 не равен нулю
    if (matrix[2][2] == 0) {
        std::cout << "a33 is zero!";
        return;
    }

    // Делим все элементы второй строки на элемент 3 3
    temp = matrix[2][2];
    for (int i = 3; i >= 0; i--) {
        matrix[2][i] = matrix[2][i] / temp;
    }
    print_matrix("Делим все элементы второй строки на элемент 3 3");

    // Вычисляем неизвестные
    double x3 = matrix[2][3];
    double x2 = matrix[1][3] - matrix[1][2] * x3;
    double x1 = matrix[0][3] - matrix[0][2] * x3 - matrix[0][1] * x2;

    std::cout << "\nОтвет:\n";
    printf("x1 = %.6lf \n", x1);
    printf("x2 = %.6lf \n", x2);
    printf("x3 = %.6lf \n", x3);

    // Проверка
    for (auto & i : init_matrix) {
        double res = i[0] * x1 + i[1] * x2 + i[2] * x3;
        std::cout << "\n";
        printf("Ожидаемое: %.6lf Результат: %.6lf Правильно: %s", i[3], res, fabs(res - i[3]) < EPSILON ? "ДА" : "НЕТ");
    }

    // Определитель
    std::cout << "\nОпределитель: " << det << "\n";
}

void solve_sqrt() {
    std::cout << "\nМетод квадратного корня\n";

    double detB, det;
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

    print_matrix("Вычисляем треугольную матрицу B из начальной матрицы");

    detB = matrix[0][0] * matrix[1][1] * matrix[2][2];

    temp_matrix[0][0] = matrix[0][0];
    temp_matrix[1][1] = matrix[1][1];
    temp_matrix[2][2] = matrix[2][2];
    temp_matrix[1][0] = matrix[0][1];
    temp_matrix[2][0] = matrix[0][2];
    temp_matrix[2][1] = matrix[1][2];

    std::cout << "\nВычисляем обратную треугольную матрицу C из начальной\n";
    for (auto & i : temp_matrix) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double y1 = matrix[0][3] / matrix[0][0];
    double y2 = (matrix[1][3] - matrix[0][1] * y1) / matrix[1][1];
    double y3 = (matrix[2][3] - matrix[0][2] * y1 - matrix[1][2] * y2) / matrix[2][2];

    std::cout << "\nВычисляем коэф-ты y из матрицы B\n";
    printf("y1 = %.6lf \n", y1);
    printf("y2 = %.6lf \n", y2);
    printf("y3 = %.6lf \n", y3);

    temp_matrix[0][3] = y1;
    temp_matrix[1][3] = y2;
    temp_matrix[2][3] = y3;

    std::cout << "\nЗадаем свободные члены матрицы C равными коэф-там y\n";
    for (auto & i : temp_matrix) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    double x3 = temp_matrix[2][3] / temp_matrix[2][2];
    double x2 = (temp_matrix[1][3] - x3 * temp_matrix[2][1]) / temp_matrix[1][1];
    double x1 = (temp_matrix[0][3] - x3 * temp_matrix[2][0] - x2 * temp_matrix[1][0]) / temp_matrix[0][0];

    std::cout << "\nВычисляем из полученной матрицы C неизвестные\n";
    printf("x1 = %.6lf \n", x1);
    printf("x2 = %.6lf \n", x2);
    printf("x3 = %.6lf \n", x3);

    // Проверка
    for (auto & i : init_matrix) {
        double res = i[0] * x1 + i[1] * x2 + i[2] * x3;
        std::cout << "\n";
        printf("Ожидаемое: %.6lf Результат: %.6lf Правильно: %s", i[3], res, fabs(res - i[3]) < EPSILON ? "ДА" : "НЕТ");
    }

    // Определитель
    det = detB * detB;
    std::cout << "\nОпределитель: " << det << "\n";
}

void solve_holecki() {
    std::cout << "\nМетод Холецкого\n";

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

    std::cout << "\nГлавные миноры не равны 0. Можно продолжать\n";

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

    std::cout << "\nМатрица B\n";
    for (auto & i : B) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    std::cout << "\nМатрица C\n";
    for (auto & i : C) {
        for (double j : i) {
            printf("%6.3lf ", j);
        }
        std::cout << "\n";
    }

    std::cout << "\nA = B * C\n";

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
        std::cout << "\nМатрицы в норме\n";
    }
    else {
        std::cout << "Матрицы не совпадают";
        return;
    }

    double y1 = matrix[0][3] / B[0][0];
    double y2 = (matrix[1][3] - B[1][0] * y1) / B[1][1];
    double y3 = (matrix[2][3] - B[2][0] * y1 - B[2][1] * y2) / B[2][2];

    std::cout << "\n";
    printf("y1 = %.6lf \n", y1);
    printf("y2 = %.6lf \n", y2);
    printf("y3 = %.6lf \n", y3);

    double x3 = y3;
    double x2 = y2 - C[1][2] * x3;
    double x1 = y1 - C[0][1] * x2 - C[0][2] * x3;

    std::cout << "\n";
    printf("x1 = %.6lf \n", x1);
    printf("x2 = %.6lf \n", x2);
    printf("x3 = %.6lf \n", x3);

    // Проверка
    for (auto & i : init_matrix) {
        double res = i[0] * x1 + i[1] * x2 + i[2] * x3;
        std::cout << "\n";
        printf("Ожидаемое: %.6lf Полученное: %.6lf Статус: %s", i[3], res, fabs(res - i[3]) < EPSILON ? "ОК" : "НЕВЕРНО");
    }

    // Определитель
    double det = B[0][0] * B[1][1] * B[2][2];
    std::cout << "\nОпределитель = " << det << "\n";
}

void solve_progonka() {
    std::cout << "\nМетод прогонки\n";

    std::copy(&progon_matrix[0][0], &progon_matrix[0][0]+3*4,&matrix[0][0]);
    print_matrix();

    std::cout << "Матрица симметрична по главной диагонали. Можно решать методом прогонки\n";

    double y1 = matrix[0][0];
    double alfa1 = (-matrix[0][1]) / y1;
    double beta1 = matrix[0][3] / y1;

    double y2 = matrix[1][1] + alfa1 * matrix[1][0];
    double alfa2 = (-matrix[1][2]) / y2;
    double beta2 = (matrix[1][3] - matrix[1][0] * beta1) / y2;

    double y3 = matrix[2][2] + alfa2 * matrix[2][1];
    double beta3 = (matrix[2][3] - matrix[2][1] * beta2) / y3;

    double x3 = beta3;
    double x2 = alfa2 * x3 + beta2;
    double x1 = alfa1 * x2 + beta1;

    std::cout << "\n";
    printf("x1 = %.6lf \n", x1);
    printf("x2 = %.6lf \n", x2);
    printf("x3 = %.6lf \n", x3);

    // Проверка
    for (auto & i : matrix) {
        double res = i[0] * x1 + i[1] * x2 + i[2] * x3;
        std::cout << "\n";
        printf("Ожидаемое: %.6lf Полученное: %.6lf Статус: %s", i[3], res, fabs(res - i[3]) < EPSILON ? "OK" : "НЕВЕРНО");
    }
}

void solve_iter() {
    std::cout << "\nМетод простых итераций\n";

    // Проверка сходимости
    if ((matrix[0][0] <= matrix[0][1] + matrix[0][2]) || (matrix[1][1] <= matrix[1][0] + matrix[1][2]) || (matrix[2][2] <= matrix[2][1] + matrix[2][0])) {
        std::cout << "\nNo conditions!\n";
        return;
    }

    std::cout << "\nСходимость есть\n";

    // Вычисляем коэфы
    double mults[3][2];
    mults[0][0] = matrix[0][1] / matrix[0][0] * -1;
    mults[0][1] = matrix[0][2] / matrix[0][0] * -1;
    mults[1][0] = matrix[1][0] / matrix[1][1] * -1;
    mults[1][1] = matrix[1][2] / matrix[1][1] * -1;
    mults[2][0] = matrix[2][0] / matrix[2][2] * -1;
    mults[2][1] = matrix[2][1] / matrix[2][2] * -1;

    // Выводим коэфы
    std::cout << "\nКоэффициенты\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%6.3lf ", mults[i][j]);
        }
        std::cout << "\n";
    }

    // Вычисляем и выводим начальное приближение
    std::cout << "\nНачальное приближение\n";
    double x_old[3], x_new[3];
    double c[3];
    for (int i = 0; i < 3; i++) {
        x_old[i] = matrix[i][3] / matrix[i][i];
        c[i] = x_old[i];
        std::cout << i + 1 << ". " << x_old[i] << "\n";
    }

    // Делаем итерации(если их более 100 - выход)
    for (int i = 0; i < 100; i++) {
        x_new[0] = mults[0][0] * x_old[1] + mults[0][1] * x_old[2] + c[0];
        x_new[1] = mults[1][0] * x_old[0] + mults[1][1] * x_old[2] + c[1];
        x_new[2] = mults[2][0] * x_old[0] + mults[2][1] * x_old[1] + c[2];

        printf("\nИтерация №%d: %9.6lf %9.6lf %9.6lf\n", i + 1, x_new[0], x_new[1], x_new[2]);
        // printf("\nIteration %d: %9.6lf %9.6lf %9.6lf\n", i + 1, x_old[0], x_old[1], x_old[2]);
        double prec = std::sqrt(pow((x_new[0] - x_old[0]), 2) + pow((x_new[1] - x_old[1]), 2) + pow((x_new[2] - x_old[2]), 2));
        std::cout << "Погрешность: " << prec << "\n";
        if (prec <= EPS) {
            std::cout << "Завершено!\n";

            // Проверка
            std::cout << "\nПроверка\n";
            for (int j = 0; j < 3; j++) {
                double tmp = matrix[j][0] * x_new[0] + matrix[j][1] * x_new[1] + matrix[j][2] * x_new[2];
                printf("\n%9.6lf %s", tmp, fabs(tmp - matrix[j][3]) < EPS ? "OK" : "НЕВЕРНО");
            }

            std::cout << "\n\nВыполнено за " << i + 1 << " итераций\n";

            return;
        }

        x_old[0] = x_new[0];
        x_old[1] = x_new[1];
        x_old[2] = x_new[2];
    }

    std::cout << "\nСлишком много итераций! Завершение\n";
}

void solve_zeidel() {
    std::cout << "\nМетод Зейделя\n";

    // Проверка сходимости
    if ((matrix[0][0] <= matrix[0][1] + matrix[0][2]) || (matrix[1][1] <= matrix[1][0] + matrix[1][2]) || (matrix[2][2] <= matrix[2][1] + matrix[2][0])) {
        std::cout << "\nNo conditions!\n";
        return;
    }

    std::cout << "\nСходимость есть\n";

    // Вычисляем коэфы
    double mults[3][2];
    mults[0][0] = matrix[0][1] / matrix[0][0] * -1;
    mults[0][1] = matrix[0][2] / matrix[0][0] * -1;
    mults[1][0] = matrix[1][0] / matrix[1][1] * -1;
    mults[1][1] = matrix[1][2] / matrix[1][1] * -1;
    mults[2][0] = matrix[2][0] / matrix[2][2] * -1;
    mults[2][1] = matrix[2][1] / matrix[2][2] * -1;

    // Выводим коэфы
    std::cout << "\nКоэффициенты\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%6.3lf ", mults[i][j]);
        }
        std::cout << "\n";
    }

    // Вычисляем и выводим начальное приближение
    std::cout << "\nНачальное приближение\n";
    double x_old[3], x_new[3];
    double c[3];
    for (int i = 0; i < 3; i++) {
        x_old[i] = matrix[i][3] / matrix[i][i];
        c[i] = x_old[i];
        std::cout << i + 1 << ". " << x_old[i] << "\n";
    }

    // Делаем итерации(если их более 100 - выход)
    for (int i = 0; i < 100; i++) {
        x_new[0] = mults[0][0] * x_old[1] + mults[0][1] * x_old[2] + c[0];
        x_new[1] = mults[1][0] * x_new[0] + mults[1][1] * x_old[2] + c[1];
        x_new[2] = mults[2][0] * x_new[0] + mults[2][1] * x_new[1] + c[2];

        printf("\nИтерация №%d: %9.6lf %9.6lf %9.6lf\n", i + 1, x_new[0], x_new[1], x_new[2]);
        // printf("\nIteration %d: %9.6lf %9.6lf %9.6lf\n", i + 1, x_old[0], x_old[1], x_old[2]);
        double prec = std::sqrt(pow((x_new[0] - x_old[0]), 2) + pow((x_new[1] - x_old[1]), 2) + pow((x_new[2] - x_old[2]), 2));
        std::cout << "Погрешность: " << prec << "\n";
        if (prec <= EPS) {
            std::cout << "Завершено!\n";

            // Проверка
            std::cout << "\nПроверка\n";
            for (int j = 0; j < 3; j++) {
                double tmp = matrix[j][0] * x_new[0] + matrix[j][1] * x_new[1] + matrix[j][2] * x_new[2];
                printf("\n%9.6lf %s", tmp, fabs(tmp - matrix[j][3]) < EPS ? "OK" : "НЕВЕРНО");
            }

            std::cout << "\n\nВыполнено за " << i + 1 << " итераций\n";

            return;
        }

        x_old[0] = x_new[0];
        x_old[1] = x_new[1];
        x_old[2] = x_new[2];
    }

    std::cout << "\nСлишком много итераций!\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::copy(&matrix[0][0], &matrix[0][0]+3*4,&init_matrix[0][0]);
    print_matrix("Начальная матрица");

    solve_gauss();
    // solve_sqrt();
    // solve_holecki();

    // solve_progonka();

    // solve_iter();
    // solve_zeidel();

    return 0;
}