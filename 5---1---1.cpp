#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void input_check(int *a, int *b) { //input_size
    printf("Введите нижнюю границу отрезка [a;b] (от 1 до 99): ");
    while (scanf_s("%d", a) != 1 || getchar() != '\n' || *a < 1 || *a > 99) {
        printf("\nОшибка: требуется ввести целое число от 1 до 99. Введите нижнюю границу отрезка [a;b] (от 1 до 99): ");
        rewind(stdin);
    }
    printf("Введите  верхнюю границу отрезка [a;b] (от 1 до 99): ");
    while (scanf_s("%d", b) != 1 || getchar() != '\n' || *b < 1 || *b > 99 || *a > *b || *a == *b) {
        printf("\nОшибка: требуется ввести целое число от 1 до 99, 'b' долбжно быть больше 'a', 'b' не должно равняться 'a'.\nВведите верхнюю границу отрезка [a;b] (от 1 до 99): ");
        rewind(stdin);
    }
}

void fillEvenNumbers(int **array, int *size) {
	*size = 49; //Четные числа от 2 до 98
	*array = malloc(*size * sizeof(int));
	if (*array == NULL) { //Ошибка если невозможно выделить память
		printf("Ошибка выделения памяти.\n");
		exit(1);
	}

	for (int i = 0; i < *size; i++) {
		(*array)[i] = (i + 1) * 2; //Заполнение четными числами
	}
}

void removeOutOfRange(int **array, int *size, int a, int b) {
    int new_size = 0;
    for (int i = 0; i < *size; i++) {
        if ((*array)[i] >= a && (*array)[i] <= b) {
            new_size++;
        }
    }

    int *new_array = malloc(new_size * sizeof(int));
    if (new_array == NULL) {
        printf("Ошибка выделения памяти.\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < *size; i++) {
        if ((*array)[i] >= a && (*array)[i] <= b) {
            new_array[j++] = (*array)[i];
        }
    }

    free(*array); //Освобождение старого массива
    *array = new_array; //Указатель на новый массив
    *size = new_size; //Обновление размера
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
	setlocale(LC_ALL, "Rus");

	int *array = NULL;
	int size = 0;

    fillEvenNumbers(&array, &size);
    printf("Четные числа от 1 до 99:\n");
    printArray(array, size);

    int a, b;
    input_check(&a, &b);

    removeOutOfRange(&array, &size, a, b); 
    printf("Четные числа в отрезке [%d;%d]:\n", a, b);
    printArray(array, size);

    free(array); // Освобождаем память
    return 0;
}