#include <stdio.h> 
#include <locale.h> 
#include <ctype.h> 
#include <stdlib.h> 
#include <time.h> 

//ФУНКЦИИ//
int max_elem(int side, int array[100][100]) {
    int max_elem = array[0][0];
    if (side % 2 == 0) {
        for (int i = 0; i != side / 2 - 1; i++) {
            for (int j = 0; j != side / 2 - 1; j++) {
                max_elem = (max_elem > array[i][j]) ? max_elem : array[i][j];
            }
        }
    }
    else {

        for (int i = 0; i != side / 2 + 1; i++) {
            for (int j = 0; j != side / 2 + 1; j++) {
                max_elem = (max_elem > array[i][j]) ? max_elem : array[i][j];
            }
        }

    }
    return max_elem;
}
void random_matrix(int side, int array[100][100]) { //random_matrix
    srand(time(NULL));

    for (int i = 0; i != side; i++) {
        for (int j = 0; j != side; j++) {
            array[i][j] = -10 + rand() % 21;
        }
    }
}

void manual_fill(int side, int array[100][100]) { //manual_fill
    for (int i = 0; i != side; i++) {
        for (int j = 0; j != side; j++) {
            printf("Введите элемент матрицы (%d, %d): ", i + 1, j + 1);
            while (scanf_s("%d", &array[i][j]) != 1 || getchar() != '\n') {
                printf("\033[31mОшибка:\033[37m требуется ввести целое число.\nВведите элемент матрицы (%d, %d): ", i + 1, j + 1);
                rewind(stdin);
            }
        }
    }
}

void input_size(int *side) { //input_size
    printf("Введите размер стороны квадратной матрицы: ");
    while (scanf_s("%d", side) != 1 || getchar() != '\n' || *side <= 0 || *side > 100) {
        printf("\n\033[31mОшибка:\033[37m требуется ввести целое положительное число от 1 до 100.\n\nВведите размер стороны квадратной матрицы: ");
        rewind(stdin);
    }
}

void print_matrix(int side, int array[100][100]) {
    for (int i = 0; i != side; i++) {
        printf("|");
        for (int j = 0; j != side; j++) {
            if (side % 2 == 0) {
                if (i <= side / 2 - 1 && j <= side / 2 - 1) {
                    printf("\033[31m%4d\033[37m", array[i][j]);
                }
                else
                    printf("%4d", array[i][j]);
            }
            else {
                if (i < side / 2 + 1 && j < side / 2 + 1) {
                    printf("\033[31m%4d\033[37m", array[i][j]);
                }
                else
                    printf("%4d", array[i][j]);
            }
        }
        printf("   |\n\n");
    }
}
 //ФУНКЦИИ//

int main() {
    setlocale(LC_ALL, "Rus");

    int array[100][100];
    char choice[2];
    int side = 0;
    
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

                input_size(&side); //input_size
                random_matrix(side, array); //random_matrix
            }
            
            else if (choice[0] == 'b' && choice[1] == '\0') {                
                printf("\nВыбрано ручное заполнение.\n\n");

                input_size(&side); //input_size
                printf("\n");               
                manual_fill(side, array); //manual_fill
            }

            printf("\nВаша матрица:\n\n");
            print_matrix(side, array);

            printf("Наибольший элемент в \033[31mкрансой\033[37m области: %d\n\n", max_elem(side, array));
            
        }
        else {
            printf("\n\033[31mОшибка:\033[37m непредвиденное значение.\n\n");
        }

    rewind(stdin);

    }
    return 0;
}