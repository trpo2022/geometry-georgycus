#ifndef GEOM
#define GEOM

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p[4];
    double squre;
    double perimetr;
} Triangle;

typedef struct {
    Point center;
    double radius;
    double squre;
    double perimetr;
} Circle;

int init(int numberOf);
int figure_check(char a[], char b[]);
int converter(char input[], int len, int countStart, int answer_point);
Triangle* format_triangle(Triangle* tr);
Circle* format_circle(Circle* cir);

#endif