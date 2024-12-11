#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void string_input(char** string, int* size) {
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

void delete_letter (char** string, int size, char letter) {
    char* new_string = malloc((size + 1) * sizeof(char));
    if (new_string == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    int enter = 0;
    int new_size = 0;
    
    for (int i = 0; i < size; i++) {
        if ((*string)[i] == letter) {
            enter++;
            if (enter % 2 == 0) {
                enter = 0;
                continue;
            }
            else
                new_string[new_size++] = (*string)[i];
        }
        else
            new_string[new_size++] = (*string)[i];
    }

    new_string[new_size] = '\0';

    printf("\nНовая строка с удалением кождого второго вхождения буквы %c: ", letter);
    puts(new_string);

    free(new_string);
}

int main() {
    setlocale(LC_ALL, "Rus");

    char* string;
    int size = 0;
    char letter = 'c';

    printf("Введите строку. Любые символы, кроме букв латинского алфавита и пробелов, будут исключены (Enter для завершения ввода):\n\n\t");
    string_input(&string, &size);

    printf("\nВведенная строка: ");
    puts(string);

    delete_letter(&string, size, letter);

    free(string);

    return 0;
}