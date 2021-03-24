#ifndef FIGURES_H
#define FIGURES_H

struct point
{
    double posx;
    double posy;
};

// de draw funcites staan voorlopig in commentaar, want we willen die waarschijnlijk in drawer definieren

 class Square
 {
    
 public:
    point center; 
    double length; //height y
    double width; //height x
    
    void show_var(); // prints the values
    void set_var(point c,double l, double w);// change the values 
    // void draw(); // draws the square 
     
 };
 
class Circle
{
    
public:
    point center;
    double radius;

    void show_var();// prints the values
    void set_var(point c,double r);// change the values 
    // void draw(); // draws the square
};

class Bezier
{
public:
    point P0;
    point P1;
    point P2;

    void show_var(); // prints the values
    void set_var(point P0,point P1, point P2); // change the values 
    // void draw(); // draws Bezier curve
};


#endif 