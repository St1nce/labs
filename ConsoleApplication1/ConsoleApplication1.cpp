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
//void data_input(product p[],int i)
//{
//	char name[N];
//    char dump;
//	//product milk;
//	printf("Введите название\nВвод: ");
//	scanf("%s", &(p[i].name));
//    scanf("%c", &dump);
//    check_input(p[i].price, p[i].count, p[i].expiration);
//    Date_try(p[i].day, p[i].month, p[i].year);
//	/*strcpy(p[i].name, name);*/
//	//printf("%s %d %d %d.%d.%d %d\n", milk.name, milk.price, milk.count,milk.day,milk.month,milk.year , milk.expiration);
//}
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

        while (k != n) fwrite(&p[k++], sizeof(p), n, f); // Записываем массив структур в файл
        fclose(f);
    }
    else
    {
        return;
    }
}
void product_inp(product p[])
{
    //FILE* ptrfile = fopen("c:\\users\\alexsandr\\source\\repos\\st1nce\\labs\\ConsoleApplication1\\text.txt", "rb+");
    /*if (ptrfile == 0)
    {
        printf("Файл не найден");
    }*/
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
    //fwrite(p, sizeof(p), num, ptrfile);
    //fclose(ptrfile);

    for (int i = 0; i < num; i++)
    {
        printf("\n%s %d %d %d.%d.%d %d\n", p[i].name, p[i].price, p[i].count, p[i].day, p[i].month, p[i].year, p[i].expiration);
    }
    Save_in_File(p,num);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
    int cnt = 10;// Количество продуктов
    struct product array[N];
    product_inp(array);
}