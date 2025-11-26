#include <cmath>
#include <iomanip>
#include <iostream>
#define EPSILON 1e-3

using namespace std;

double odds[4] = {1, 2, 0, 4};

void solve_iter(double from, double to) {
    cout << "\nУточняем корень уравнения x1 на [-3; -2.5] уравнения f(x) = x^3 + 2 * x^2 + 4\n";
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
    cout << "\nУточняем корень уравнения x1 на [-3; -2.5] уравнения f(x) = x^3 + 2 * x^2 + 4\n";
    cout << "\nМетод Ньютона\n";

    double init_pribl;
    if (f(from) * f2(from) > 0) {
        cout << "\nУсловие выполняется для начала отрезка";
        init_pribl = from;
    }
    else if (f(to) * f2(to) > 0) {
        cout << "\nУсловие выполняется для конца отрезка";
        init_pribl = to;
    }
    else {
        cout << "\nУсловие не выполняется ни для одного конца отрезка!";
        return;
    }

    cout << "\nНачальное приближение: " << init_pribl << "\n";

    double current_x = init_pribl - f(init_pribl) / f1(init_pribl);
    double prev_x = init_pribl;
    for (int i = 1; i < 100; i++) {
        double eps = current_x - prev_x;
        cout << i << ". " << current_x << " | Разность: " << eps << "\n";
        if (eps < EPSILON) {
            cout << "x=x" << i << "\n";

            cout << "Проверка: \nЕсли полученный х подставить в начальное уравнение, то ответ будет: " << f(current_x) << " " << (f(current_x) < EPSILON ? "ОК" : "НЕВЕРНО") << "\n";

            return;
        }

        prev_x = current_x;
        current_x = prev_x - f(prev_x) / f1(prev_x);
    }

    std::cout << "Достигнуто максимальное количество итераций! Ответ не найден";
}

void solve_hord(double from, double to) {
    cout << "\nУточняем корень уравнения x1 на [-3; -2.5] уравнения f(x) = x^3 + 2 * x^2 + 4\n";
    cout << "\nМетод хорд\n";

    double c;
    if (f(from) * f2(from) > 0) {
        cout << "\nУсловие выполняется для начала отрезка";
        c = from;
    }
    else if (f(to) * f2(to) > 0) {
        cout << "\nУсловие выполняется для конца отрезка";
        c = to;
    }
    else {
        cout << "\nУсловие не выполняется ни для одного конца отрезка!";
        return;
    }

    cout << "\nНеподвижная точка: " << c << "\n";

    double init_pribl;
    if (f(from) * f(c) < 0) {
        cout << "\nУсловие выполняется для начала отрезка";
        init_pribl = from;
    }
    else if (f(to) * f(c) < 0) {
        cout << "\nУсловие выполняется для конца отрезка";
        init_pribl = to;
    }
    else {
        cout << "\nУсловие не выполняется ни для одного конца отрезка!";
        return;
    }

    cout << "\nНачальное приближение: " << init_pribl << "\n";

    double current_x = init_pribl - (f(init_pribl) * (init_pribl - c)) / (f(init_pribl) - f(c));
    double prev_x = init_pribl;
    for (int i = 1; i < 100; i++) {
        double eps = abs(current_x - prev_x);
        cout << i << ". " << current_x << " | Разность: " << eps << "\n";
        if (eps < EPSILON) {
            cout << "x=x" << i << "\n";

            cout << "Проверка: \nЕсли полученный х подставить в начальное уравнение, то ответ будет: " << f(current_x) << " " << (f(current_x) < EPSILON ? "ОК" : "НЕВЕРНО") << "\n";

            return;
        }

        prev_x = current_x;
        current_x = prev_x - f(prev_x) / f1(prev_x);
    }

    std::cout << "Достигнуто максимальное количество итераций! Ответ не найден";
}

void solve_combine(double from, double to) {
    cout << "\nУточняем корень уравнения x1 на [-3; -2.5] уравнения f(x) = x^3 + 2 * x^2 + 4\n";
    cout << "\nКомбинированный метод\n";

    double a = from;
    double b = to;

    double c;     // неподвижная точка (для хорд)
    bool newton_left; // true: Newton на a, false: Newton на b

    if (f(a) * f2(a) > 0) {
        cout << "Выполняется f(a) * f''(a) > 0 → a считаем методом Ньютона, b — методом хорд.\n";
        newton_left = true;
        c = a;
    }
    else if (f(b) * f2(b) > 0) {
        cout << "Выполняется f(b) * f''(b) > 0 → b считаем методом Ньютона, a — методом хорд.\n";
        newton_left = false;
        c = b;
    }
    else {
        cout << "Условие f(x)*f''(x)>0 не выполняется ни в одной точке отрезка!\n";
        return;
    }

    cout << "Неподвижная точка c = " << c << "\n";

    // Начальные приближения
    double x_new;
    double x_hord;

    if (newton_left) {
        x_new = a - f(a) / f1(a);
        x_hord = b - f(b) * (b - c) / (f(b) - f(c));
    } else {
        x_new = b - f(b) / f1(b);
        x_hord = a - f(a) * (a - c) / (f(a) - f(c));
    }

    cout << "Начаьное приближение:\nНьютона: " << x_new << "\nХорд: " << x_hord << "\n";

    cout << "\nНачало итераций:\n";

    for (int i = 1; i <= 100; i++) {

        cout << "\nИтерация " << i << ":\n";
        cout << "  Ньютон: x_new = " << x_new << "\n";
        cout << "  Хорды:  x_hord = " << x_hord << "\n";

        if (fabs(x_new - x_hord) < EPSILON) {
            double ans = (x_new + x_hord) / 2;
            cout << "\nКорень найден: x = " << ans << "\n";
            cout << "Проверка: f(x) = " << f(ans) << "\n";
            return;
        }

        if (newton_left) {
            a = x_new;
            b = x_hord;
        } else {
            b = x_new;
            a = x_hord;
        }

        if (newton_left) {
            x_new = a - f(a) / f1(a);
            x_hord = b - f(b) * (b - c) / (f(b) - f(c));
        } else {
            x_new = b - f(b) / f1(b);
            x_hord = a - f(a) * (a - c) / (f(a) - f(c));
        }
    }

    cout << "\nДостигнуто максимальное количество итераций! Корень не найден.\n";
}


