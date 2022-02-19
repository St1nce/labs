#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <Windows.h>
#define N 20
struct product  
{
	char name[20];
	int price;
    int day;
    int month;
    int year;
	int count, expiration;
};


void Date_try(int& day, int& month, int& year)
{
    char temp[N]; // массив для ввода данных в едином (символьном) формате
    do
    {
        do
        {
            printf("Дата получения\nВведите день:  ");
            day = atoi(gets_s(temp));
            if ((day > 0) && (day < 32)) break;
            printf("\nОшибка при вводе дня!\n");
        } while (1);

        do
        {
            printf("Введите месяц: ");
            month = atoi(gets_s(temp));
            if ((month > 0) && (month < 13)) break;
            printf("\nОшибка при вводе месяца!\n");
        } while (1);

        do
        {
            printf("Введите год (с 1940 до 2020): ");
            year = atoi(gets_s(temp));
            if ((year >= 1940) && (year < 2022)) break;
            printf("\nОшибка при вводе года!\n");
        } while (1);

        switch (month)
        {
        case 2: if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
        {
            if (day < 30) return;
            printf("Ошибка при вводе дня для високосного года!  Повторите ввод!\n");
            break;
        }
              else
            if (day < 29) return;
            printf("Ошибка при вводе дня для не високосного года! Повторите ввод!\n");
            break;
        case 4: case 6: case 9: case 11:
            if (day < 31) return;
            printf("Ошибка при вводе месяца с количеством дней не больше 30! Повторите ввод!\n");
            break;
        default:    return;
        }
    } while (1);
   /* char date1[11] =
    {
        day / 10 + '0',
        day % 10 + '0',
        '.',
        month / 10 + '0',
        month % 10 + '0',
        '.',
        year / 1000 + '0',
        (year / 100) % 10 + '0',
        (year / 10) % 10 + '0',
        year % 10 + '0',
        '\0'
    };
    strcpy(date, date1);*/
    //printf_s("%s\n", date);
    
}
void check_input(int& price, int& count, int& expiration)
{

    
    char temp[N]; // массив для ввода данных в едином (символьном) формате
    do
    {
        printf("Введите цену: ");
        do
        {
            price = atoi(gets_s(temp));
            if (price > 0)  break;
            printf("\nОшибка при вводе цены! Повторите ввод: ");
        } while (1);

        printf("Введите количество: ");
        do
        {
            count = atoi(gets_s(temp));
            if (count > 0)  break;
            printf("\nОшибка при вводе количества товара! Повторите ввод: ");
        } while (1);

        printf("Введите срок годности: ");
        do
        {
            expiration = atoi(gets_s(temp));
            if (expiration > 0)  break;
            printf("\nОшибка при вводе срока годности! Повторите ввод: ");
        } while (1);
        return;
    } while (1);   
    
}
void data_input()
{
    /*char date[11];*/
	char name[N];
    char dump;
	product milk;
	printf("Введите название\nВвод: ");
	scanf("%s", &name);
    scanf("%c", &dump);

    
    check_input(milk.price, milk.count, milk.expiration);
    Date_try(milk.day, milk.month, milk.year);
    /*printf("Введите срок годности:");
    scanf("%d",&milk.expiration);*/
	strcpy(milk.name, name);
    /*strcpy(milk.date, date);*/
    
    //Date_Input(&milk.day, &milk.month, &milk.year);
	printf("%s %d %d %d.%d.%d %d\n", milk.name, milk.price, milk.count,milk.day,milk.month,milk.year , milk.expiration);
}

int main()
{
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "rus");
	data_input();
    
}
