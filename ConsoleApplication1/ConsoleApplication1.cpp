#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
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
void Sort_Name(product p[], int& n);
void Sort_Date(product p[], int& n);
void del(product p[], int& n);
void Bin_search(product p[], int& n);
void Output_struct(product p[], int& n)//вывод массива структуры
{
    for (int i = 0; i < n; i++)
    {
        printf("%s %d %d %d.%d.%d %d\n", p[i].name, p[i].price, p[i].count, p[i].day, p[i].month, p[i].year, p[i].expiration);
    }
}
void check_date(int& day, int& month, int& year)// проверка ввода даты
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
            printf("Введите год (с 2000 до 2022): ");
            year = atoi(gets_s(temp));
            if ((year >= 2000) && (year <= 2022)) break;
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
void check_input(int& price, int& count, int& expiration)//Проверка ввода данных
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
void Save_in_File(product p[], int& n)//сохранение в файл
{
    int k = 0, ansr;
    char fname[N];
    printf("Хотите сохранить данные в файл?\n 1 - ДА, 2 - Выход из программы\n");
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
        printf("Закрыто");
        return;
    }
}
void Load_from_File(product p[], int& n)//загрузка из файла в массив стуктур
{
    int i = 0;
    char fname[N];
    FILE* f;

    printf("\nВведите имя файла: ");
    scanf("%s",&fname);
    if ((f = fopen(fname, "rb")) == NULL) // Открываем файл для чтения
    {
        puts("Ошибка загрузки"); return;
    } 
    else
    {
        fseek(f, 0L, 2); // Позиционируем указатель на конец файла
        n = ftell(f) / sizeof(product); // Определяем количество записей в файле
        rewind(f); // Позиционируем указатель на начало файла
        fread(p, sizeof(product), n, f); // Копируем записи из файла
        fclose(f); // Закрываем файл
    }
    Output_struct(p, n);
    int answer;
    printf("1 - Сортировать по названию\n2 - Сортировать по дате получению\n3 - Удаления данных\n Ввод:");
    scanf("%d", &answer);
    if (answer == 1)
    {
        Sort_Name(p, n);
        Bin_search(p, n);
        Save_in_File(p, n);
        

    }
    else if (answer == 2)
    {
        Sort_Date(p, n);
        Bin_search(p, n);
        Save_in_File(p, n);
    }
    else
    {
        del(p, n);
        printf("Товар удален\n");
        Save_in_File(p, n);
    }

}
void Sort_Name(product p[], int& n)// сортирока по названию товара
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
    Output_struct(p, n);
}
void Sort_Date(product p[], int& n)// сортировка по дате получения
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
    Output_struct(p, n);
}
void del(product p[],int& n)// удаление данных
{
    int ans;
    for(int i=0;i<n;i++)
    {
        printf("%d - %s\n", i+1, p[i].name);
    }
    printf(" Теперь каждый товар пронумерован,введите номер товара: ");
    int j = 0;
    for (; j < n; j++) 
    {
        int numb;
        scanf("%d", &numb);
        j = numb;
        
        p[j-1].Output();// вывод информации о товаре
        break;
    }
    int numb=j;
    printf("Хотите удалить? Да(1)/ Нет(2)\n");
    scanf("%d", &ans);
    if (ans == 1)
    {
        for (int j = numb; j < n - 1; j++) p[j - 1] = p[j + 1];
        n--;
        Output_struct(p, n);
    }
    else
    {
        printf("Не удалили\n");
        Output_struct(p, n);
    } 
}
void Bin_search(product p[], int& n)// бинарный поиск
{
    int i, l = 0, r = n - 1, f = 0, otv;
    char name[N];
    printf("Хотите ли найти товар? 1 - Да, 2 - Нет\nВвод:");
    scanf("%d", &otv);
    if (otv == 1)
    {
        printf("Название товара?: ");
        scanf("%s", &name);
        while ((l <= r) && (f == 0))
        {
            i = (l + r) / 2;
            if (strcmp(p[i].name, name) == 0)
            {
                f = 1;
                p[i].Output(); // вывод информации об автомобиле
                break;
            }

            if (strcmp(p[i].name, name) < 0) l = i + 1;
            if (strcmp(p[i].name, name) > 0) r = i - 1;
        }
            if (f == 0) puts("Нет данных!");
            _getch();
        
    }
}
void product_inp(product p[])// функция ввода данных о товаре.
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

    printf("Доступные действия\n1 - Сортировать по названия\n2 - Сортировать по дате\n3 - Удалить данные\n4 - сохранить данные\n");
    int answer, ans1, ans2;
    scanf_s("%d", &answer);
    if (answer == 1)
    {
        Sort_Name(p, num);
        printf("Сортировка по названию:\n");
        Bin_search(p, num);
        Save_in_File(p, num);
    }
    else if (answer == 2)
    {
         Sort_Date(p, num);
         printf("Сортировка по дате:\n");
         Output_struct(p, num);
         Bin_search(p, num);
         Save_in_File(p, num);
    }
    else if (answer == 3)
    {
        del(p, num);
    }
    else if (answer == 4)
    {
        Save_in_File(p, num);
    }
}
void menu(product array[],int& n)// меню
{
    int start;
    printf("Доступные действия:\nВвести данные о товарах (1)\nЗагрузить данные из файла (2)\nВвод: ");
    scanf("%d", &start);
    if (start == 1)
        product_inp(array);
    else if (start == 2)
        Load_from_File(array, n);
    else
        printf("Такого действия нету");
}
int main()
{
    int n = 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    struct product array[N];
    menu(array,n);
    
}