//----------------------------------------
//Решение уравнений типа ax^2 + bx + c = 0
//----------------------------------------

#include <stdio.h>
#include <math.h>
#include <TXLib.h>


//----------------------------------------
//const int Sum_of_tests - размер массива тестовых примеров
//----------------------------------------

const int AMOUNT_OF_TESTS = 6;


//----------------------------------------
//const int N - количество данных тестового примера
//----------------------------------------

const int N = 6;


//----------------------------------------
//const float EPSILON - константа эпсилон окрестности вычислений
//----------------------------------------

const float EPSILON = 0.00001;


//----------------------------------------
// struct Roots - структура корней уравнения
// x1 первый корень уравнения
// x2 второй корень уравнения
// num_roots количество корней
//----------------------------------------

typedef struct
{
    double x1;
    double x2;
    int num_roots;
} Roots;


//----------------------------------------
// struct Coefficients - структура корней уравнения
// a первый коэффицент уравнения a
// b второй коэффицент уравнения b
// c третий коэффицент уравнения c
//----------------------------------------

typedef struct
{
    double a;
    double b;
    double c;
} Coefficients;


//----------------------------------------
//@param [in] double number число, для которого проверяется эпсилон окрестность
//@param [in] double program_number число, вокруг которого проверяется эпсилон окрестность
//[out] int число (1 - если True и 0 - если False)
//----------------------------------------

