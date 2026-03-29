#include <iostream>      // вместо iostream.h
#include <cstdlib>       // вместо alloc.h (содержит malloc, free)
#include <cstring>       // для работы со строками (опционально)
#include <clocale>       // для setlocale
using namespace std;

int dlina(char* str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void kopir(char* dest, const char* src)  // const char* для строковых литералов
{
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

void konkat(char* dest, const char* src)  // const char* для строковых литералов
{
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

int sravn(const char* str1, const char* str2)  // const для корректного сравнения
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

int main()  // int main вместо void main
{
    // Устанавливаем русскую локаль для корректного вывода
    setlocale(LC_ALL, "Russian");
    // Альтернативный вариант для Windows:
    // system("chcp 1251 > nul");

    char* str1, * str2;
    str1 = (char*)malloc(100);
    str2 = (char*)malloc(100);

    // Проверка успешности выделения памяти
    if (str1 == NULL || str2 == NULL)
    {
        cout << "Ошибка выделения памяти!" << endl;
        return 1;
    }

    // Инициализация строк
    kopir(str1, "Hello");
    kopir(str2, "World");

    cout << "str1 = " << str1 << ", длина = " << dlina(str1) << endl;
    cout << "str2 = " << str2 << ", длина = " << dlina(str2) << endl;

    // Конкатенация
    konkat(str1, " ");
    konkat(str1, str2);
    cout << "После конкатенации: " << str1 << endl;

    // Сравнение
    int cmp = sravn(str1, str2);
    cout << "Сравнение: " << cmp << endl;

    free(str1);
    free(str2);

    return 0;
}