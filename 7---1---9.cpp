#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void input_check(int* input) {
    while (scanf_s("%d", input) != 1 || getchar() != '\n' || *input <= 0) {
        printf("\nОшибка: требуется ввести целое положительное число число: ");
        rewind(stdin);
    }
}

void string_input(char **string, int *size) {
    int input;
    int capacity = 10;
    
    *string = malloc(capacity * sizeof(char));
    if (*string == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    while ((input = getchar()) != '\n' && input != EOF) {
        if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || input == ' ') {
            if (*size >= capacity - 1) {
                capacity *= 2;
                char* string2 = realloc(*string, capacity * sizeof(char));
                if (string2 == NULL) {
                    printf("Ошибка перераспределения памяти\n");
                    exit(1);
                }
                *string = string2;
            }
            (*string)[(*size)++] = (char)input;           
        }
    }
    (*string)[*size] = '\0';
}

void delete_words(char** string, int size, int max_word_size) {
    int new_size = 0;
    char* new_string = malloc((size + 1) * sizeof(char));
    if (new_string == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    int word_size = 0;
    int i = 0;

    while (i < size) {
        if ((*string)[i] == ' ') {
            new_string[new_size++] = ' ';
            i++;
        }
        else if ((*string)[i] != ' ') {
            word_size = 0;

            for (int j = i; (*string)[j] != ' ' && j < size; j++) {
                word_size++;
            }

            if (word_size > max_word_size) {
                i += word_size;
            }

            else {
                for (int k = i; k < i + word_size; k++) {
                    new_string[new_size++] = (*string)[k];
                }
                i += word_size;
            }
        }
    }

    new_string[new_size] = '\0';

    printf("\nНовая строка с удаленными словами, больше %d букв: ", max_word_size);
    puts(new_string);

    free(new_string);
}

int main() {
    setlocale(LC_ALL, "Rus");

    char* string;
    int size = 0;
    int max_word_size;

    printf("Введите строку. Любые символы, кроме букв латинского алфавита и пробелов, будут исключены (Enter для завершения ввода):\n\n\t");
    string_input(&string, &size);

    printf("\nВведенная строка: ");
    puts(string);

    printf("\nВведите максимальное количество 'k' букв в слове: ");
    input_check(&max_word_size);
    
    delete_words(&string, size, max_word_size);

    free(string);

    return 0;
}