#include "fractal.h"

int main()
{   
    //Image dimensions
    const int width = 2000;
    const int height = 2000;
    //Extreme coords of image
    double x0 = -2.25;//-0.34853774148008254;
    double x1 = 0.75;//-0.34831493420245574;
    double y0 = -1.5;//-0.6065922085831237;
    double y1 = y0 + x1 - x0;
    //Create an image file to output to
    std::ofstream image;
    image.open("img/image.ppm");
    //Specify file type, width, height and the max color of the image
    image << "P3" << std::endl;
    image << width << " " << height << std::endl;
    image << "255" << std::endl;
    //Main loop:
    for (int j = 0; j < height; j++)
    {
        std::cerr << "\rRendering: " << j + 1 << " out of " << height << " complete..." << std::flush;
        for (int i = 0; i < width; i++)
        {
            double c_real = map(i, 0, (double)width-1.0, x0, x1);
            double c_imaginary = map(j, 0, (double)height-1.0, y0, y1);
            int n = (int)map(Mandelbrot(c_real, c_imaginary), 0, ITERATIONS, 0, 255);
            int r, g, b;

            r = ((int)map((double)n * n, 0, 255.0*255.0, 0, 255)) % 255;
            g = n % 255;
            b = ((int)map(sqrt(n), 0, sqrt(255), 0, 255)) % 255;

            image << r << " " << g << " " << b << std::endl;
        }
    }
    std::cerr << "\nDone";
    image.close();
    return 0;
}