// Послідовність: a1 = 1, an = (2*a(n-1) + 8/a(n-1)^2) / 3, n > 1
// Границя: 2 (метод Ньютона для рівняння x^3 = 8)
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Обчислення a_n на рекурсивному підйомі.
// n     - номер члена послідовності
// level - поточний рівень рекурсії (параметр-значення)
// depth - глибина рекурсії (параметр-посилання)
double a(const int n, const int level, int& depth);

// Пошук границі на рекурсивному спуску.
// prev  - попередній член послідовності
// k     - номер члена, який обчислюється на цьому рівні
// eps   - точність
// level - поточний рівень рекурсії, depth - глибина рекурсії
// cnt   - номер члена, на якому досягнуто точності (параметр-посилання)
double lim(const double prev, const int k, const double eps,
    const int level, int& depth, int& cnt);

double a(const int n, const int level, int& depth)
{
    if (level > depth)
        depth = level;
    cout << "  level = " << level << ", n = " << n << endl;

    if (n == 1)                 // базова задача
        return 1;
    double p = a(n - 1, level + 1, depth);   // рекурсивний виклик
    return (2 * p + 8 / (p * p)) / 3;        // дія на рекурсивному підйомі
}

double lim(const double prev, const int k, const double eps,
    const int level, int& depth, int& cnt)
{
    if (level > depth)
        depth = level;
    cout << "  level = " << level << ", n = " << k << endl;

    double next = (2 * prev + 8 / (prev * prev)) / 3;  // дія на спуску
    if (abs(next - prev) < eps)                        // базова задача
    {
        cnt = k;
        return next;
    }
    return lim(next, k + 1, eps, level + 1, depth, cnt); // рекурсивний виклик
}

int main()
{
    int n;
    double eps;
    cout << "n = "; cin >> n;
    cout << "eps = "; cin >> eps;

    cout << fixed << setprecision(10);

    cout << "\nОбчислення a(n):" << endl;
    int depth = 0;
    double an = a(n, 1, depth);
    cout << "a(" << n << ") = " << an << endl;
    cout << "depth = " << depth << endl;

    cout << "\nПошук границі з точністю eps:" << endl;
    depth = 0;
    int cnt = 0;
    double L = lim(1, 2, eps, 1, depth, cnt);
    cout << "lim = " << L << " (досягнуто на n = " << cnt << ")" << endl;
    cout << "depth = " << depth << endl;
    cout << "Точне значення границі: 2" << endl;
    return 0;
}
