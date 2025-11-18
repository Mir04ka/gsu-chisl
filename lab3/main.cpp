#include <iostream>
#define EPSILON 1e-3

using namespace std;

double odds[4] = {1, 2, 0, 4};

void solve_iter(double from, double to) {
    cout << "\nМетод итераций\n";

    double der_odds[4];
    int k = 3;
    for (int i = 0; i < 4; i++) {
        der_odds[i] = odds[i] * k;
        k--;
    }

    cout << "\nПроизводная:\nf'(x) = ";
    for (int i = 3; i >=1; i--) {
        cout << der_odds[3 - i] << " * x^" << i;
        if (i != 1) cout << " + ";
    }

    cout << "\n\nПроверим знак производной на рассматриваемом отрезке [" << from << "; " << to << "]:\n";
    double step = 0.1;
    bool is_negative = false;
    double max = from * from * der_odds[0] + from * der_odds[1] + der_odds[2];
    for (double i = from; i < to + step; i += step) {
        double res = i * i * der_odds[0] + i * der_odds[1] + der_odds[2];
        if (max < res) max = res;
        if (res < 0) is_negative = true;

        printf("x = %4.1lf -> f'(x) = %4.1lf\n", i, res);
    }

    max = abs(max);

    cout << "\nf'(x) " << (is_negative ? "<" : ">") << " 0\n";
    cout << "max|f'(x)| = " << max << "\n";

    cout << "\nlambda = 1/" << max << "\n";

    cout << "φ(x) = x - 1/" << max << "(" << odds[0] << "x^3 + " << odds[1] << "x^2 + " << odds[2] << "x + " << odds[3] << ")\n";

    cout << "Начальное приближение x0 = " << from << "\n";

    double current, previous;
    previous = from;

    for (int i = 0; i < 100; i++) {
        current = previous - 1 / max * (previous * previous * previous * odds[0] + previous * previous * odds[1] + previous * odds[2] + odds[3]);

        double prec = abs(current - previous);
        cout << "\nx" << i + 1 << " = " << current << " Точность: " << prec << "\n";

        if (prec <= EPSILON) {
            cout << "Достигнута достаточная точность. Ответ найден\nОтвет: f(x" << i + 1 << ") = " << current << " \n";
            return;
        }

        previous = current;
    }

    cout << "\nOut of iterations!";
}

double f(double x) {
    return odds[0] * x * x * x +
           odds[1] * x * x +
           odds[2] * x +
           odds[3];
}

double f1(double x) {
    return 3 * odds[0] * x * x +
           2 * odds[1] * x +
           odds[2];
}

double f2(double x) {
    return 6 * odds[0] * x +
           2 * odds[1];
}

void solve_newton(double from, double to) {
    double init_pribl;

    double der_odds[3];
    int k = 3;
    for (int i = 0; i < 3; i++) {
        der_odds[i] = odds[i] * k;
        k--;
    }

    double der2_odds[2];
    k = 2;
    for (int i = 0; i < 2; i++) {
        der2_odds[i] = der_odds[i] * k;
        k--;
    }



    // TODO Newton method
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "\nУточняем корень уравнения x1 на [-3; -2.5] уравнения f(x) = x^3 + 2 * x^2 + 4\n";

    solve_iter(-3, -2.5);
    solve_newton(-3, -2.5);

    return 0;
}