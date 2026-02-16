#include <iostream>
#include <cstdlib>
#include <ctime>

// Lab 08
// TODO: реализуйте решение по заданию в labs/lab08_pointers_arrays/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке
void zadanie2_func(int& x, int* y) {
    x *= 2;
    *y *= 3;
}

int main() {
    srand(time(NULL));
    // Упражнение 1: объяснить использование типов/переменных в коде (без ввода).
    // TODO: при необходимости вывести пояснения/результаты.
    printf("n = 53.14, m = 456\n");
    // Упражнение 2: найти ошибки в коде (без ввода).
    // TODO: при необходимости вывести пояснения/результаты.
    int a, b;
    if (!(std::cin >> a >> b)) {
        std::cout << "Error";
        return 1;
    }
    zadanie2_func(a, &b);
    std::cout << a << "\t" << b << std::endl;
    // Упражнение 3: заполнить массивы (10 элементов) разными способами.
    // TODO: реализуйте 4 варианта заполнения и выведите 10 значений для каждого.
    const int zad3_length = 10;
    int zad3_arr_static[zad3_length];
    int *zad3_arr_dyn; zad3_arr_dyn = new int[zad3_length];
    int temp, new_rand, temp_index;
    for (int i = 0; i < zad3_length; i++) {
        new_rand = rand() % 100;
        printf("%d ", new_rand);
        zad3_arr_static[i] = new_rand;
        temp_index = i;
            //std::cout << zad3_arr_static[i] << " ";
        while ((temp_index > 0 && temp_index < zad3_length) && (zad3_arr_static[temp_index] < zad3_arr_static[temp_index - 1])) {
            temp = zad3_arr_static[temp_index];
            zad3_arr_static[temp_index] = zad3_arr_static[temp_index - 1];
            zad3_arr_static[temp_index - 1] = temp;
            temp_index--;
            }
        
    }
    printf("\n");
    for (int i = 0; i < 10; i++) std::cout << zad3_arr_static[i] << " ";

    // Упражнение 4: линейный самоадресуемый список из 10 элементов.
    // TODO: сформируйте список и выведите элементы по порядку.
    return 0;
}
