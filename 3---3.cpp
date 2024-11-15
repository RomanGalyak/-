#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <time.h> 

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int array[100];
    int array_2[100];
    int array_3[100];
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
                while (scanf_s("%d", &array_size) != 1 || getchar() != '\n' || array_size <= 0 || array_size > 100) {
                    printf("\nОшибка: требуется ввести целое положительное число от 1 до 100.\n\nВведите желаемое количество элементов массива: ");
                    rewind(stdin);
                }

                for (int i = 0; i != array_size; i++) {
                    array[i] = -10 + rand() % 21;
                    array_2[i] = -10 + rand() % 21;
                }
            }
            else if (choice[0] == 'b' && choice[1] == '\0') {
                printf("\nВыбрано ручное заполнение.\n\n");


                printf("Введите желаемое количество элементов массива: ");
                while (scanf_s("%d", &array_size) != 1 || getchar() != '\n' || array_size <= 0 || array_size > 50) {
                    printf("\nОшибка: требуется ввести целое положительное число от 1 до 50.\n\nВведите желаемое количество элементов массива: ");
                    rewind(stdin);
                }

                printf("\n");
                for (int i = 0; i != array_size; i++) {
                    printf("Введите элемент первого массива(%d): ", i + 1);
                    while (scanf_s("%d", &array[i]) != 1 || getchar() != '\n') {
                        printf("Ошибка: требуется ввести целое число.\nВведите элемент массива(%d): ", i + 1);
                        rewind(stdin);
                    }
                }

                printf("\n");
                for (int i = 0; i != array_size; i++) {
                    printf("Введите элемент второго массива(%d): ", i + 1);
                    while (scanf_s("%d", &array_2[i]) != 1 || getchar() != '\n') {
                        printf("Ошибка: требуется ввести целое число.\nВведите элемент массива(%d): ", i + 1);
                        rewind(stdin);
                    }
                }
            }

            int temp_var = 0;
            int max_number = 0;
            int min_number = 0;
            int max_number_pos = -1;
            int min_number_pos = -1;
            
            for (int i = 0; i != array_size; i++) {
                max_number = array[i];
                for (int j = i; j != array_size; j++) {
                    max_number = (max_number > array[j]) ? max_number : array[j];
                    if (array[j] == max_number)
                        max_number_pos = j;
                }
                temp_var = array[i];
                array[i] = array[max_number_pos];
                array[max_number_pos] = temp_var;
            }

            printf("\nВаш первый массив, упорядоченный по убыванию: ");
            for (int i = 0; i != array_size; i++) {
                printf("%d ", array[i]);
            }

            for (int i = 0; i != array_size; i++) {
                max_number = array_2[i];
                for (int j = i; j != array_size; j++) {
                    max_number = (max_number > array_2[j]) ? max_number : array_2[j];
                    if (array_2[j] == max_number)
                        max_number_pos = j;
                }
                temp_var = array_2[i];
                array_2[i] = array_2[max_number_pos];
                array_2[max_number_pos] = temp_var;
            }

            printf("\nВаш второй массив, упорядоченный по убыванию: ");
            for (int i = 0; i != array_size; i++) {
                printf("%d ", array_2[i]);
            }

            for (int i = 0; i < array_size; i++) {
                array_3[i] = array[i];
            }

            for (int i = 0; i < array_size; i++) {
                array_3[array_size + i] = array_2[i];
            }

            for (int i = 0; i != array_size * 2; i++) {
                max_number = array_3[i];
                for (int j = i; j != array_size * 2; j++) {
                    max_number = (max_number > array_3[j]) ? max_number : array_3[j];
                    if (array_3[j] == max_number)
                        max_number_pos = j;
                }
                temp_var = array_3[i];
                array_3[i] = array_3[max_number_pos];
                array_3[max_number_pos] = temp_var;
            }

            printf("\nОбъединенный массив, упорядоченный по убыванию: ");
            for (int i = 0; i != array_size * 2; i++) {
                printf("%d ", array_3[i]);
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