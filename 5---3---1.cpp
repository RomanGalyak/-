#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void input_check(int *input) {
    printf("Введите размерность стороны квадратного массива: ");
    while (scanf_s("%d", input) != 1 || getchar() != '\n' || *input <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число число: ");
        rewind(stdin);
    }
}

void malloc_2d(int*** array, int side) {
    *array = malloc(side * sizeof(int*));
    if (*array == NULL) {
        printf("Ошибка выделения памяти для 2D массива.\n");
        exit(1);
    }
}

void random_fill(int** array, int side) {
    srand(time(NULL));
    for (int i = 0; i < side; i++) {
        array[i] = malloc(side * sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j < side; j++) {
            array[i][j] = -10 + rand() % 21;
        }
    }
}

void print_array(int** array, int side) {
    printf("Ваш массив:\n");
    int k = 0;
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (j == k) {
                printf("\033[31m%4d\033[37m ", array[i][j]);
            }
            else
                printf("%4d ", array[i][j]);
        }
        printf("\n\n");
        k++;
    }
}

void max_elem(int** array, int side, int *elem) {
    int n = side;
    *elem = array[1][0];
    for (int i = 0; i != side; i++) {
        for (int j = 0; j != side - n; j++) {
            *elem = (*elem < array[i][j]) ? *elem : array[i][j];
        }
        n--;
    }
}

void manual_fill(int** array, int side) {
    for (int i = 0; i != side; i++) {
        array[i] = malloc(side * sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(1);
        }

        for (int j = 0; j != side; j++) {
            printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
            while (scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n' || array[i][j] <= 0) {
                printf("\nОшибка: требуется ввести целое число: ");
                rewind(stdin);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");

    int side;
    int elem;
    int choice;

    input_check(&side);

    int** array = NULL;
    malloc_2d(&array, side);

    printf("Введите 'a', если хотите заполнить массив автоматически, любую другую клавишу для заполнения вручную: ");
    choice = getchar();
    switch (choice) {
    case 'a':
        random_fill(array, side);
        break;

    default:
        manual_fill(array, side);
        break;
    }

    print_array(array, side);

    max_elem(array, side, &elem);

    printf("Наименьший элемент под главной диагональю: %d", elem);
}