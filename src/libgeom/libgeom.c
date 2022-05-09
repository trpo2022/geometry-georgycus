#include <libgeom.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SQR(x) x* x

int init(int numberOf)
{
    char circleEx[7] = {"circle"};
    char triangleEx[9] = {"triangle"};
    char input[50] = {'0'};
    int len = 0;
    int countStart = 0;
    printf("Enter %d figure\nexample: triangle(x1 y1, x2 y2, x3 y3, x4 y4), "
           "circle(x1 y2, radius)\n",
           numberOf);
    while ((input[len] = getchar()) != '\n') {
        if (input[len] == '(') {
            countStart = len;
        }
        len++;
    }
    input[len] = '\0';

    if ((input[0] == circleEx[0]) || (input[0] == circleEx[0] - ' ')) {
        if (figure_check(input, circleEx) == 0) {
            if (converter(input, len, countStart, 1) == 0)
                return 100;
        }

    } else if (
            (input[0] == triangleEx[0]) || (input[0] == triangleEx[0] - ' ')) {
        if (figure_check(input, triangleEx) == 0) {
            if (converter(input, len, countStart, 2) == 0)
                return 100;
        }
    } else {
        printf("Please, enter the correct figure! Expected: 'circle' or "
               "'triangle'.\n");
        return 0;
    }
    return 0;
}

int figure_check(char a[], char b[])
{
    for (int i = 1; a[i] != '('; i++) {
        if ((a[i] == b[i]) || (a[i] == b[i] - ' ')) {
            continue;
        } else {
            printf("Undefined figure. Maybe you put something between command "
                   "and '(', check it.\n");
            return 0;
        }
    }
    return 0;
}

int converter(char input[], int len, int countStart, int answer_point)
{
    for (int j = countStart + 1; j < len - 1; j++) {
        if ((input[j] == ',') || (input[j] == '.') || (input[j] == ' ')
            || ((input[j] >= '0') && (input[j] <= '9')))
            continue;
        else {
            printf("Incorrect input!\n");
            return 0;
        }
    }

    if (input[len - 1] != ')') {
        printf("Expected )");
        return 0;
    }

    char converter[20];
    Circle cir_obj;
    Triangle tr_obj;
    int answer = 0;

    if (answer_point == 1) {
        while (input[countStart] != '\0') {
            int k = 0;
            for (countStart += 1; countStart < len; countStart++) {
                if (input[countStart] == ' ' || input[countStart] == ','
                    || input[countStart] == ')') {
                    continue;
                } else {
                    if (input[countStart + 1] == ' '
                        || input[countStart + 1] == ','
                        || input[countStart + 1] == ')') {
                        converter[k] = input[countStart];
                        converter[k + 1] = '\0';
                        countStart++;
                        answer++;
                        break;
                    }
                    converter[k] = input[countStart];
                    k++;
                }
            }
            if (answer == 1) {
                cir_obj.center.x = atof(converter);
            }
            if (answer == 2) {
                cir_obj.center.y = atof(converter);
            }
            if (answer == 3) {
                cir_obj.radius = atof(converter);
            }
        }
    }
    answer = 0;
    if (answer_point == 2) {
        while (input[countStart] != '\0') {
            int k = 0;
            for (countStart += 1; countStart < len; countStart++) {
                if (input[countStart] == ' ' || input[countStart] == ','
                    || input[countStart] == ')') {
                    continue;
                } else {
                    if (input[countStart + 1] == ' '
                        || input[countStart + 1] == ','
                        || input[countStart + 1] == ')') {
                        converter[k] = input[countStart];
                        converter[k + 1] = '\0';
                        countStart++;
                        answer++;
                        break;
                    }
                    converter[k] = input[countStart];
                    k++;
                }
            }
            switch (answer) {
            case 1:
                tr_obj.p[0].x = atof(converter);
                break;

            case 2:
                tr_obj.p[0].y = atof(converter);
                break;

            case 3:
                tr_obj.p[1].x = atof(converter);
                break;

            case 4:
                tr_obj.p[1].y = atof(converter);
                break;

            case 5:
                tr_obj.p[2].x = atof(converter);
                break;

            case 6:
                tr_obj.p[2].y = atof(converter);
                break;

            case 7:
                tr_obj.p[3].x = atof(converter);
                break;

            case 8:
                tr_obj.p[3].y = atof(converter);
                break;
            }
        }
    }

    if (answer_point == 1) {
        printf("Circle's x = %.2lf, y = %.2lf\n",
               cir_obj.center.x,
               cir_obj.center.y);
        printf("Circle's radius = %.2lf\n", cir_obj.radius);
        printf("Perimeter of circle = %lf\n",
               format_circle(&cir_obj)->perimetr);
        printf("Square of circle = %lf\n", format_circle(&cir_obj)->squre);
    }
    if (answer_point == 2) {
        if ((tr_obj.p[0].x != tr_obj.p[3].x)
            && (tr_obj.p[0].y != tr_obj.p[3].y)) {
            printf("First and last coordinate can't be different!\n");
            return -1;
        }

        for (int k = 0; k < 4; k++) {
            printf("Triangle's x%d = %.2lf, y%d = %.2lf\n",
                   k + 1,
                   tr_obj.p[k].x,
                   k + 1,
                   tr_obj.p[k].y);
        }
        printf("Perimeter of triangle = %.2lf\n",
               format_triangle(&tr_obj)->perimetr);
        printf("Square of circle = %lf\n", format_triangle(&tr_obj)->squre);
    }
    return 0;
}

Triangle* format_triangle(Triangle* tr)
{
    double first_side = sqrt(
            SQR((tr->p[1].x - tr->p[0].x)) + SQR((tr->p[1].y - tr->p[0].y)));
    double second_side = sqrt(
            SQR((tr->p[2].x - tr->p[1].x)) + SQR((tr->p[2].y - tr->p[1].y)));
    double third_side = sqrt(
            SQR((tr->p[3].x - tr->p[2].x)) + SQR((tr->p[3].y - tr->p[2].y)));
    tr->perimetr = first_side + second_side + third_side;
    double halfp = tr->perimetr / 2;
    tr->squre
            = sqrt(halfp * (halfp - first_side) * (halfp - second_side)
                   * (halfp - third_side));
    return tr;
}

Circle* format_circle(Circle* cir)
{
    cir->squre = M_PI * SQR(cir->radius);
    cir->perimetr = 2 * M_PI * cir->radius;
    return cir;
}