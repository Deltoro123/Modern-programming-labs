#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    char ch;
    FILE* in;
    int empty_count = 0;
    int non_empty_count = 0;
    char name[50] = { 0 };

    // Устанавливаем кодировку консоли Windows-1251
    SetConsoleCP(1251);      // Для ввода
    SetConsoleOutputCP(1251); // Для вывода

    printf("Введите имя файла для просмотра: ");

    if (scanf("%49s", name) != 1) {
        printf("Ошибка ввода имени файла\n");
        return 1;
    }

    if ((in = fopen(name, "r")) == NULL) {
        printf("Файл %s не открыт\n", name);
        return 1;
    }

    printf("\nСодержимое файла:\n");
    printf("-----------------\n");

    while ((ch = fgetc(in)) != EOF) {
        putchar(ch);

        if (isspace(ch) || iscntrl(ch)) {
            empty_count++;
        }
        else {
            non_empty_count++;
        }
    }

    printf("\n-----------------\n");
    printf("\nРезультаты подсчета:\n");
    printf("Пустых символов: %d\n", empty_count);
    printf("Непустых символов: %d\n", non_empty_count);
    printf("Всего символов: %d\n", empty_count + non_empty_count);

    fclose(in);
    return 0;
}