#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <time.h> 

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    double array[100]; 
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
                    array[i] = -10.0 + (rand() / (double)RAND_MAX) * 20.0;
                }
            }
            else if (choice[0] == 'b' && choice[1] == '\0') {
                printf("\nВыбрано ручное заполнение.\n\n");

            
                printf("Введите желаемое количество элементов массива: ");
                while (scanf_s("%d", &array_size) != 1 || getchar() != '\n' || array_size <= 0 || array_size > 100) {
                    printf("\nОшибка: требуется ввести целое положительное число от 1 до 100.\n\nВведите желаемое количество элементов массива: ");
                    rewind(stdin);
                }

                printf("\n");
                for (int i = 0; i != array_size; i++) {
                    printf("Введите элемент массива(%d): ", i + 1);
                    while (scanf_s("%lf", &array[i]) != 1 || getchar() != '\n') {
                        printf("Ошибка: требуется ввести число.\nВведите элемент массива(%d): ", i + 1);
                        rewind(stdin);
                    }
                }
            }
            printf("\nВаш массив: ");
            for (int i = 0; i != array_size; i++) {
                printf("%.2lf ", array[i]);
            }

            double even_sum = 0;
            
            for (int i = 0, j = 1; i < array_size; i++) {
    
                if (j % 2 == 0) {
                    even_sum += array[i];
                    j++;
                }
                else {
                    j++;
                }
            }
            
            if (array_size <= 1)
                printf("\nВ массиве нет четных элементов.");
            else 
                printf("\nСумма четных элементов массива: %.2lf", even_sum);
            
            int first_neg_i = 0;
            int last_neg_i = 0;
            double between_sum = 0;
            int any_negative = 0;

            for (int i = 0; i != array_size; i++) {
                if (array[i] < 0) {
                    first_neg_i = i;
                    any_negative++;
                    break;
                }
            }

            for (int i = array_size - 1; i != 0; i--) {
                if (array[i] < 0) {
                    last_neg_i = i;
                    any_negative++;
                    break;
                }
            }

            if (any_negative == 2 && first_neg_i != last_neg_i) {
                for (int i = first_neg_i + 1; i != last_neg_i; i++) {
                    between_sum += array[i];
                }
                if (between_sum == 0) {
                    printf("\nМежду первым и последним отрицательными элементами нет других элементов.");
                }
                else {
                    printf("\nСумма  элементов между первым и последним отрицательными: %.2lf", between_sum);
                }
            }
            else {
                printf("\nВ данном массиве есть лишь один отрицательный элемент, или же их нет вообще.");
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