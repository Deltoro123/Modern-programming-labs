#include "Stroka.h"
#include <iostream>
using namespace std;

// ==================== Статические методы ====================

// Вычисление длины строки (собственная реализация)
int Stroka::str_len(const char* s) {
    int len = 0;
    if (s != nullptr) {
        while (s[len] != '\0') {
            len++;
        }
    }
    return len;
}

// Копирование строки (собственная реализация)
void Stroka::str_cpy(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr) return;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Конкатенация строк (собственная реализация)
void Stroka::str_cat(char* dest, const char* src) {
    if (dest == nullptr || src == nullptr) return;
    // Находим конец dest
    int dest_len = str_len(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

// Сравнение строк (собственная реализация)
int Stroka::str_cmp(const char* s1, const char* s2) {
    if (s1 == nullptr || s2 == nullptr) {
        if (s1 == nullptr && s2 == nullptr) return 0;
        return -1;
    }
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

// ==================== Конструкторы ====================

// Конструктор по умолчанию
Stroka::Stroka() {
    length = 0;
    str = new char[1];
    str[0] = '\0';
}

// Конструктор из C-строки
Stroka::Stroka(const char* s) {
    if (s != nullptr) {
        length = str_len(s);
        str = new char[length + 1];
        str_cpy(str, s);
    }
    else {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }
}

// Конструктор копирования
Stroka::Stroka(const Stroka& other) {
    length = other.length;
    str = new char[length + 1];
    str_cpy(str, other.str);
}

// Конструктор с заданным размером (динамическая память)
Stroka::Stroka(int size) {
    if (size <= 0) {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }
    else {
        length = 0;
        str = new char[size + 1];
        str[0] = '\0';
    }
}

// ==================== Деструктор ====================
Stroka::~Stroka() {
    delete[] str;
}

// ==================== Перегруженные операции ====================

// Оператор присваивания
Stroka& Stroka::operator=(const Stroka& other) {
    if (this != &other) {  // проверка на самоприсваивание
        delete[] str;
        length = other.length;
        str = new char[length + 1];
        str_cpy(str, other.str);
    }
    return *this;
}

// Оператор сцепления (возвращает новую строку)
Stroka Stroka::operator+(const Stroka& other) const {
    Stroka result;
    delete[] result.str;
    result.length = length + other.length;
    result.str = new char[result.length + 1];
    
    str_cpy(result.str, str);
    str_cat(result.str, other.str);
    
    return result;
}

// Оператор сравнения
bool Stroka::operator==(const Stroka& other) const {
    return (str_cmp(str, other.str) == 0);
}

// ==================== Методы ====================

// Определение длины строки
int Stroka::dllina() const {
    return length;
}

// Ввод строки
void Stroka::vvod() {
    char buffer[1000];  // буфер для ввода
    cin >> buffer;
    
    delete[] str;
    length = str_len(buffer);
    str = new char[length + 1];
    str_cpy(str, buffer);
}

// Вывод строки
void Stroka::vyvod() const {
    cout << str;
}