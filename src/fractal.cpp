//Map function and fractal code
#include "fractal.h"

double map(double input, double iRange_min, double iRange_max, double oRange_min, double oRange_max)
{
    double slope = 1.0 * (oRange_max - oRange_min) / (iRange_max - iRange_min);
    return oRange_min + slope * (input - iRange_min);
}

int Mandelbrot(double c_real, double c_imaginary)
{
    double z_real = c_real;
    double z_imaginary = c_imaginary;
    int i = 0;
    while (i <= ITERATIONS && z_real * z_real + z_imaginary * z_imaginary < 4.0)
    {
        double temp = z_real * z_real - z_imaginary * z_imaginary + c_real;
        z_imaginary = 2.0 * z_real * z_imaginary + c_imaginary;
        z_real = temp;
        i++;
    }
    return i;
}


