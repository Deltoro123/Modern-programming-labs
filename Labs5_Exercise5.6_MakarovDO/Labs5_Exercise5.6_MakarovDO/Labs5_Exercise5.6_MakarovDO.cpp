#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    FILE* in = NULL, * out = NULL;
    int ch;
    int key_len;
    int key_index = 0;
    char input_file[260] = { 0 };
    char output_file[260] = { 0 };
    char key[100] = { 0 };
    int result;

    // Устанавливаем русскую кодировку в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Проверка аргументов командной строки
    if (argc == 4) {
        // Аргументы переданы: программа input_file output_file key
        strncpy(input_file, argv[1], sizeof(input_file) - 1);
        input_file[sizeof(input_file) - 1] = '\0';

        strncpy(output_file, argv[2], sizeof(output_file) - 1);
        output_file[sizeof(output_file) - 1] = '\0';

        strncpy(key, argv[3], sizeof(key) - 1);
        key[sizeof(key) - 1] = '\0';

        printf("========================================\n");
        printf("Режим: командная строка\n");
        printf("Входной файл: %s\n", input_file);
        printf("Выходной файл: %s\n", output_file);
        printf("Ключ: %s\n", key);
        printf("========================================\n");
    }
    else if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        // Интерактивный режим
        printf("========================================\n");
        printf("Программа шифрования/дешифрования\n");
        printf("========================================\n\n");

        printf("Введите имя входного файла: ");
        result = scanf("%259s", input_file);
        if (result != 1) {
            printf("Ошибка ввода имени входного файла\n");
            return 1;
        }

        printf("Введите имя выходного файла: ");
        result = scanf("%259s", output_file);
        if (result != 1) {
            printf("Ошибка ввода имени выходного файла\n");
            return 1;
        }

        printf("Введите ключ шифрования: ");
        result = scanf("%99s", key);
        if (result != 1) {
            printf("Ошибка ввода ключа\n");
            return 1;
        }

        printf("\n========================================\n");
        printf("Режим: интерактивный\n");
        printf("Входной файл: %s\n", input_file);
        printf("Выходной файл: %s\n", output_file);
        printf("Ключ: %s\n", key);
        printf("========================================\n");
    }
    else {
        printf("========================================\n");
        printf("ПРОГРАММА ШИФРОВАНИЯ/ДЕШИФРОВАНИЯ\n");
        printf("========================================\n\n");
        printf("Использование:\n");
        printf("  %s input_file output_file key\n", argv[0]);
        printf("  %s -i (интерактивный режим)\n\n", argv[0]);
        printf("Примеры:\n");
        printf("  %s input.txt encrypted.txt mykey\n", argv[0]);
        printf("  %s encrypted.txt decrypted.txt mykey\n\n", argv[0]);
        printf("Для шифрования: программа шифрует input.txt в encrypted.txt\n");
        printf("Для дешифрования: программа расшифровывает encrypted.txt в decrypted.txt\n");
        printf("========================================\n");
        return 1;
    }

    // Проверка, что ключ не пустой
    if (strlen(key) == 0) {
        printf("Ошибка: ключ шифрования не может быть пустым\n");
        return 1;
    }

    // Открытие входного файла
    if ((in = fopen(input_file, "rb")) == NULL) {
        printf("\nОшибка: не удалось открыть файл %s\n", input_file);
        printf("Проверьте, существует ли файл в текущей директории\n");
        return 1;
    }

    // Открытие выходного файла
    if ((out = fopen(output_file, "wb")) == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", output_file);
        fclose(in);
        return 1;
    }

    key_len = (int)strlen(key);

    printf("\nИдет обработка...\n");

    // Шифрование/дешифрование
    while ((ch = fgetc(in)) != EOF) {
        ch = ch ^ key[key_index % key_len];
        fputc(ch, out);
        key_index++;
    }

    printf("========================================\n");
    printf("Операция завершена успешно!\n");
    printf("Обработано %d байт\n", key_index);
    printf("Использован ключ: %s\n", key);
    printf("========================================\n");

    fclose(in);
    fclose(out);

    return 0;
} 