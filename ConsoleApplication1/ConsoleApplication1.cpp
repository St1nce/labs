#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
struct product
{
	char name[20], date[11];
	int price;
	int count, expiration;
};
void data_input()
{
	char name[20];
	char date[11];
	product milk;
	printf("Введите данные о товарах в формате:\nНазвание, цена, количество, дата поступления (например 20.03.2012), срок годности (в днях)\nВвод: ");
	scanf("%s %d %d %s %d", &name, &milk.price, &milk.count, &date, &milk.expiration);
	strcpy(milk.name, name);
	strcpy(milk.date, date);
	printf("%s %d %d %s %d", milk.name, milk.price, milk.count, date, milk.expiration);
}

int main()
{
	setlocale(LC_ALL, "rus");
	data_input();
}
