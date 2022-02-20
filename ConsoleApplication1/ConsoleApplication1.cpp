﻿#define _CRT_SECURE_NO_WARNINGS
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
    void Output()
    {
        printf("%s %d %d %d.%d.%d %d\n",name, price, count, day, month, year, expiration); // Вывод данных на экран 
    }
    bool operator > (product& right)
    {
        if (strcmp(name, right.name) > 0) return true;
        return false;
    }
    product& operator = (product& c)
    {
        strcpy(name, c.name);
        price = c.price;
        day = c.day;
        month = c.month;
        year = c.year;
        count = c.count;
        expiration = c.expiration;
        return *this;
    }
};
void Output_struct(product p[], int& n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %d %d.%d.%d %d\n", p[i].name, p[i].price, p[i].count, p[i].day, p[i].month, p[i].year, p[i].expiration);
    }
}
void check_date(int& day, int& month, int& year)
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
void Save_in_File(product p[], int& n)
{
    int k = 0, ansr;
    char fname[N];
    printf("Хотите сохранить данные в файл?\n 1 - ДА, 0 - Нет\n");
    scanf("%d", &ansr);
    if (ansr == 1)
    {
        printf("\nВведите 'имя_файла.расширение': ");
        scanf("%s", &fname);
        FILE* f;
        if ((f = fopen(fname, "wb")) == NULL) // Открываем файл для записи
        {
            puts("Ошибка сохранения!");
            return;
        }

        fwrite(p, sizeof(product), n, f); // Записываем массив структур в файл
        fclose(f);
    }
    else
    {
        return;
    }
}
void Load_from_File(product p[], int& n)
{
    int i = 0;
    char fname[N];
    FILE* f;

    printf("\nВведите имя файла: ");
    gets_s(fname);
    if ((f = fopen(fname, "rb")) == NULL) puts("Ошибка загрузки"); // Открываем файл для чтения
    else
    {
        fseek(f, 0L, 2); // Позиционируем указатель на конец файла
        n = ftell(f) / sizeof(product); // Определяем количество записей в файле
        rewind(f); // Позиционируем указатель на начало файла
        fread(p, sizeof(product), n, f); // Копируем записи из файла
        fclose(f); // Закрываем файл
    }
    Output_struct(p, n);
}
void Sort_Name(product p[], int& n)
{
    int i, j, min;
    product tmp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (p[min] > p[j]) min = j; //см. перегрузку операции отношения > в файле "avto.h"
        tmp = p[i];
        p[i] = p[min];
        p[min] = tmp;
    }
}
void Sort_Date(product p[], int& n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].day + p[i].month + p[i].year > p[j].day + p[j].month + p[j].year)
            {
                product temp = p[j];
                p[j] = p[i];
                p[i] = temp;
            }
        }
    }
}
void Delete_name(product p[], int& n)
{
    int i, j, l = 0, r = n - 1, f = 0;
    char name[N];
    printf(" Введите название товара: ");
    scanf("%s", &name);
    while ((l <= r) && (f == 0))
    {
        i = (l + r) / 2;
        if (strcmp(p[i].name, name) == 0)
        {
            f = 1;
            p[i].Output(); // вывод информации о товаре
            printf("\n Удалить запись? Да(1) или нет(0)?\n");
            scanf("%d", &l);
            if (l == 1)
            {
                for (j = i; j < n - 1; j++) p[j] = p[j + 1];
                n--;
                Output_struct(p, n);
            }
            
            else
            {
                printf("Не удалили! \n");
                Output_struct(p,n);
                break;
            }
        }
        if (strcmp(p[i].name, name) < 0) l = i + 1;
        if (strcmp(p[i].name, name) > 0) r = i - 1;
    }
    if (f == 0) puts("Нет данных!");
}

void product_inp(product p[])
{
    int num = 0;
    while (num < N)
    {
        char dump;
        printf("Введите название продукта без пробела(Если хотите закончить список введите END в строке 'Ввод').\nВвод: ");
        scanf("%s", &(p[num].name));
        if (strcmp(p[num].name, "END") == 0)
        {
            break;
        }
        scanf("%c", &dump);
        check_input(p[num].price, p[num].count, p[num].expiration);
        check_date(p[num].day, p[num].month, p[num].year);
        num++;
    }

    Output_struct(p, num);

    printf("Доступные действия\n1 - Сортировать по названия\n2 - Сортировать по дате\n3 - Удалить данные\n");
    int answer;
    scanf_s("%d",&answer);
    if (answer == 1)
    {
         Sort_Name(p, num);
         printf("Сортировка по названию:\n");
         Output_struct(p, num);
    }
    else if (answer == 2)
    {
         Sort_Date(p, num);
         printf("Сортировка по дате:\n");
         Output_struct(p, num);
    }
    else if (answer == 3)
    {
        Delete_name(p,num);
    }
    else
    {
        printf("Такой команды такой нету");
    }
}

//void Bin_search(product* p[], int& n)
//{
//    int i, l = 0, r = n - 1, f = 0;
//    char name[L];
//
//    printf("Название товара?: ");
//    gets_s(name);
//
//    while ((l <= r) && (f == 0))
//    {
//        i = (l + r) / 2;
//        if (strcmp(p[i].name, name) == 0)
//        {
//            f = 1;
//            p[i].Output(); // вывод информации об автомобиле
//            break;
//        }
//
//        if (strcmp(p[i].name, name) < 0) l = i + 1;
//        if (strcmp(p[i].name, name) > 0) r = i - 1;
//    }
//
//    if (f == 0) puts("Нет данных!");
//    _getch();
//}

int main()
{
    int n = 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    struct product array[N];
    product_inp(array);
    //Load_from_File(array, n);
}