#include <iostream>
#include <clocale>  // для setlocale
using namespace std;

// 1 способ: подсчет длины строки с помощью цикла и индекса
int dlina1(char* str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

// 2 способ: подсчет длины строки через указатель
int dlina2(char* str)
{
    char* p = str;
    while (*p != '\0')
        p++;
    return p - str;
}

// 3 способ: рекурсивный подсчет длины
int dlina3(char* str)
{
    if (*str == '\0')
        return 0;
    return 1 + dlina3(str + 1);
}

// Копирование строки
void kopir(char* dest, char* src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Сравнение строк
int sravn(char* str1, char* str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Конкатенация строк
void konkat(char* dest, char* src)
{
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main()
{
    // Устанавливаем русскую локаль для корректного вывода
    setlocale(LC_ALL, "Russian");
    // Альтернативный вариант для Windows:
    // system("chcp 1251 > nul");

    char str1[100] = "qwerty";
    char str2[100] = "1234567890";
    char str3[100];
    char str4[100];

    cout << "длина str1=" << dlina1(str1) << ", str2=" << dlina1(str2) << endl;
    cout << "длина str1=" << dlina2(str1) << ", str2=" << dlina2(str2) << endl;
    cout << "длина str1=" << dlina3(str1) << ", str2=" << dlina3(str2) << endl;

    kopir(str3, str1);
    cout << "результат копирования: str3=" << str3 << endl;

    int cmp = sravn(str1, str2);
    cout << "результат сравнения str1 и str2: " << cmp << endl;

    kopir(str4, str1);
    konkat(str4, str2);
    cout << "результат сцепления: str4=" << str4 << endl;

    return 0;
}