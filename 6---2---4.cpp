#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void input_check(int* input) {
    while (scanf_s("%d", input) != 1 || getchar() != '\n' || *input <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число число: ");
        rewind(stdin);
    }
}

void random_fill(int** matrix, int strings, int columns) {
    srand(time(NULL));
    for (int i = 0; i < strings; i++) {
        matrix[i] = malloc(columns * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j < columns; j++) {
            matrix[i][j] = -10 + rand() % 21;
        }
    }
}

void manual_fill(int** matrix, int strings, int columns) {
    for (int i = 0; i != strings; i++) {
        matrix[i] = malloc(columns * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j != columns; j++) {
            printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
            while (scanf_s("%d", &matrix[i][j]) != 1 || getchar() != '\n' || matrix[i][j] <= 0) {
                printf("\nОшибка: требуется ввести целое число: ");
                rewind(stdin);
            }
        }
    }
}

void count_even(int** matrix, int strings, int columns, int *even_counter) {
    int even_sum = 0;
    for (int j = 0; j != columns; j++) {
        for (int i = 0; i != strings; i++) {
            if (matrix[i][j] % 2 == 0) {
                even_sum += matrix[i][j];
            }
        }
        even_counter[j] = even_sum;
        even_sum = 0;
    }
}

void merge(int array[], int positions[], int left, int mid, int right) {
    int i, j, k;
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int* left_array = malloc(size1 * sizeof(int));
    int* right_array = malloc(size2 * sizeof(int));
    int* left_array1 = malloc(size1 * sizeof(int));
    int* right_array1 = malloc(size2 * sizeof(int));

    if (left_array == NULL || right_array == NULL || left_array1 == NULL || right_array1 == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    for (i = 0; i < size1; i++) {
        left_array[i] = array[left + i];
        left_array1[i] = positions[left + i];
    }
    for (j = 0; j < size2; j++) {
        right_array[j] = array[mid + 1 + j];
        right_array1[j] = positions[mid + 1 + j];
    }

    i = 0; 
    j = 0; 
    k = left; 

    while (i < size1 && j < size2) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            positions[k] = left_array1[i];
            i++;
        }
        else {
            array[k] = right_array[j];
            positions[k] = right_array1[j];
            j++;
        }
        k++;
    }

    while (i < size1) {
        array[k] = left_array[i];
        positions[k] = left_array1[i];
        i++;
        k++;
    }

    while (j < size2) {
        array[k] = right_array[j];
        positions[k] = right_array1[j];
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
    free(left_array1);
    free(right_array1);
}

void merge_sort(int** array, int* positions, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(array, positions, left, mid);
        merge_sort(array, positions, mid + 1, right);
        merge(array, positions, left, mid, right);
    }
}

void malloc_2d(int*** array, int strings) {
    *array = malloc(strings * sizeof(int*));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для 2D массива.\n");
        exit(1);
    }
}

void malloc_int(int** array, int size) {
    *array = malloc(size * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для массива.\n");
        exit(1);
    }
}

void print_array(int** matrix, int strings, int columns) {
    for (int i = 0; i < strings; i++) {
        printf("|");
        for (int j = 0; j < columns; j++) {
                printf("%4d   |", matrix[i][j]);
        }
        printf("\n\n");
    }
}

void fill_positions(int* positions, int size) {
    for (int i = 0; i < size; i++)
        positions[i] = i;
}

void print_sorted_array(int** matrix, int* positions, int strings, int columns) {
    printf("Отсортированный массив:\n");
    for (int i = 0; i < strings; i++) {  
        printf("|");
        for (int j = 0; j < strings; j++) {
            int k = positions[j];
            printf("%4d   |", matrix[i][k]); 
        }
        printf("\n\n");
    }
}

void CHECK(int columns, int *even_counter, int *positions) {
    printf("\n");
    for (int i = 0; i != columns; i++) {
        printf("%4d ", even_counter[i]);
    }
    printf("\n");
    for (int i = 0; i != columns; i++) {
        printf("%4d ", positions[i] + 1);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");

    int** matrix;
    int strings;
    int columns;
    char choice;
    int* even_counter;
    int* positions;

    printf("Введите кол-во строк матрицы: ");
    input_check(&strings);
    printf("Введите кол-во столбцов матрицы: ");
    input_check(&columns);

    malloc_2d(&matrix, strings);
    malloc_int(&even_counter, columns);
    malloc_int(&positions, columns);
    fill_positions(positions, columns);

    printf("Введите 'a', если хотите заполнить массив автоматически, нажмите любую другую клавишу для заполнения вручную: ");
    choice = getchar();
    switch (choice) {
    case 'a':
        random_fill(matrix, strings, columns);
        break;

    default:
        manual_fill(matrix, strings, columns);
        break;
    }

    printf("Ваш массив:\n");
    print_array(matrix, strings, columns);

    count_even (matrix, strings, columns, even_counter);

    CHECK(columns, even_counter, positions);

    merge_sort(even_counter, positions, 0, columns - 1);

    CHECK(columns, even_counter, positions);

    printf("Ваш отсортированный массив:\n");
    print_sorted_array(matrix, positions, strings, columns);

    return 0;
}