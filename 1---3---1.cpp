#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void input_check(int *var) {
    while (scanf_s("%d", var) != 1 || getchar() != '\n' || *var <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число: ");
        rewind(stdin);
    }
}

void malloc_1d(int **array, int size) {
    *array = (int*)malloc(size * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для 1D массива.\n");
        exit(1);
    }
}

void f_fill(int size, int *array, errno_t err, FILE *f) {
    if (err == 0) {
        for (int i = 0; i < size; i++) {
            fprintf(f, "%d\n", array[i]);
        }
        fclose(f);
    }
    else {
        printf("Ошибка открытия файла.\n");
    }
}

void err_check(errno_t err, int *numbers) {
    if (err != 0) {
        printf("Ошибка открытия файла для чтения.\n");
        free(numbers);
        exit(1);
    }
}

int comparison(FILE *f, int comp) {
    int number;
    int amount = 0;
    while (fscanf_s(f, "%d", &number) == 1) {
        if (number < comp) {
            amount++;
        }
    }
    return amount;
}

void fill_new(int *array, int *new_array, int size, int comp, int *new_size) {
    for (int i = 0; i < size; i++) {
        if (array[i] > comp) {
            new_array[*new_size] = array[i]; 
            (*new_size)++; 
        }
    }
}

void array_print(int *array, int size) {
    for (int i = 0; i < size; i++)
        printf_s("%d", array[i]);
}

void bubble_sort(int* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
int main() {
    setlocale(LC_ALL, "Rus");

    int size;
    int* numbers = NULL;

    printf("Введите желаемое количество чисел: ");
    input_check(&size);

    malloc_1d(&numbers, size);

    printf("Введите %d целых чисел:\n", size);
    
    for (int i = 0; i < size; i++) {
        input_check(&numbers[i]);
    }

    FILE* f = NULL;
    errno_t err = fopen_s(&f, "file.txt", "w"); 

    f_fill(size, numbers, err, f);

    int comp;
    printf_s("Введите число для сравнения: ");
    input_check(&comp);

    err = fopen_s(&f, "file.txt", "r");
    err_check(err, numbers);

    printf("Количество чисел меньше %d: %d\n", comp, comparison(f, comp));

    int* new_numbers = NULL;
    int new_size = 0;
    malloc_1d(&new_numbers, size);

    fill_new(numbers, new_numbers, size, comp, &new_size);
    array_print(new_numbers, new_size);

    bubble_sort(numbers, size);

    printf("Отсортированные числа:\n");
    array_print(numbers, size);

    free(numbers); 
    free(new_numbers); 
    return 0;
}