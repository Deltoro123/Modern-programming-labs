#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_LINE 1024

// Функция поиска подстроки в строке
int find_substring(const char* str, const char* substr) {
    return (strstr(str, substr) != NULL);
}

int main(int argc, char* argv[])
{
    FILE* in = NULL, * out = NULL;
    char name[260] = { 0 };
    char search_str[100] = { 0 };
    char line[MAX_LINE] = { 0 };
    int line_num = 0;
    int found_count = 0;
    int result;

    // Устанавливаем русскую кодировку в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Проверка аргументов командной строки
    if (argc >= 3) {
        strncpy(name, argv[1], sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';

        strncpy(search_str, argv[2], sizeof(search_str) - 1);
        search_str[sizeof(search_str) - 1] = '\0';

        printf("Поиск подстроки \"%s\" в файле %s\n", search_str, name);
    }
    else {
        // Интерактивный режим
        printf("Введите имя файла для поиска: ");
        result = scanf("%259s", name);
        if (result != 1) {
            printf("Ошибка ввода имени файла\n");
            return 1;
        }

        printf("Введите искомую подстроку: ");
        result = scanf("%99s", search_str);
        if (result != 1) {
            printf("Ошибка ввода подстроки\n");
            return 1;
        }
    }

    // Открытие входного файла
    if ((in = fopen(name, "r")) == NULL) {
        printf("Файл %s не открыт\n", name);
        printf("Проверьте, существует ли файл в текущей директории\n");
        return 1;
    }

    // Открытие выходного файла для результатов
    if ((out = fopen("result.txt", "w")) == NULL) {
        printf("Не удалось создать файл результатов\n");
        fclose(in);
        return 1;
    }

    fprintf(out, "Результаты поиска подстроки \"%s\" в файле %s:\n", search_str, name);
    fprintf(out, "================================================\n\n");

    // Поиск подстроки
    while (fgets(line, MAX_LINE, in) != NULL) {
        line_num++;

        if (find_substring(line, search_str)) {
            found_count++;
            // Удаляем символ новой строки для вывода
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }
            fprintf(out, "Строка %d: %s\n", line_num, line);
        }
    }

    if (found_count == 0) {
        fprintf(out, "Подстрока \"%s\" не найдена.\n", search_str);
    }
    else {
        fprintf(out, "\nВсего найдено вхождений: %d\n", found_count);
    }

    printf("\nРезультаты поиска сохранены в файл result.txt\n");
    printf("Найдено вхождений: %d\n", found_count);

    fclose(in);
    fclose(out);

    return 0;
}