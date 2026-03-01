#include <iostream>
#include <cstdlib>
#include <ctime>

// Lab 10
void compressor(int *array, int N, int *result){
    for (int i = 0; i < 18; i++){
        result[i] = 0;
    }
    for (int i = 0; i < N; i++){
        result[array[i]]++;
    }
}

void decompressor(int *source, int *result, int N){
    int index = 0;
    for (int i = 0; i < 18; i++){
       for (int j = 0; j < source[i]; j++) {
            result[index++] = i;
       }
    }
}

void array_generator(int* arr, int N){
    srand(time(NULL));
    int temp, new_rand, temp_index;
    for (int i = 0; i < N; i++) {
        new_rand = rand() % 18;
        arr[i] = new_rand;
        temp_index = i;
        while ((temp_index > 0 && temp_index < N) && (arr[temp_index] < arr[temp_index - 1])) {
            temp = arr[temp_index];
            arr[temp_index] = arr[temp_index - 1];
            arr[temp_index - 1] = temp;
            temp_index--;
        }

    }
}

int main() {
    int array_size, *array, *compressed_array, *decompressed_array;
    int size_source, size_decompressed, size_compressed;
    if (!(std::cin >> array_size)){
        return 1;
    }
    if (array_size < 1000){ 
        printf("Size must be > 1000");
        return 1;
    }
    array = new int[array_size]; compressed_array = new int[18]; decompressed_array = new int[array_size];

    array_generator(array, array_size);
    size_source = sizeof(array[0])*array_size;
    /*for (int i = 0; i < array_size; i++) {
        std::cout << array[i] << " ";
    } printf("\n");*/

    compressor(array, array_size, compressed_array);
    for (int i = 0; i < 18; i++) {
        std::cout << compressed_array[i] << " ";
    } printf("\n");
    size_compressed = sizeof(compressed_array[0])*18;

    decompressor(compressed_array, decompressed_array, array_size);
    /*for (int i = 0; i < array_size; i++) {
        std::cout << decompressed_array[i] << " ";
    } printf("\n");*/
    size_decompressed = sizeof(decompressed_array[0])*array_size;

    printf("Original: %d, Compressed: %d, Decompressed: %d. \n Memory saved: %d \n", size_source,size_compressed,size_decompressed, size_source-size_compressed);

    delete[] array; delete[] compressed_array; delete[] decompressed_array;

    return 0;
}
