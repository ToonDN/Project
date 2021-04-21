#include "figures.h"
#include <stdio.h>

void Square::show_var()
{
    printf("Center of square: x = %f, y = %f \n", center.posx, center.posy);
    printf("Shape of square: length = %f ,width = %f\n", length, width);
}

void Square::set_var(point c, double l, double b)
{
    center = c;
    length = l;
    width = b;
}

void Circle::show_var()
{
    printf("Center of circle: x = %f, y = %f\n", center.posx, center.posy);
    printf("Radius of circle = %f", radius);
}
void Circle::set_var(point c, double r)
{
    center = c;
    radius = r;
}

void Bezier::show_var()
{
    printf("Defining points of the Bezier curve:\n ");
    printf("P0: x = %f, y = %f\n", P0.posx, P0.posy);
    printf("P1: x = %f, y = %f\n", P1.posx, P1.posy);
    printf("P2: x = %f, y = %f\n", P2.posx, P2.posy);
}

void Bezier::set_var(point A, point B, point C)
{
    P0 = A;
    P1 = B;
    P2 = C;
}

point makepoint(double x, double y)
{
    point p;
    p.posx = x;
    p.posy = y;
    return p;
}
Square makeSquare(point c, double l, double h)
{
    Square sq;
    sq.center = c;
    sq.length = l;
    sq.width = h;
    return sq;
}

Circle makeCircle(point c, double r)
{
    Circle cir;
    cir.center = c;
    cir.radius = r;
    return cir;
}

Bezier makeBezier(point p0, point p1, point p2)
{
    Bezier bez;
    bez.P0 = p0;
    bez.P1 = p1;
    bez.P2 = p2;
    return bez;
}

void testfigures()
{
    //test point
    point punt = makepoint(1, 8);
    
    printf("%lf\n", punt.posx);
    printf("%lf\n", punt.posy);

    // test square
    Square rechthoek = makeSquare(makepoint(15, 15), 5, 10);
    rechthoek.show_var();

    // // test circle
    Circle cirkel = makeCircle(makepoint(60, 45), 8);
    cirkel.show_var();
    
    // //test Bezier
    Bezier Bez = makeBezier(makepoint(15, 15), makepoint(20, 35), makepoint(15, 15));
    Bez.show_var();
}