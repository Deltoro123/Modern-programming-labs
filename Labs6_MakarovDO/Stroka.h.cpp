#ifndef STROKA_H
#define STROKA_H

#include <iostream>
using namespace std;

class Stroka {
private:
    char* str;      // указатель на динамическую память для строки
    int length;     // длина строки

public:
    // Конструкторы
    Stroka();                                    // конструктор по умолчанию
    Stroka(const char*);                         // конструктор из C-строки
    Stroka(const Stroka&);                       // конструктор копирования
    Stroka(int size);                            // конструктор с заданным размером
    
    // Деструктор
    ~Stroka();                                    // освобождает динамическую память
    
    // Перегруженные операции
    Stroka& operator=(const Stroka&);             // присваивание
    Stroka operator+(const Stroka&) const;        // сцепление (возвращает новую строку)
    bool operator==(const Stroka&) const;         // сравнение
    
    // Методы
    int dllina() const;                           // возвращает длину строки
    void vvod();                                  // ввод строки
    void vyvod() const;                           // вывод строки
    
    // Дополнительные методы для работы со строками (собственные реализации)
    static int str_len(const char* s);            // вычисление длины строки
    static void str_cpy(char* dest, const char* src);  // копирование строки
    static void str_cat(char* dest, const char* src);  // конкатенация строк
    static int str_cmp(const char* s1, const char* s2); // сравнение строк
};

#endif