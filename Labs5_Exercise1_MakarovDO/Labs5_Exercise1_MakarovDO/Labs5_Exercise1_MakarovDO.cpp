#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main(int argc, char* argv[])
{
    char ch;
    FILE* in;

    // Устанавливаем русскую локаль для корректного вывода
    setlocale(LC_ALL, "Russian");
    // Альтернатива: setlocale(LC_ALL, "ru-RU");
    // Или: setlocale(LC_ALL, ".1251"); для Windows-1251

    // Если имя файла передано как аргумент командной строки
    if (argc > 1) {
        if (fopen_s(&in, argv[1], "r") != 0) {
            printf("Файл %s не открыт\n", argv[1]);
            return 1;
        }
    }
    else {
        // Запрос имени файла у пользователя
        char name[50] = { 0 };
        printf("Введите имя файла для просмотра: ");

        // Безопасный ввод с ограничением длины
        if (scanf_s("%49s", name, (unsigned)sizeof(name)) != 1) {
            printf("Ошибка ввода имени файла\n");
            return 1;
        }

        if (fopen_s(&in, name, "r") != 0) {
            printf("Файл %s не открыт\n", name);
            return 1;
        }
    }

    // Вывод содержимого файла
    while ((ch = fgetc(in)) != EOF) {
        putchar(ch);
    }

    fclose(in);
    return 0;
}