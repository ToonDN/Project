#ifndef FIGURES_H
#define FIGURES_H

struct point
{
    double posx;
    double posy;
};


//  class Square
//  {
    
//  public:
//     point center; 
//     double length; //height y
//     double width; //height x
//     const double dx= 0.05; // actual value to be decided
    
//     void show_var(); // prints the values
//     void set_var(point c,double l, double w);// change the values 
    
     
//  };
 
class Circle
{
    
public:
    point center;
    double radius;
    const double dx= 0.05; // actual value to be decided

    void show_var();// prints the values
    void set_var(point c,double r);// change the values 
    
};

class Bezier
{
public:
    point P0;
    point P1;
    point P2;
    const double dt= 0.01; // actual value to be decided

    void show_var(); // prints the values
    void set_var(point P0,point P1, point P2); // change the values 
    
};

class Grid
{
    public:
    point origin;
    int max_x;
    int max_y;
    const double dx= 0.05; // actual value to be decided
};

point makepoint(double x, double y);

// Square makeSquare(point c, double l, double h);


Circle makeCircle(point c, double r);


Bezier makeBezier(point p0, point p1, point p2);

void testfigures();
#endif 