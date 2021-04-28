#ifndef __MANDELBROT__
#define __MANDELBROT__

double map(double x, double irMin, double irMax, double orMin, double orMax);
int Mandelbrot(double cr, double ci, int iterations);

#endif