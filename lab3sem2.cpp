#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TITLE_LENGTH 100
#define MAX_DATE_LENGTH 11
#define INITIAL_CAPACITY 10

// Структура для хранения информации о сериале
typedef struct {
    int episodes;
    char* title;
    char release_date[MAX_DATE_LENGTH];
    int seasons;
} Series;

// Функция для создания нового сериала
Series create_series(int episodes, const char* title, const char* release_date, int seasons) {
    Series series;
    series.episodes = episodes;

    size_t title_len = strnlen_s(title, MAX_TITLE_LENGTH) + 1;
    series.title = (char*)malloc(title_len);
    if (!series.title) {
        fprintf_s(stderr, "Ошибка выделения памяти.\n");
        exit(EXIT_FAILURE);
    }
    strcpy_s(series.title, title_len, title);

    strncpy_s(series.release_date, MAX_DATE_LENGTH, release_date, _TRUNCATE);
    series.seasons = seasons;
    return series;
}

// Функция для освобождения памяти сериалов
void free_series(Series* series) {
    free(series->title);
}

// Функция для вывода информации о сериале
void print_series(const Series* series) {
    printf_s("Название: %s, Эпизоды: %d, Дата выхода: %s, Сезоны: %d\n",
        series->title, series->episodes, series->release_date, series->seasons);
}

// Функция для поиска сериалов с количеством серий меньше заданного
void find_series_with_less_episodes(Series* series_array, int count, int max_episodes) {
    printf_s("Сериалы к количеством эпизодов меньше %d:\n", max_episodes);
    for (int i = 0; i < count; i++) {
        if (series_array[i].episodes < max_episodes) {
            print_series(&series_array[i]);
        }
    }
}

// Функция для удаления сериалов по названию
int remove_series_by_title(Series** series_array, int* count, const char* title_to_remove) {
    int removed_count = 0;
    for (int i = 0; i < *count; i++) {
        if (strcmp((*series_array)[i].title, title_to_remove) == 0) {
            free_series(&(*series_array)[i]);
            removed_count++;
        }
        else if (removed_count > 0) {
            (*series_array)[i - removed_count] = (*series_array)[i];
        }
    }
    *count -= removed_count;
    return removed_count;
}

// Функция для добавления сериала в массив
void add_series(Series** series_array, int* count, int* capacity, Series new_series) {
    if (*count >= *capacity) {
        *capacity *= 2;
        Series* temp = (Series*)realloc(*series_array, (*capacity) * sizeof(Series));
        if (!temp) {
            fprintf_s(stderr, "Ошибка выделения памяти.\n");
            exit(EXIT_FAILURE);
        }
        *series_array = temp;
    }
    (*series_array)[(*count)++] = new_series;
}

// Функция для вывода всех сериалов
void print_all_series(Series* series_array, int count) {
    if (count == 0) {
        printf_s("Не найдено ни олного сериала.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        print_series(&series_array[i]);
    }
}

// Функция для получения ввода от пользователя
void get_series_input(Series* series) {
    printf_s("Введите количество эпизодов: ");
    scanf_s("%d", &series->episodes);
    while (getchar() != '\n'); // Очистка буфера ввода

    free(series->title);
    series->title = (char*)malloc(MAX_TITLE_LENGTH);
    if (!series->title) {
        fprintf_s(stderr, "Ошибка выделения памяти.\n");
        exit(EXIT_FAILURE);
    }

    printf_s("ВВедите название: ");
    gets_s(series->title, MAX_TITLE_LENGTH);

    printf_s("Введите дату выхода: ");
    scanf_s("%10s", series->release_date, (unsigned)_countof(series->release_date));
    while (getchar() != '\n'); // Очистка буфера ввода

    printf_s("Введите кол-во сезонов: ");
    scanf_s("%d", &series->seasons);
    while (getchar() != '\n'); // Очистка буфера ввода
}

// Функция для нахождения числа в 8 раз меньше заданного
void eight_times_less() {
    int number;
    printf_s("Введите целое число: ");
    scanf_s("%d", &number);
    while (getchar() != '\n'); // Очистка буфера ввода
    int result = (int)(number >> 3);
    printf_s("Число в 8 раз меньше чем %d: %d\n", number, result);
}

void display_menu() {
    printf_s("\nМеню:\n");
    printf_s("1. Добавить сериал\n");
    printf_s("2. Просмотреть список сериалов\n");
    printf_s("3. Найти сериал по числу эпизодов\n");
    printf_s("4. Удалить сериал по названию\n");
    printf_s("5. Выйти\n");
    printf_s("Выберите опцию: ");
}

int main() {
    setlocale(LC_ALL, "Rus");

    // Задача 1
    eight_times_less();

    // Задача 2
    Series* series_array = (Series*)malloc(INITIAL_CAPACITY * sizeof(Series));
    if (!series_array) {
        fprintf_s(stderr, "Ошибка выделения памяти.\n");
        return EXIT_FAILURE;
    }
    int count = 0, capacity = INITIAL_CAPACITY;
    int choice;

    do {
        display_menu();
        scanf_s("%d", &choice);
        while (getchar() != '\n'); // Очистка буфера ввода

        switch (choice) {
        case 1: {
            Series new_series = { 0 };
            get_series_input(&new_series);
            add_series(&series_array, &count, &capacity, new_series);
            break;
        }
        case 2:
            print_all_series(series_array, count);
            break;
        case 3: {
            int max_episodes;
            printf_s("Введите кол-во эпизодов: ");
            scanf_s("%d", &max_episodes);
            while (getchar() != '\n');
            find_series_with_less_episodes(series_array, count, max_episodes);
            break;
        }
        case 4: {
            char title_to_remove[MAX_TITLE_LENGTH];
            printf_s("Введите название сериала для удаления: ");
            gets_s(title_to_remove, MAX_TITLE_LENGTH);
            int removed = remove_series_by_title(&series_array, &count, title_to_remove);
            printf_s("Удалено %d сериалов.\n", removed);
            break;
        }
        case 5:
            printf_s("Выход...\n");
            break;
        default:
            printf_s("Недопустимый ввод. Попробуйте еще разок.\n");
        }
    } while (choice != 5);

    // Освобождение памяти
    for (int i = 0; i < count; i++) {
        free_series(&series_array[i]);
    }
    free(series_array);

    return 0;
}