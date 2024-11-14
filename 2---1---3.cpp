#include <stdio.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Rus");

	int period = 2024 - 1626;
	double cash = 20;

	printf("Начальная сумма вклада: $%.2lf\n", cash);
	printf("Временной период: %d лет\n\n", period);

	for (int i = period; i != 0; i--) {
		cash += cash / 100 * 4;
	}

	printf("Конечная сумма: $%.2lf\n", cash);

	return 0;
}