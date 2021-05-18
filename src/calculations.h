

#ifndef CALCULATIONS_H
#define CALCULATIONS_H
/**
 * @brief converts x and y coordinates to an array wiht 2 servo values
 * 
 * @param x 
 * @param y 
 * @param values 
 * @return unsigned short* 
 */
unsigned short *valuesFromCoordinates(double x, double y, unsigned short values[2]);

#endif