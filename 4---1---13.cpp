#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <time.h> 

//ФУНКЦИИ//
int random_matrix(int strings, int columns, int array[100][100]) { //random_matrix
    srand(time(NULL));

    for (int i = 0; i != strings; i++) {
        for (int j = 0; j != columns; j++) {
            array[i][j] = -10 + rand() % 21;
        }
    }

    return array;
}

void manual_fill(int strings, int columns, int array[100][100]) { //manual_fill
    for (int i = 0; i != strings; i++) {
        for (int j = 0; j != columns; j++) {
            printf("Введите элемент матрицы (%d, %d): ", i + 1, j + 1);
            while (scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n') {
                printf("\033[31mОшибка:\033[37m требуется ввести целое число.\nВведите элемент матрицы (%d, %d): ", i + 1, j + 1);
                rewind(stdin);
            }
        }
    }
}

void input_size(int *strings, int *columns) { //input_size
    printf("Введите желаемое число строк матрицы: ");
    while (scanf_s("%d", strings) != 1 || getchar() != '\n' || *strings <= 0 || *strings > 100) {
        printf("\n\033[31mОшибка:\033[37m требуется ввести целое положительное число от 1 до 100.\n\nВведите желаемое число строк матрицы: ");
        rewind(stdin);
    }

    printf("Введите желаемое число столбцов матрицы: ");
    while (scanf_s("%d", columns) != 1 || getchar() != '\n' || *columns <= 0 || *columns > 100) {
        printf("\n\033[31mОшибка:\033[37m требуется ввести целое положительное число от 1 до 100.\n\nВведите желаемое число столбцов: ");
        rewind(stdin);
    }
}

int str_zeros(int strings, int columns, int array[100][100]) { //str_zeros
    int str_zeros = 0;
    for (int i = 0; i != strings; i++) {
        for (int j = 0; j != columns; j++) {
            if (array[i][j] == 0) {
                str_zeros++;
                break;
            }
        }
    }

    return str_zeros;
}

int series(int strings, int columns, int array[100][100]) { //series
    int temp_var = 0;
    int temp_series = 1;
    int col_series = 0;
    int total_series[100] = { 0 };
    int max_index = 0;

    for (int j = 0; j != columns; j++) {
        for (int i = 0; i != strings; i++) {
            temp_var = array[i][j];
            for (int k = 0; k != strings; k++) {
                if (temp_var == array[k][j] && k != i) {
                    temp_series++;
                }
            }
            col_series = (col_series > temp_series) ? col_series : temp_series;
            total_series[j] = col_series;
            temp_series = 1;
        }
        col_series = 0;
    }

    int temp_var1 = total_series[0];
    for (int i = 0; i != columns; i++) {
        if (total_series[i] > temp_var1) {
            temp_var1 = total_series[i];
            max_index = i;
        }
    }

    return max_index + 1;
}

void print_matrix(int strings, int columns, int array[100][100]) {
    for (int i = 0; i != strings; i++) {
        printf("|");
        for (int j = 0; j != columns; j++) {
            /*Для выделения нулей*/if (array[i][j] == 0)
                printf("\033[35m%4d\033[37m", array[i][j]);
            else
                printf("%4d", array[i][j]);/*Для выделения нулей*/
        }
        printf("    |\n\n");
    }
}
 //ФУНКЦИИ//

int main() {
    setlocale(LC_ALL, "Rus");

    int array[100][100];
    char choice[2];
    int strings = 0;
    int columns = 0;
    
    while (1) {
        printf("Как вы хотите заполнить матрицу? Автоматически - '\033[33ma\033[37m', вручную - '\033[33mb\033[37m' ('\033[33mq\033[37m' для выхода): ");
        scanf_s("%s", choice, 2);
        choice[0] = tolower(choice[0]);

        if (choice[0] == 'q' && choice[1] == '\0') {
            break;
        }

        else if ((choice[0] == 'a' && choice[1] == '\0') || (choice[0] == 'b' && choice[1] == '\0')) {
            if (choice[0] == 'a' && choice[1] == '\0') {         
                printf("\nВыбрано автоматическое заполнение.\n\n");

                input_size(&strings, &columns); //input_size
                random_matrix(strings, columns, array); //random_matrix
            }
            
            else if (choice[0] == 'b' && choice[1] == '\0') {                
                printf("\nВыбрано ручное заполнение.\n\n");

                input_size(&strings, &columns); //input_size
                printf("\n");               
                manual_fill(strings, columns, array); //manual_fill
            }

            printf("\nВаша матрица:\n\n");
            print_matrix(strings, columns, array);
            
            if (str_zeros(strings, columns, array) != 0) {
                printf("Кол-во строк с хотя бы одним нулевым элементом: %d\n", str_zeros(strings, columns, array));
            }
            else {
                printf("В данной матрице отсутствуют строки с хотя бы одним нулевым элементом.\n");
            }
            printf("Номер столбца c наибольшей чередой повторений: %d", series(strings, columns, array));
            printf("\n\n");

        }
        else {
            printf("\n\033[31mОшибка:\033[37m непредвиденное значение.\n\n");
        }

    rewind(stdin);

    }
    return 0;
}