int check_epsilon_neighborhood(double number, double program_number)
{
    if (!((number<program_number+EPSILON) && (number>program_number-EPSILON)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//----------------------------------------
//@param [in] Coefficients структура коэффицентов a,b,c
//[out] вывод вида уравнения на экран пользователя
//----------------------------------------

void print_equation(Coefficients coefficients)
{
    printf("Уравнение: %.4fx^2", coefficients.a);
    if (coefficients.b >= 0) {
        printf(" + %.4fx", coefficients.b);
    }
    else
    {
        printf(" - %.4fx", -(coefficients.b));
    }

    if (coefficients.c >= 0) {
        printf(" + %.4f = 0\n", coefficients.c);
    }
    else {
        printf(" - %.4f = 0\n", -(coefficients.c));
    }
}


//----------------------------------------
//@param [out] Coefficients структура коэффицентов a,b,c
//----------------------------------------

 Coefficients input()
 {
    Coefficients coefficients;
    double a = NAN;
    double b = NAN;
    double c = NAN;

    printf("==== РЕШЕНИЕ КВАДРАТНЫХ УРАВНЕНИЙ ====\n");
    printf("Введите три коэффицента a,b,c (каждое число с новой строки):\n");

    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    coefficients.a=a;
    coefficients.b=b;
    coefficients.c=c;

    printf("\nВы ввели:\n");
    printf("Первый коэфицент a: %.4f\n", coefficients.a);
    printf("Второй коэфицент b: %.4f\n", coefficients.b);
    printf("Третий коэфицент c: %.4f\n", coefficients.c);
    //  print_equation(coefficients);  //

    return coefficients;
 }


//----------------------------------------
//@param [in] Coefficients структура коэффицентов a,b,c
//@param [out] discriminant вывод дискриминанта уравнения
//----------------------------------------

double calc_discriminant(Coefficients coefficients)
{
    return coefficients.b * coefficients.b - 4 * coefficients.a * coefficients.c;
}


//----------------------------------------
//@param [in] Coefficients структура коэффицентов a,b,c
//@param [out] Roots структура значений уравнения x1,x2 и количества решений num_roots
//----------------------------------------

Roots solve_quadratic_equation(Coefficients coefficients)
{
    Roots roots;

    double discriminant = calc_discriminant(coefficients);

    if (check_epsilon_neighborhood(coefficients.a, 0)==1)
    {

        if (discriminant > 0+EPSILON) {
            roots.num_roots = 2;
            roots.x1 = (-coefficients.b + sqrt(discriminant)) / (2 * coefficients.a);
            roots.x2 = (-coefficients.b - sqrt(discriminant)) / (2 * coefficients.a);
        }
        else if (check_epsilon_neighborhood(discriminant, 0)==0) {
            roots.num_roots = 1;
            roots.x1 = roots.x2 = -coefficients.b / (2 * coefficients.a);
        }
        else {
            roots.num_roots = 0;
            roots.x1 = roots.x2 = 0;
        }

    }

    else if (check_epsilon_neighborhood(coefficients.a, 0)==0)
    {
        if (check_epsilon_neighborhood(coefficients.b, 0)==0) {
            if (check_epsilon_neighborhood(coefficients.c, 0)==0) {
                roots.num_roots = -1;
                roots.x1 = roots.x2 = 0;
            }
            else {
                roots.num_roots = 0;
                roots.x1 = roots.x2 = 0;
            }
            }
        else {
            roots.num_roots = 1;
            roots.x1 = -coefficients.c / coefficients.b;
            roots.x2 = roots.x1;
        }
    }

    return roots;
}


//----------------------------------------
//@param [in] double a  коэффицент а
//@param [in] double b  коэффицент b
//@param [in] double c  коэффицент c
//@param [in] double x1_specified  тестовый корень 1
//@param [in] double x2_specified  тестовый корень 2
//@param [in] int number_of_solutions  количество тестовых корней
//@param [out] 1, если тестовые корни совпадают с настоящим, иначе 0
//----------------------------------------

int run_one_test(double a, double b, double c, double x1_specified , double x2_specified, int number_of_solutions)
{
    Coefficients coefficients;
    Roots roots;

    coefficients.a=a;
    coefficients.b=b;
    coefficients.c=c;

    roots = solve_quadratic_equation(coefficients);

    if ((check_epsilon_neighborhood(roots.x1,x1_specified)==0)  && (check_epsilon_neighborhood(roots.x2,x2_specified)==0) && (number_of_solutions == roots.num_roots)){
        return 1;
    }
    else{
        return 0;
    }
}


//----------------------------------------
//@param [out] int not_failed количество верно пройденных тестов
//----------------------------------------

int run_test()
{
    float tests_array[AMOUNT_OF_TESTS][N] = {
          {3,5,-2,0.3333333,-2,2},
          {-2,8,6,-0.645751,4.64575,2},
          {4,-4,1,0.5,0.5,1},
          {7,2,9,0,0,0},
          {0,0,0,0,0,-1},
          {2,-3,1,1,0.5,2}
    };

    int not_failed = 0;
    for (int i = 0; i < AMOUNT_OF_TESTS; i++)
    {
        not_failed += run_one_test(tests_array[i][0], tests_array[i][1], tests_array[i][2], tests_array[i][3], tests_array[i][4], tests_array[i][5]);
    }

    return not_failed;
}


//----------------------------------------
//[out] количество верно пройденных тестов
//----------------------------------------

void testing_program()
{
    int count_tests = run_test();

    printf("ПРОЙДЕНО ТЕСТОВ: %d", count_tests);
    printf(" ИЗ %d\n", AMOUNT_OF_TESTS, "\n");
}


//----------------------------------------
//@param [in]  roots  корни уравнения
//@param [in]  x1 первый корень уравнения
//@param [in]  x2 второй корень уравнения
//----------------------------------------

void print_results(Roots roots)
{
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
            printf("x = %.12f\n", roots.x1);
            break;
        case 2:
            printf("Уравнение имеет два корня:\n");
            printf("x1 = %.12f\n", roots.x1);
            printf("x2 = %.12f\n", roots.x2);
            break;
    }
}



int main() {

    Coefficients coefficients;
    Roots roots;

    testing_program();

    coefficients = input();

    roots = solve_quadratic_equation(coefficients);
    print_results(roots);

    return 0;
}