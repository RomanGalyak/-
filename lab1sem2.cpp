#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <io.h>

void write_numbers_to_file(const char* filename, int* numbers, int count) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Невозможноо открыть файл для записи.");
        exit(1);
    }

    fwrite(numbers, sizeof(int), count, file);
    fclose(file);
}

void read_numbers_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Невозможно открыть фай для чтения.");
        exit(1);
    }

    int number;
    printf("Содержимое файла:\n");
    while (fread(&number, sizeof(int), 1, file)) {
        printf("%d ", number);
    }
    printf("\n");

    fclose(file);
}

int count_less_than(const char* filename, int threshold) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Невозможно открыть фай для чтения.");
        exit(1);
    }

    int number, count = 0;
    while (fread(&number, sizeof(int), 1, file)) {
        if (number < threshold) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void remove_less_than(const char* filename, int threshold) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Невозможно открыть фай для чтения.");
        exit(1);
    }

    FILE* tempFile = fopen("temp.bin", "wb");
    if (!tempFile) {
        perror("Невозможно создать временный файл.");
        fclose(file);
        exit(1);
    }

    int number;
    while (fread(&number, sizeof(int), 1, file) == 1) {
        if (number >= threshold) {
            fwrite(&number, sizeof(int), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0) {
        perror("Невозможно удалить изначальный файл.");
        exit(1);
    }

    if (rename("temp.bin", filename) != 0) {
        perror("Невозможно переименовать временный файл.");
        exit(1);
    }
}

void sort_file_descending(const char* filename) {
    FILE* file = fopen(filename, "r+b");
    if (!file) {
        perror("Невозможно открыть файл для чтения/записи.");
        exit(1);

    }

    int number, temp;
    long pos1, pos2;

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    int count = fileSize / sizeof(int);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            pos1 = j * sizeof(int);
            pos2 = (j + 1) * sizeof(int);
            fseek(file, pos1, SEEK_SET);
            fread(&number, sizeof(int), 1, file);
            fseek(file, pos2, SEEK_SET);
            fread(&temp, sizeof(int), 1, file);

            if (number < temp) {
                fseek(file, pos1, SEEK_SET);
                fwrite(&temp, sizeof(int), 1, file);
                fseek(file, pos2, SEEK_SET);
                fwrite(&number, sizeof(int), 1, file);
            }
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        printf_s("Недостаточно аргументов.");
        return 1;
    }

    const char* filename = argv[1];
    int count = argc - 2;
    int* numbers = malloc(count * sizeof(int));

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 2]);
    }

    write_numbers_to_file(filename, numbers, count);
    read_numbers_from_file(filename);
    int threshold;
    printf("Введите пороговое значение: ");
    scanf_s("%d", &threshold);

    int numCount = count_less_than(filename, threshold);
    printf("Количество элементов меньше %d: %d\n", threshold, numCount);

    removeLessThan(filename, threshold);
    printf("Элементы меньше %d удалены.\n", threshold);
    read_numbers_from_file(filename);

    sort_file_descending(filename);
    printf("Файл отсортирован по убыванию.\n");
    read_numbers_from_file(filename);

    free(numbers);
    return 0;
}