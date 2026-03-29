
//int
#define PR(x) printf("x=%u, *x=%d, &x=%u\n", x, *x, &x)
#include <stdio.h>

void main(void) {
    int mas[] = { 100, 200, 300 };
    int* ptr1, * ptr2;
    ptr1 = mas;
    ptr2 = &mas[2];
    PR(ptr1);
    ptr1++;
    PR(ptr1);
    PR(ptr2);
    ++ptr2;
    printf("ptr2 - ptr1 = %u\n", ptr2 - ptr1);
}
//double
#define PR(x) printf("x=%u, *x=%f, &x=%u\n", x, *x, &x)
#include <stdio.h>

void main(void) {
    double mas[] = { 100.5, 200.5, 300.5 };
    double* ptr1, * ptr2;
    ptr1 = mas;
    ptr2 = &mas[2];
    PR(ptr1);
    ptr1++;
    PR(ptr1);
    PR(ptr2);
    ++ptr2;
    printf("ptr2 - ptr1 = %u\n", ptr2 - ptr1);
}