#include <iostream>
#include <cstdlib>   // для calloc, free
#include <cstring>   // для строковых функций
using namespace std;

int dlina(char* str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

void kopir(char* dest, const char* src)
{
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

void konkat(char* dest, const char* src)
{
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
}

int sravn(const char* str1, const char* str2)
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

int main()
{
    // Для корректного отображения русского текста
    setlocale(LC_ALL, "Russian");

    char* strings[3];
    char buffer[100];

    // Выделение памяти
    for (int i = 0; i < 3; i++)
    {
        strings[i] = (char*)calloc(100, sizeof(char));
        if (strings[i] == NULL)
        {
            cout << "Ошибка выделения памяти!" << endl;
            return 1;
        }
    }

    // Ввод строк
    for (int i = 0; i < 3; i++)
    {
        cout << "Введите строку " << i + 1 << ": ";
        cin >> buffer;
        kopir(strings[i], buffer);
    }

    // Вывод строк
    cout << "\nВведенные строки:" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Строка " << i + 1 << ": " << strings[i];
        cout << ", длина = " << dlina(strings[i]) << endl;
    }

    // Конкатенация
    konkat(strings[0], strings[1]);
    cout << "\nПосле конкатенации строки 1 и 2: " << strings[0] << endl;

    // Сравнение
    int cmp = sravn(strings[1], strings[2]);
    cout << "Результат сравнения строк 2 и 3: " << cmp << endl;

    // Освобождение памяти
    for (int i = 0; i < 3; i++)
        free(strings[i]);

    return 0;
}