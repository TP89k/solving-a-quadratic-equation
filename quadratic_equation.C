//----------------------------------------
//Решение уравнений типа ax^2 + bx + c = 0


#include <stdio.h>
#include <math.h>
#include <TXLib.h>

typedef struct {
    double x1;
    double x2;
    int num_roots;
} Roots;


//@param [in]  a  кожффицент a
//@param [in]  b  коэффицент b
//@param [in]  c  коэффицент c
//@param [out] вывод вида уравнения на экран пользователя


void input_yravn(double *a, double *b, double *c) {

    printf("Уравнение: %.2fx^2", *a);
    if (*b >= 0) {
        printf(" + %.2fx", *b);
    } else {
        printf(" - %.2fx", -(*b));
    }
    if (*c >= 0) {
        printf(" + %.2f = 0\n", *c);
    } else {
        printf(" - %.2f = 0\n", -(*c));
    }
}


//@param [in]  a  кожффицент a
//@param [in]  b  коэффицент b
//@param [in]  c  коэффицент c
//@param [out] discrim вывод дискриминанта уравнения

double cal_discrim(double a, double b, double c) {
    return b * b - 4 * a * c;
}

//@param [in]  b  коэффицент b
//@param [in]  c  коэффицент c
//@param [out] roots инфрмация о количестве корней и их значения (первый корень)

Roots solve_linear(double b, double c) {
    Roots roots;

    if (b == 0) {
        if (c == 0) {
            roots.num_roots = -1;
            roots.x1 = roots.x2 = 0;
        } else {
            roots.num_roots = 0;
            roots.x1 = roots.x2 = 0;
        }
    } else {
        roots.num_roots = 1;
        roots.x1 = -c / b;
        roots.x2 = roots.x1;
    }

    return roots;
}

//@param [in]  a  кожффицент a
//@param [in]  b  коэффицент b
//@param [in]  c  коэффицент c
//@param [out] roots вывод значения второго корня

Roots solve_quadr(double a, double b, double c) {
    Roots roots;

    double discrim = cal_discrim(a, b, c);

    if (discrim > 0) {
        roots.num_roots = 2;
        roots.x1 = (-b + sqrt(discrim)) / (2 * a);
        roots.x2 = (-b - sqrt(discrim)) / (2 * a);
    } else if (discrim == 0) {
        roots.num_roots = 1;
        roots.x1 = roots.x2 = -b / (2 * a);
    } else {
        roots.num_roots = 0;
        roots.x1 = roots.x2 = 0;
    }

    return roots;
}

//@param [in]  roots  корни уравнения
//@param [in]  x1 первый корень уравнения
//@param [in]  x2 второй корень уравнения

void print_res(Roots roots) {
    printf("\n==== РЕЗУЛЬТАТЫ ====\n");

    switch (roots.num_roots) {
        case -1:
            printf("Уравнение имеет бесконечно много корней\n");
            break;
        case 0:
            printf("Уравнение не имеет корней\n");
            break;
        case 1:
            printf("Уравнение имеет один корень:\n");
            printf("x = %.4f\n", roots.x1);
            break;
        case 2:
            printf("Уравнение имеет два корня:\n");
            printf("x1 = %.4f\n", roots.x1);
            printf("x2 = %.4f\n", roots.x2);
            break;
    }
}



int main() {
    double a, b, c;
    Roots roots;

    printf("==== КАЛЬКУЛЯТОР КВАДРАТНЫХ УРАВНЕНИЙ ====\n");
    printf("Введите три коэффицента (каждое с новой строки):\n");

    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    printf("\nВы ввели:\n");
    printf("Первое число: %.2f\n", a);
    printf("Второе число: %.2f\n", b);
    printf("Третье число: %.2f\n", c);
    input_yravn(&a, &b, &c);

    if (a == 0) {
        roots = solve_linear(b, c);
    } else {
        roots = solve_quadr(a, b, c);
    }

    print_res(roots);

    return 0;
}