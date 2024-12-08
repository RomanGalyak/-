#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void input_check(int* input) {
    while (scanf_s("%d", input) != 1 || getchar() != '\n' || *input <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число число: ");
        rewind(stdin);
    }
}

void malloc_int(int** array, int size) {
    *array = malloc(size * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для массива.\n");
        exit(1);
    }
}

void print_array_1d(int* array, int size, int last_pos_i) {
    printf("|");
    for (int i = 0; i != size; i++) {
        if (i % 2 != 0 && i != 0 && i != last_pos_i)
            printf("\033[31m%3d\033[0m  |", array[i]);
        else if (i == last_pos_i && i != 0)
            printf("\033[36m%3d\033[0m  |", array[i]);
        else
            printf("%3d  |", array[i]);
    }
    printf("\n");
}

void random_fill_1d(int *array, int size) {
    srand(time(NULL));
    for (int i = 0; i != size; i++)
        array[i] = -9 + rand() % 19;
}

void manual_fill(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Введите элемент [%d]: ", i + 1);
        while (scanf_s("%d", &array[i]) != 1 || getchar() != '\n') {
            printf("\nОшибка: требуется ввести целое число: ");
            rewind(stdin);
        }
    }
}

void last_pos_index(int *array, int size, int *last_pos_i, int *last_pos) {
    for (int i = size - 1; i >= 0; i--) {
        if (array[i] > 0 && i % 2 != 0) {
            *last_pos_i = i;
            *last_pos = array[i];
            break;
        }
    }
}

void shell_sort_odd(int *array, int last_pos_i) {
    for (int gap = (last_pos_i + 1) / 2; gap != 2; gap /= 2) {
        if (gap % 2 != 0)
            gap += 1;
        for (int i = 1; i + gap <= last_pos_i; i += 2) {
            int temp;
            if (array[i] > array[i + gap]) {
                temp = array[i];
                array[i] = array[i + gap];
                array[i + gap] = temp;
            }
        }


        for (int i = 3; i <= last_pos_i; i += 2) {
            int var = array[i];
            int j = i - 2;
            while (j >= 0 && array[j] > var) {
                array[j + 2] = array[j];
                j -= 2;
            }
            array[j + 2] = var;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    int size;
    int* array;
    char choice;
    int last_pos_i = -1;
    int last_pos = 0;

    while (1) {
        printf("Введите количество элементов массива: ");
        input_check(&size);
        malloc_int(&array, size);

        printf("Введите 'a', если хотите заполнить массив автоматически, любую другую клавишу для заполнения вручную: ");
        choice = getchar();
        switch (choice) {
        case 'a':
            random_fill_1d(array, size);
            break;

        default:
            manual_fill(array, size);
            break;
        }

        last_pos_index(array, size, &last_pos_i, &last_pos);

        if (last_pos_i != -1) {
            printf("Ваш массив:\n ");
            print_array_1d(array, size, last_pos_i);
            shell_sort_odd(array, last_pos_i);
            printf("Ваш отсортированный массив:\n ");
            print_array_1d(array, size, last_pos_i);
        }
        else
            printf("Ошибка: нет положительных элементов на нечетных индексах.\n");
    }

    return 0;
}