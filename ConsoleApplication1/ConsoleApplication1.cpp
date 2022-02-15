#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
struct product
{
	char name[20];
	char data[20];
	int priceRub; int priceCop;
	int count, expiration;
};

void data_input()
{
	char name[20];
	char data[20];
	product milk;
	printf("Введите данные о товарах в формате:\nНазвание, цена, количество, дата поступления, срок годности\nВвод: ");
	scanf("%s %d.%d %d %s %d", &name, &milk.priceRub, &milk.priceCop, &milk.count, &data, &milk.expiration);
	strcpy(milk.name, name);
	strcpy(milk.data, data);
	printf("%s %d.%d %d %s %d", &milk.name, &milk.priceRub, &milk.priceCop, &milk.count, &milk.data, &milk.expiration);
}

int main()
{
	setlocale(LC_ALL, "rus");
	data_input();
}
