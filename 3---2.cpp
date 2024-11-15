#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <time.h> 

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int array[100];
    int array2[100];
    char choice[2];
    int array_size = 0;

    while (1) {
        printf("Как вы хотите заполнить массив? Автоматически - 'a', вручную - 'b' ('q' для выхода): ");
        scanf_s("%s", choice, sizeof(choice));
        choice[0] = tolower(choice[0]);

        if (choice[0] == 'q' && choice[1] == '\0') {
            break;
        }

        else if ((choice[0] == 'a' && choice[1] == '\0') || (choice[0] == 'b' && choice[1] == '\0')) {
            if (choice[0] == 'a' && choice[1] == '\0') {
                printf("\nВыбрано автоматическое заполнение.\n\n");

                printf("Введите желаемое количество элементов массива: ");
                while (scanf_s("%d", &array_size) != 1 || getchar() != '\n' || array_size <= 0 || array_size > 50) {
                    printf("\nОшибка: требуется ввести целое положительное число от 1 до 50 во избежание возможного переполнения.\n\nВведите желаемое количество элементов массива: ");
                    rewind(stdin);
                }

                for (int i = 0; i != array_size; i++) {
                    array[i] = -10 + rand() % 21;
                }
            }
            else if (choice[0] == 'b' && choice[1] == '\0') {
                printf("\nВыбрано ручное заполнение.\n\n");


                printf("Введите желаемое количество элементов массива: ");
                while (scanf_s("%d", &array_size) != 1 || getchar() != '\n' || array_size <= 0 || array_size > 50) {
                    printf("\nОшибка: требуется ввести целое положительное число от 1 до 50 во избежание возможного переполнения.\n\nВведите желаемое количество элементов массива: ");
                    rewind(stdin);
                }

                printf("\n");
                for (int i = 0; i != array_size; i++) {
                    printf("Введите элемент массива(%d): ", i + 1);
                    while (scanf_s("%d", &array[i]) != 1 || getchar() != '\n') {
                        printf("Ошибка: требуется ввести целое число.\nВведите элемент массива(%d): ", i + 1);
                        rewind(stdin);
                    }
                }

            }

            int first_max = array[0];
            int first_max_i = 0;

            for (int i = 0; i != array_size; i++) {
                if (first_max < array[i]) {
                    first_max = array[i];
                    first_max_i = i;
                }
            }

            int last_min = array[0];
            int last_min_i = 0;

            for (int i = 0; i != array_size; i++) {
                if (last_min >= array[i]) {
                    last_min = array[i];
                    last_min_i = i;
                }
            }

            printf("\nВаш массив: ");
            for (int i = 0; i != array_size; i++) {
                printf("%d ", array[i]);
            }

            printf("\n");

           /* array[first_max_i + 1] = array[last_min_i];*/

            printf("\nВаш массив: ");

            for (int i = 0, j = 0; i != array_size; i++, j++) {
                if (last_min_i > first_max_i) {
                    if (i <= first_max_i || i >= last_min_i) {
                        array2[j] = array[i];
                        printf("%d ", array2[j]);
                    }
                }
                else {
                    if (i <= last_min_i || i >= first_max_i) {
                        array2[j] = array[i];
                        printf("%d ", array2[j]);
                    }
                }
            }

            printf("\n\n");

        }
        else {
                printf("\nОшибка: непредвиденное значение.\n\n");
        }

        rewind(stdin);
    }

    return 0;
}