double phi1(double y) {
    return 1.5 - cos(y);
}

double phi2(double x) {
    return (1.0 + sin(x - 0.5)) / 2.0;
}

double F1(double x, double y) {
    return cos(y) + x - 1.5;
}

double F2(double x, double y) {
    return 2.0 * y - sin(x - 0.5) - 1.0;
}

// double F1(double x, double y) { return cos(y) + x - 1.5; }
// double F2(double x, double y) { return 2.0 * y - sin(x - 0.5) - 1.0; }
//
// // функции итераций
// double phi1(double y) { // x = 1.5 - cos(y)
//     return 1.5 - cos(y);
// }
// double phi2(double x) { // y = (1 - sin(x - 0.5)) / 2
//     return 0.5 * (1.0 - sin(x - 0.5));
// }
//
// производные
double dphi1_dy(double y) { return sin(y); }                    // dx/dy
double dphi2_dx(double x) { return -0.5 * cos(x - 0.5); }       // dy/dx


void solve_system_iter() {
    cout << "Используя метод итераций решаем систему уравнений\n┌cos(y) + x = 1.5\n{\n└2y - sin(x - 0.5) = 1";
    cout << "Проверяем условия сходимости:\n";
    cout << "\nd(1.5-cos(y))/dx = 0\nd(1.5-cos(y))/dy = sin(y)\nd((1-sin(x-0.5))/2)/dx = -(cos(x-0.5)/2)\nd((1-sin(x-0.5))/2)/dy = 0\n";

    double x_prev = 1.17;
    double y_prev = 0.81;

    cout << "\nПо графику видим, что x0 = " << x_prev << " y0 = " << y_prev << "\n";

    double q1 = fabs(dphi1_dy(y_prev));   // |∂φ1/∂y|
    double q2 = fabs(dphi2_dx(x_prev));   // |∂φ2/∂x|
    double q = max(q1, q2);
    cout << "Оценка локального коэффициента сходимости q = max(|dφ1/dy|, |dφ2/dx|) = " << q << "\n";
    if (q >= 1.0) {
        cout << "q >= 1 - метод может не сходиться\n";
        return;
    }
    cout << "q < 1 - локально метод сходится\n";

    cout << fixed << setprecision(10);

    for (int k = 1; k <= 200; ++k) {

        double x_next = phi1(y_prev);      // ← новое x
        double y_next = phi2(x_next);      // ← новое y (ВАЖНО!)

        double dx = fabs(x_next - x_prev);
        double dy = fabs(y_next - y_prev);
        double err = max(dx, dy);

        cout << "Iter " << setw(3) << k
             << ": x = " << x_next
             << ", y = " << y_next
             << ", err = " << err << "\n";

        if (err < EPSILON) {
            cout << "\nРезультат:\n";
            cout << "x = " << x_next << "\n";
            cout << "y = " << y_next << "\n\n";
            cout << "Проверка:\n";
            cout << "F1 = " << F1(x_next, y_next) << "\n";
            cout << "F2 = " << F2(x_next, y_next) << "\n";
            return;
        }

        x_prev = x_next;
        y_prev = y_next;
    }

    cout << "Метод не сошелся.\n";

    cout << "\nДостигнуто максимальное количество итераций! Решение не найдено\n";
    cout << "Текущее приближение: x = " << x_prev << " , y = " << y_prev << "\n";
    cout << "Остатки: F1 = " << F1(x_prev, y_prev) << " , F2 = " << F2(x_prev, y_prev) << "\n";
}

void solve_system_newton() {
    cout << "Используя метод итераций решаем систему уравнений\n┌cos(y) + x = 1.5\n{\n└2y - sin(x - 0.5) = 1\n";

    double x = 1.17;
    double y = 0.81;

    for(int iter = 1; iter <= 20; iter++) {

        double f1 = F1(x, y);
        double f2 = F2(x, y);

        double J11 = 1;
        double J12 = -sin(y);
        double J21 = -cos(x - 0.5);
        double J22 = 2;

        // Якобиан
        double det = J11 * J22 - J12 * J21;

        if (fabs(det) < 1e-10) {
            cout << "Якобиан вырожден!\n";
            return;
        }

        // Обратная матрица * F
        double dx = (-f1 * J22 + f2 * J12) / det;
        double dy = (-J11 * f2 + f1 * J21) / det;

        x += dx;
        y += dy;

        cout << "Iter " << iter
             << ": x=" << x
             << "  y=" << y
             << "  |dx|=" << fabs(dx)
             << "  |dy|=" << fabs(dy) << endl;

        if (fabs(dx) < EPSILON && fabs(dy) < EPSILON)
            break;
    }

    cout << "\nПроверка:\n";
    cout << "F1 = " << F1(x,y) << endl;
    cout << "F2 = " << F2(x,y) << endl;

    cout << "\nРешение:\n";
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // solve_iter(-3, -2.5);
    // solve_newton(-3, -2.5);
    // solve_hord(-3, -2.5);
    // solve_combine(-3, -2.5);
    solve_system_iter();
    // solve_system_newton();

    return 0;
}