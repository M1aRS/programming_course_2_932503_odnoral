#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <string>


// Lab 07
// TODO: реализуйте решение по заданию в labs/lab07_console/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке
int main() {
    // Задание 1: вычисление значений функции.
    // Ввод: x0 — начальная точка интервала.
    double x0 = 0.0;
    if (!(std::cin >> x0)) {
        return 1;
    }
    else if ((x0 <= 0) || (x0 > 4)) {
        std::cout << "Your point must be in these borders (0;4]";
        return 1;
    }
    double delta = (4 - x0) / 10;
    for (double i = x0; i <= 4; i = i + delta) {
        std::cout << i << ' ' << sin(i) / i << std::endl;
    }
    printf("\n");
    // TODO: вычислите и выведите 10 значений функции на (0, 4].

    // Задание 2: сумма чисел Фибоначчи.
    // Ввод: MAX — ограничение на сумму.
    long long max_value = 0;
    if (!(std::cin >> max_value)) {
        return 0;
    } else if (max_value < 0) {
        std::cout << "The value cannot be less than 0." << std::endl;
        return 1;
    }
    long long fib_sum = 1;
    long long fib_prev = 1; long long fib_post_prev = 0;
    long long temp;
    int fib_count = 1;
    while (max_value >= fib_sum) {
        temp = fib_prev;
        fib_prev = fib_prev + fib_post_prev;
        fib_post_prev = temp;
        fib_sum += fib_prev;
        fib_count++;
        //std::cout << fib_sum << " - current sum; var - " << fib_prev << std::endl;
    }
    std::cout << "Number of elements: " << fib_count<< " Sum of elements : " << fib_sum << std::endl;
    printf("\n");
    // TODO: вычислите N и S (S <= MAX) и выведите результаты.

    //Задание 3: кредиты
    double loan_value; printf("(RUB): "); if (scanf("%lf", &loan_value) != 1) return 1;
    double loan_percent; printf("(%%) : "); if (scanf("%lf", &loan_percent) != 1) return 1;
    int loan_months; printf("(month) : ");  if (scanf("%d", &loan_months) != 1) return 1;
    /*std::cout << "(RUB): ";  std::cin >> loan_value;
    std::cout << "(%): "; std::cin >> loan_percent;
    std::cout << "(month): "; std::cin >> loan_months;*/
    loan_percent = loan_percent / (100*12);
    double loan_payment, loan_debt, loan_debt_total = 0;
    for (int i = 0; i < loan_months; i++) {
        loan_debt = loan_value * loan_percent;
        loan_payment = (loan_value / (loan_months-i)) + loan_debt;
        printf("%-3d %-10.2lf | %-10.2lf | %-10.2lf \n", (i+1), loan_value, loan_debt, loan_payment);
        loan_value += loan_debt;
        loan_debt_total += loan_debt;
        loan_value -= loan_payment;
    }
    printf("'%.2f'", loan_debt_total);
    return 0;
}
