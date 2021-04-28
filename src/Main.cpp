#include <iostream>
#include <fstream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <string>
#include "Mandelbrot.h"

const int imageWidth = 702;
const int imageHeight = 402;
int iterations = 10;
double Rmin = -2.5, Rmax = 1;
double Imin = -1, Imax = 1;

int pixels[imageWidth][imageHeight][3];

double x, y, r, g, b;
int iter;

sf::Image image;
sf::Texture texture;
sf::Sprite sprite;
sf::Text text;

void execThread(int y1, int y2, int x1, int x2) {
	for (int j = y1; j < y2; j++) for (int i = x1; i < x2; i++) {
		x = Rmin + (Rmax - Rmin) * i / imageWidth;
		y = Imin + (Imax - Imin) * j / imageHeight;
		iter = Mandelbrot(x, y, iterations);

		r = iter % 255;
		g = map(iter, 0, iterations, 0, 255);
		b = 54;

		pixels[i][j][0] = r;
		pixels[i][j][1] = g;
		pixels[i][j][2] = b;

		sf::Color col(r, g, b, 0xff);
		image.setPixel(i, j, sf::Color(col));
	}
}

void screenshot() {
	std::ofstream scr("screenshot.ppm");
	scr << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
	std::cout << "writing scr\n";
	for (int j = 0; j < imageHeight; j++) for (int i = 0; i < imageWidth; i++) {
		scr << pixels[i][j][0] << " " << pixels[i][j][1] << " " << pixels[i][j][2] << "\n";
	}
	std::cout << "complete";
}

void zoom(sf::Event event, double zoom) {
	double cr, ci, temp;
	cr = Rmin + (Rmax - Rmin) * event.mouseButton.x / imageWidth;
	ci = Imin + (Imax - Imin) * event.mouseButton.y / imageHeight;

	double Rfactor = (Rmax - Rmin) / 2 / zoom;
	double Ifactor = (Imax - Imin) / 2 / zoom;

	temp = cr - Rfactor;
	Rmax = cr + Rfactor;
	Rmin = temp;

	temp = ci - Ifactor;
	Imax = ci + Ifactor;
	Imin = temp;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(imageWidth, imageHeight), "Window");
	image.create(imageWidth, imageHeight);
	
	sf::Font font;
	font.loadFromFile("ARIALBD.ttf");

	text.setFont(font);

	while (window.isOpen()) {
		window.clear();
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				double side = 0.1 * (Rmax - Rmin);
				double up = 0.1 * (Imax - Imin);

				if (event.key.code == sf::Keyboard::W) { Imin -= up; Imax -= up; }
				if (event.key.code == sf::Keyboard::S) { Imin += up; Imax += up; }
				if (event.key.code == sf::Keyboard::A) { Rmin -= side; Rmax -= side; }
				if (event.key.code == sf::Keyboard::D) { Rmin += side; Rmax += side; }

				if (event.key.code == sf::Keyboard::Space) { screenshot(); }
			}
			if (event.type == sf::Event::MouseWheelScrolled) {
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
					if (event.mouseWheelScroll.delta > 0) iterations *= 2;
					if (event.mouseWheelScroll.delta < 0) iterations /= 2;
				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) zoom(event, 5.0);
				if (event.mouseButton.button == sf::Mouse::Right) zoom(event, 0.2);
			}
			
		}

		std::thread t1(execThread, 0, imageHeight / 3, 0, imageWidth);
		std::thread t2(execThread, imageHeight / 3, 2 * imageHeight / 3, 0, imageWidth);
		std::thread t3(execThread, 2 * imageHeight / 3, imageHeight, 0, imageWidth);
		t1.join();
		t2.join();
		t3.join();

		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		
		text.setString("Iterations: " + std::to_string(iterations));
		window.draw(text);
		window.display();
	}
}