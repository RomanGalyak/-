#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Функция для записи чисел в файл
void write_numbers_to_file(const char* filename, int count, int* numbers) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);
}

// Функция для отображения содержимого файла
void display_file(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    int num;
    printf("Содержимое файла:\n");
    while (fscanf_s(file, "%d", &num) == 1) {
        printf("%d\n", num);
    }
    fclose(file);
}

// Функция для суммирования чисел в файле
int sum_numbers(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    int sum = 0, num;
    while (fscanf_s(file, "%d", &num) == 1) {
        sum += num;
    }
    fclose(file);
    return sum;
}

// Функция для обмена двух последних чисел в файле
void swap_last_two(const char* filename) {
    FILE* file;
    int count = 0, num;

    // Определяем количество чисел в файле
    if (fopen_s(&file, filename, "r") != 0) {
        perror("Ошибка открытия файла");
        exit(1);
    }
    while (fscanf_s(file, "%d", &num) == 1) {
        count++;
    }
    fclose(file);

    if (count < 2) {
        printf("Недостаточно чисел для обмена.\n");
        return;
    }

    // Читаем все числа из файла в массив
    int* numbers = (int*)malloc(count * sizeof(int));
    if (numbers == NULL) {
        perror("Ошибка выделения памяти");
        exit(1);
    }
    if (fopen_s(&file, filename, "r") != 0) {
        perror("Ошибка открытия файла");
        free(numbers);
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        if (fscanf_s(file, "%d", &numbers[i]) != 1) {
            perror("Ошибка чтения данных");
            free(numbers);
            fclose(file);
            exit(1);
        }
    }
    fclose(file);

    // Меняем местами последние два числа
    int temp = numbers[count - 1];
    numbers[count - 1] = numbers[count - 2];
    numbers[count - 2] = temp;

    // Записываем обновлённые данные обратно в файл
    if (fopen_s(&file, filename, "w") != 0) {
        perror("Ошибка открытия файла");
        free(numbers);
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", numbers[i]);
    }
    fclose(file);
    free(numbers);
}

// Основная функция
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        fprintf(stderr, "Использование: %s <имя файла> <числа ...>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    int count = argc - 2;
    int* numbers = (int*)malloc(count * sizeof(int));
    if (numbers == NULL) {
        perror("Ошибка выделения памяти");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 2]);
    }

    write_numbers_to_file(filename, count, numbers);
    display_file(filename);

    int total_sum = sum_numbers(filename);
    printf("Сумма чисел в файле: %d\n", total_sum);

    swap_last_two(filename);
    display_file(filename);

    free(numbers);
    return 0;
}
