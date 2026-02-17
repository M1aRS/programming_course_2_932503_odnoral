#include <iostream>
#include <cstdlib>
#include <ctime>

struct Node
{
    int data;
    Node* prev;
    Node* next;
};
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

void zadanie3_arr_gen(int *arr, int N) {
    int temp, new_rand, temp_index;
    for (int i = 0; i < N; i++) {
        new_rand = rand() % 100;
        //printf("%d ", new_rand);
        arr[i] = new_rand;
        temp_index = i;
        //std::cout << zad3_arr_static[i] << " ";
        while ((temp_index > 0 && temp_index < N) && (arr[temp_index] < arr[temp_index - 1])) {
            temp = arr[temp_index];
            arr[temp_index] = arr[temp_index - 1];
            arr[temp_index - 1] = temp;
            temp_index--;
        }

    }
    //printf("\n");
}

int* zadanie3_arr_merge(int* arr1, int* arr2, int size1, int size2) {
    int i = 0; int j = 0; int k = 0;
    int sizeResult = size1 + size2;
    int* result; result = new int[sizeResult];
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            result[k++] = arr1[i++];
        }
        else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) result[k++] = arr1[i++];
    while (j < size2) result[k++] = arr2[j++];
    return result;
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
    for (int i = 0; i < zad3_length; i++) { 
        zad3_arr_static[i] = i * i; 
        std::cout << zad3_arr_static[i] << '\t';
    }
    printf("\n");

    int zad3_arr_static_ptr[zad3_length];
    for (int i = 0; i < zad3_length; i++) {
        *(zad3_arr_static_ptr + i) = i * i; 
        std::cout << zad3_arr_static_ptr[i] << '\t';
    }
    printf("\n");

    int *zad3_arr_dyn; zad3_arr_dyn = new int[zad3_length];
    for (int i = 0; i < zad3_length; i++) {
        zad3_arr_dyn[i] = i * i;
        std::cout << zad3_arr_dyn[i] << '\t';
    }
    printf("\n");

    int* zad3_arr_dyn_ptr; zad3_arr_dyn_ptr = new int[zad3_length];
    for (int i = 0; i < zad3_length; i++) {*
        (zad3_arr_dyn_ptr + i) = i * i;
        std::cout << zad3_arr_dyn_ptr[i] << '\t';
    }
    printf("\n");

    delete[] zad3_arr_dyn; delete[] zad3_arr_dyn_ptr;

    int zad3_N1, zad3_N2;
    if (!(std::cin >> zad3_N1 >> zad3_N2)) return 1;
    int *zad32_arr1; int* zad32_arr2; int* zad32_arr3;
    zad32_arr1 = new int[zad3_N1]; zad32_arr2 = new int[zad3_N2];

    zadanie3_arr_gen(zad32_arr1, zad3_N1);
    for (int i = 0; i < zad3_N1; i++) std::cout << zad32_arr1[i] << " ";
    printf("\n");
    zadanie3_arr_gen(zad32_arr2, zad3_N2);
    for (int i = 0; i < zad3_N2; i++) std::cout << zad32_arr2[i] << " ";
    printf("\n");
    zad32_arr3 = zadanie3_arr_merge(zad32_arr1, zad32_arr2, zad3_N1, zad3_N2);
    for (int i = 0; i < zad3_N2 + zad3_N1; i++) std::cout << zad32_arr3[i] << " ";
    printf("\n");
    delete[]zad32_arr1; delete[]zad32_arr2; delete[]zad32_arr3;

    // Упражнение 4: линейный самоадресуемый список из 10 элементов.
    // TODO: сформируйте список и выведите элементы по порядку.
    Node* head = nullptr; Node* last = nullptr;

    for (int i = 1; i <= 10; i++) {
        Node* newNode = new Node;
        newNode->data = i*10;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            newNode->prev = nullptr;
        }
        else {
            last->next = newNode;
            newNode->prev = last;
        }
        last = newNode;
    }
    Node* aasd = head;
    while (aasd != nullptr) {
        std::cout << aasd->data << " ";
        aasd = aasd->next;
    }

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}