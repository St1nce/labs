#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
struct product
{
	char name[20];
	char data[20];
	int price, count, expiration;
}milk;

int main()
{
	setlocale(LC_ALL, "rus");
	 char name[20] = "";
	 milk.count = 10;
	strcpy(milk.name, name);
	printf("%d %s", milk.count, milk.name);
}
