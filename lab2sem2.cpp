#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

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

void swap_last_two(const char* filename) {
    FILE* file;
    int count = 0, num;

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

    int temp = numbers[count - 1];
    numbers[count - 1] = numbers[count - 2];
    numbers[count - 2] = temp;

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

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        fprintf(stderr, "Недостаточно аргументов.\n", argv[0]);
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
