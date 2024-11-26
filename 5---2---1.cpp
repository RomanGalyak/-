#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void input_check(int* input) { 
    printf("Введите количество строк массива: ");
    while (scanf_s("%d", input) != 1 || getchar() != '\n' ||  *input <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число число: ");
        rewind(stdin);
    }
}

void malloc_2d(int*** array, int strings) {
    *array = malloc(strings * sizeof(int*));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для 2D массива.\n");
        exit(1);
    }
}

void malloc_int(int** array, int strings) {
    *array = malloc(strings * sizeof(int));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для 2D массива.\n");
        exit(1);
    }
}

void manual_fill(int** array, int* colCount, int strings) {
    for (int i = 0; i < strings; i++) {
        printf("Введите количество элементов в строке %d: ", i + 1);
        while (scanf_s("%d", &colCount[i]) != 1 || getchar() != '\n' || colCount[i] <= 0) {
            printf("\nОшибка: требуется ввести целое положительное число число: ");
            rewind(stdin);
        }

        array[i] = calloc(colCount[i] + 1, sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j < colCount[i]; j++) {
            printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
            while (scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n' || array[i][j] <= 0) {
                printf("\nОшибка: требуется ввести целое число: ");
                rewind(stdin);
            }
        }
    }
}

void random_fill(int** array, int* colCount, int strings) {
    srand(time(NULL));
    for (int i = 0; i < strings; i++) {
        printf("Введите количество элементов в строке %d: ", i + 1);
        while (scanf_s("%d", &colCount[i]) != 1 || getchar() != '\n' || colCount[i] <= 0) {
            printf("\nОшибка: требуется ввести целое положительное число число: ");
            rewind(stdin);
        }

        array[i] = calloc(colCount[i] + 1, sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j < colCount[i]; j++) {
            array[i][j] = -10 + rand() % 21;
        }
    }
}

void print_array(int** array, int* colCount, int strings) {
    printf("Зубчатый массив:\n");
    for (int i = 0; i < strings; i++) {
        for (int j = 0; j < colCount[i] + 1; j++) {
            printf("%4d ", array[i][j]);
        }
        printf("\n");
    }
}

void free_memory(int** array, int* colCount, int strings) {
    free(colCount);
    for (int i = 0; i < strings; i++) {
        free(array[i]);
    }
    free(array);
}

int main() {
	setlocale(LC_ALL, "Rus");
	
    char choice;
    int strings;
    input_check(&strings);

    int** array = NULL;
    malloc_2d(&array, strings);
    
    int* colCount = NULL;
    malloc_int(&colCount, strings);

    printf("Введите 'a', если хотите заполнить массив автоматически, любую другую клавишу для заполнения вручную: ");
    choice = getchar();
    switch (choice) {
        case 'a': 
            random_fill(array, colCount, strings);
            break;
        
        default: 
            manual_fill(array, colCount, strings);
            break;
    }

    print_array(array, colCount, strings);
    free_memory(array, colCount, strings);

    return 0;
}
