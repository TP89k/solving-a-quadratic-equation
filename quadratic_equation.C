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
// struct Equation_data - структура коэффицентов и корней уравнения + количество корней
// a первый коэффицент уравнения a
// b второй коэффицент уравнения b
// c третий коэффицент уравнения c
// x1 первый корень уравнения
// x2 второй корень уравнения
// num_roots количество корней
//----------------------------------------

typedef struct
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    int num_roots;
} Equation_data;


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
//@param [in] Equation_data - структура коэффицентов и корней уравнения + количество корней
//[out] вывод вида уравнения на экран пользователя
//----------------------------------------

void print_equation(Equation_data equation_data)
{
    printf("Уравнение: %.4fx^2", equation_data.a);
    if (equation_data.b >= 0) {
        printf(" + %.4fx", equation_data.b);
    }
    else
    {
        printf(" - %.4fx", -(equation_data.b));
    }

    if (equation_data.c >= 0) {
        printf(" + %.4f = 0\n", equation_data.c);
    }
    else {
        printf(" - %.4f = 0\n", -(equation_data.c));
    }
}


//----------------------------------------
//@param [out] Equation_data - структура коэффицентов и корней уравнения + количество корней
//----------------------------------------

 Equation_data input()
 {
    Equation_data equation_data;
    double a = NAN;
    double b = NAN;
    double c = NAN;

    printf("==== РЕШЕНИЕ КВАДРАТНЫХ УРАВНЕНИЙ ====\n");
    printf("Введите три коэффицента a,b,c (каждое число с новой строки):\n");

    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);

    equation_data.a=a;
    equation_data.b=b;
    equation_data.c=c;

    printf("\nВы ввели:\n");
    printf("Первый коэфицент a: %.4f\n", equation_data.a);
    printf("Второй коэфицент b: %.4f\n", equation_data.b);
    printf("Третий коэфицент c: %.4f\n", equation_data.c);
    //  print_equation(coefficients);  //

    return equation_data;
 }


//----------------------------------------
//@param [in] Equation_data - структура коэффицентов и корней уравнения + количество корней
//@param [out] discriminant вывод дискриминанта уравнения
//----------------------------------------

double calc_discriminant(Equation_data equation_data)
{
    return equation_data.b * equation_data.b - 4 * equation_data.a * equation_data.c;
}


//----------------------------------------
//@param [in] Equation_data - структура коэффицентов и корней уравнения + количество корней
//@param [out] Equation_data - структура коэффицентов и корней уравнения + количество корней
//----------------------------------------

Equation_data solve_quadratic_equation(Equation_data equation_data)
{

    double discriminant = calc_discriminant(equation_data);

    if (check_epsilon_neighborhood(equation_data.a, 0)==1)
    {

        if (discriminant > 0+EPSILON) {
            equation_data.num_roots = 2;
            equation_data.x1 = (-equation_data.b + sqrt(discriminant)) / (2 * equation_data.a);
            equation_data.x2 = (-equation_data.b - sqrt(discriminant)) / (2 * equation_data.a);
        }
        else if (check_epsilon_neighborhood(discriminant, 0)==0) {
            equation_data.num_roots = 1;
            equation_data.x1 = equation_data.x2 = -equation_data.b / (2 * equation_data.a);
        }
        else {
            equation_data.num_roots = 0;
            equation_data.x1 = equation_data.x2 = 0;
        }

    }

    else if (check_epsilon_neighborhood(equation_data.a, 0)==0)
    {
        if (check_epsilon_neighborhood(equation_data.b, 0)==0) {
            if (check_epsilon_neighborhood(equation_data.c, 0)==0) {
                equation_data.num_roots = -1;
                equation_data.x1 = equation_data.x2 = 0;
            }
            else {
                equation_data.num_roots = 0;
                equation_data.x1 = equation_data.x2 = 0;
            }
            }
        else {
            equation_data.num_roots = 1;
            equation_data.x1 = -equation_data.c / equation_data.b;
            equation_data.x2 = equation_data.x1;
        }
    }

    return equation_data;
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
    Equation_data equation_data;

    equation_data.a=a;
    equation_data.b=b;
    equation_data.c=c;

    equation_data = solve_quadratic_equation(equation_data);

    if ((check_epsilon_neighborhood(equation_data.x1,x1_specified)==0)  && (check_epsilon_neighborhood(equation_data.x2,x2_specified)==0) && (number_of_solutions == equation_data.num_roots)){
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
    Equation_data tests[AMOUNT_OF_TESTS] = {
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
        not_failed += run_one_test(tests[i].a, tests[i].b, tests[i].c, tests[i].x1, tests[i].x2, tests[i].num_roots);
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
//@param [in]  Equation_data - структура коэффицентов и корней уравнения + количество корней
//@param [in]  x1 первый корень уравнения
//@param [in]  x2 второй корень уравнения
//----------------------------------------

void print_results(Equation_data equation_data)
{
    printf("\n==== РЕЗУЛЬТАТЫ ====\n");

    switch (equation_data.num_roots) {
        case -1:
            printf("Уравнение имеет бесконечно много корней\n");
            break;
        case 0:
            printf("Уравнение не имеет корней\n");
            break;
        case 1:
            printf("Уравнение имеет один корень:\n");
            printf("x = %.12f\n", equation_data.x1);
            break;
        case 2:
            printf("Уравнение имеет два корня:\n");
            printf("x1 = %.12f\n", equation_data.x1);
            printf("x2 = %.12f\n", equation_data.x2);
            break;
    }
}



int main() {

    Equation_data equation_data;

    testing_program();

    equation_data = input();

    equation_data = solve_quadratic_equation(equation_data);
    print_results(equation_data);

    return 0;
}