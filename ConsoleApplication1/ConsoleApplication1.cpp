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
}milk;

void data_input()
{
	char name[20];
	char data[20];
	printf("Введите данные о товарах в формате\nНазвание, цена, количество, дата поступления, срок годности\nВвод:");
	scanf("%s %f %d %s %d", &name, &milk.price, &milk.count, &data, &milk.expiration);
	milk.name = strcpy(milk.name, name);
	milk.data = strcpy(milk.data, data);
	printf("%s %f %d %s %");
}

int main()
{
	setlocale(LC_ALL, "rus");
}
