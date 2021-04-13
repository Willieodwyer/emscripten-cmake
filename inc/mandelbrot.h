const int WIDTH = 800;
const int HEIGHT = 600;
unsigned char image[WIDTH * HEIGHT * 4];

#include <cmath>

unsigned char colour(int iteration, int offset, int scale) {
  iteration = ((iteration * scale) + offset) % 1024;
  if (iteration < 256) {
    return iteration;
  } else if (iteration < 512) {
    return 255 - (iteration - 255);
  } else {
    return 0;
  }
}

#include <complex>
using namespace std;

int mandelbrot_complex(double x, double y, int maxiterations)  {
    complex<double> point(x, y);
    complex<double> z(0, 0);
    int nb_iter = 0;
    while (abs (z) < 2 && nb_iter <= maxiterations) {
        z = z * z + point;
        nb_iter++;
    }
    if (nb_iter < maxiterations)
       return (255*nb_iter)/maxiterations;
    else
       return 0;
}

int mandelbrot_real(double x0, double y0, int maxiterations) {
  double a = 0.0, b = 0.0, rx = 0.0, ry = 0.0;
  int iterations = 0;
  while (iterations < maxiterations && (abs(rx * rx + ry * ry) <= 4.0)) {
    rx = a * a - b * b + x0;
    ry = 2.0 * a * b + y0;
    a = rx;
    b = ry;
    iterations++;
  }
  return iterations;
}

double scale(double domainStart, double domainLength, double screenLength, double step) {
  return domainStart + domainLength * ((step - screenLength) / screenLength);
}

void mandelbrot(int maxIterations, double cx, double cy, double diameter) {
  double verticalDiameter = diameter * HEIGHT / WIDTH;
  for(double x = 0.0; x < WIDTH; x++) {
    for(double y = 0.0; y < HEIGHT; y++) {
      // map to mandelbrot coordinates
      double rx = scale(cx, diameter, WIDTH, x);
      double ry = scale(cy, verticalDiameter, HEIGHT, y);
      int iterations = mandelbrot_real(rx, ry, maxIterations);
      int idx = ((x + y * WIDTH) * 4);
      // set the red and alpha components
      image[idx] = iterations == maxIterations ? 0 : colour(iterations, 0, 4);
      image[idx + 1] = iterations == maxIterations ? 0 : colour(iterations, 128, 4);
      image[idx + 2] = iterations == maxIterations ? 0 : colour(iterations, 356, 4);
      image[idx + 3] = 255;
    }
  }
}

unsigned char* getImage() {
  return &image[0];
}