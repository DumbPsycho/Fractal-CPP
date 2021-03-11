#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

const int ITERATIONS = 100;
double map(double input, double iRange_start, double iRange_end, double oRange_start, double oRange_end);
int Mandelbrot(double c_real, double c_imaginary);