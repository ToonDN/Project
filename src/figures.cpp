#include "figures.h"
#include <stdio.h>


void Square::show_var() 
{
    printf("Center of square: x = %f, y = %f \n", center.posx,center.posy);
    printf("Shape of square: length = %f ,width = %f\n",length,width);
}

void Square::set_var(point c,double l,double b){
    center=c;
    length=l;
    width=b;
}

void Circle::show_var(){
    printf("Center of circle: x = %f, y = %f\n", center.posx,center.posy);
    printf("Radius of circle = %f", radius);

}
void Circle::set_var(point c, double r){
    center=c;
    radius=r;
}

void Bezier::show_var(){
    printf("Defining points of the Bezier curve:\n ");
    printf("P0: x = %f, y = %f\n",P0.posx,P0.posy);
    printf("P1: x = %f, y = %f\n",P1.posx,P1.posy);
    printf("P2: x = %f, y = %f\n",P2.posx,P2.posy);
}

void Bezier::set_var(point A,point B,point C){
    P0=A;
    P1=B;
    P2=C;
}