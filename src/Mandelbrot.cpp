#include "Mandelbrot.h"

double map(double x, double irMin, double irMax, double orMin, double orMax) {
	double slope = (orMax - orMin) / (irMax - irMin);
	return (x - irMin) * slope + orMin;
}

int Mandelbrot(double cr, double ci, int iterations) {
	double zr = 0, zi = 0;
	int i = 0;
	double temp;
	while (zr * zr + zi * zi <= 4.0 && i < iterations) {
		temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}