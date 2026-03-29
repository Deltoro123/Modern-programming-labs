#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_LINE 1024

// Функция извлечения номера страницы из строки
int extract_page_number(char* line) {
    char* start;
    char num_str[20] = { 0 };
    int i = 0;

    // Поиск шаблона "- число -"
    start = strstr(line, "-");
    if (start != NULL) {
        start++; // пропускаем первый '-'

        // Пропускаем пробелы
        while (*start == ' ') start++;

        // Копируем цифры
        while (isdigit((unsigned char)*start)) {
            if (i < 19) {
                num_str[i++] = *start++;
            }
            else {
                break;
            }
        }
        num_str[i] = '\0';

        // Проверяем наличие закрывающего '-'
        while (*start == ' ') start++;
        if (*start == '-') {
            return atoi(num_str);
        }
    }
    return -1;
}

// Функция удаления знаков переноса
void remove_hyphens(char* line) {
    char temp[MAX_LINE] = { 0 };
    int i = 0, j = 0;

    while (line[i] != '\0' && j < MAX_LINE - 1) {
        if (line[i] == '-' && (line[i + 1] == '\n' || line[i + 1] == '\0')) {
            i++;
            continue;
        }
        temp[j++] = line[i++];
    }
    temp[j] = '\0';
    strcpy(line, temp);
}

int main(int argc, char* argv[])
{
    FILE* in = NULL, * out = NULL;
    char line[MAX_LINE] = { 0 };
    char page_line[MAX_LINE] = { 0 };
    int page_num = -1;
    int in_page = 1;
    char name[260] = { 0 };
    int result;

    // Устанавливаем русскую кодировку в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("========================================\n");
    printf("Программа обработки номеров страниц\n");
    printf("========================================\n\n");

    printf("Введите имя файла для обработки: ");

    result = scanf("%259s", name);
    if (result != 1) {
        printf("Ошибка ввода имени файла\n");
        return 1;
    }

    // Открытие входного файла
    if ((in = fopen(name, "r")) == NULL) {
        printf("\nОшибка: Файл '%s' не открыт\n", name);
        printf("Проверьте, существует ли файл в текущей директории\n");
        return 1;
    }

    printf("Файл успешно открыт. Идет обработка...\n\n");

    // Открытие выходного файла
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("Не удалось создать выходной файл\n");
        fclose(in);
        return 1;
    }

    // Обработка файла
    while (fgets(line, MAX_LINE, in) != NULL) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Проверка на символ перехода на новую страницу
        if (strchr(line, '\f') != NULL) {
            if (page_num > 0 && page_line[0] != '\0') {
                fprintf(out, "%s", page_line);
                fprintf(out, "\n[Страница %d]\n\n", page_num);
            }

            page_line[0] = '\0';
            in_page = 1;
            continue;
        }

        // Проверяем, является ли строка номером страницы
        if (in_page) {
            int temp_num = extract_page_number(line);
            if (temp_num > 0) {
                page_num = temp_num;
                in_page = 0;
                continue;
            }
        }

        // Удаляем знаки переноса
        remove_hyphens(line);

        // Добавляем строку к текущей странице
        if (strlen(page_line) + strlen(line) + 1 < MAX_LINE) {
            strcat(page_line, line);
            strcat(page_line, "\n");
        }
        in_page = 0;
    }

    // Записываем последнюю страницу
    if (page_num > 0 && page_line[0] != '\0') {
        fprintf(out, "%s", page_line);
        fprintf(out, "[Страница %d]\n", page_num);
    }

    printf("========================================\n");
    printf("Обработка завершена успешно!\n");
    printf("Результат сохранен в файл: output.txt\n");
    printf("========================================\n");

    fclose(in);
    fclose(out);

    return 0;
}