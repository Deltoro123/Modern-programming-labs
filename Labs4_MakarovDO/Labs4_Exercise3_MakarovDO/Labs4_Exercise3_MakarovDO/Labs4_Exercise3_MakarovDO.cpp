#include <iostream.h>
#include <alloc.h>

int dlina(char* str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void kopir(char* dest, char* src)
{
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

void konkat(char* dest, char* src)
{
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

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

void main(void)
{
    char* str1, * str2;
    str1 = (char*)malloc(100);
    str2 = (char*)malloc(100);

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
}