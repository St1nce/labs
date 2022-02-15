#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
struct product
{
	char name[20];
	char data[20];
	float price;
	int count, expiration;
};

void data_input()
{
	char name[20];
	char data[20];
	product milk;
	printf("Введите данные о товарах в формате:\nНазвание, цена, количество, дата поступления (например 20.03.12), срок годности (в днях)\nВвод: ");
	scanf("%s %f %d %s %d", &name, &milk.price, &milk.count, &data, &milk.expiration);
	strcpy(milk.name, name);
	strcpy(milk.data, data);
	printf("%s %f %d %s %d", &milk.name, &milk.price, &milk.count, &milk.data, &milk.expiration);
}

int main()
{
	setlocale(LC_ALL, "rus");
	data_input();
}
