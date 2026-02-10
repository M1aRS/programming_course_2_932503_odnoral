#include <iostream>
#include <math.h>

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
        return 0;
    }
    else if ((x0 <= 0) || (x0 > 4)) {
        std::cout << "Your point must be in these borders (0;4]";
        return 1;
    }
    double delta = (4 - x0) / 10;
    for (double i = x0; i <= 4; i = i + delta) {
        std::cout << i << ' ' << sin(i) / i << std::endl;
    }
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
    long long fib_sum = 0;
    long long fib_prev = 1; long long fib_post_prev = 0;
    long long temp;
    int fib_count = 1;
    while (max_value >= fib_sum) {
        temp = fib_prev;
        fib_prev = fib_prev + fib_post_prev;
        fib_post_prev = temp;
        fib_sum += fib_prev;
        fib_count++;
        //std::cout << fib_sum << " - current sum; var -" << fib_prev << std::endl;
    }
    printf("Number of elements: %d  Sum of elements: %x \n",fib_count, fib_sum);
    //std::cout << fib_count << " " << fib_sum;

    // TODO: вычислите N и S (S <= MAX) и выведите результаты.
    return 0;
}
