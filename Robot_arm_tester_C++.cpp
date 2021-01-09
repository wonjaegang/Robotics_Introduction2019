#include "pch.h"
#include <iostream>
#include <cmath>
#define PI 3.141592
#define MAX(a,b) (((a)>(b))?(a):(b))
using namespace std;


double a = 150, b = 94.25, d_center = 19.75;


void draw_pixel(double x, double y, double z)  // Function that calculate backward Kinematics. Refer to PDF file to get more information.
{
	double B, C, D, E, F;
	int servo1, servo2, servo3;
	double c, r, k;
	r = sqrt(x * x + y * y - d_center * d_center);
	k = z - (87 + 48);
	c = sqrt(x * x + y * y + k * k);
	B = acos((a * a + c * c - b * b) / (2 * a * c));
	C = acos((a * a + b * b - c * c) / (2 * a * b));
	D = atan2(k, r);
	E = PI - C - B + D;
	F = atan2(r, d_center) - atan2(x, y);
	servo1 = int((PI - F) * (180 / PI) + 0.5);   // Change angle(radian) to Servo motor PWM(voltage) input. It includes rounding.
	servo2 = int((PI / 2 - E) * (180 / PI) + 0.5);
	servo3 = int(C * (255 / PI) + 0.5);
	cout << "Angle(" << servo1 << ", " << servo2 << ", " << servo3 << ")" << endl;  // Print the angle(degree) of servo motors.
	cout << "Location(" << x << ", " << y << ", " << z << ")" << endl;
}


void draw_line(double x0, double y0, double z0, double x1, double y1, double z1) // Function that quantize the line and draw it. Modified from Bresenham's line drawing algorithm
{
	char steep;
	if (MAX(MAX(abs(x1 - x0), abs(y1 - y0)), abs(z1 - z0)) == abs(x1 - x0))  // We need the reference axis which increasing uniformly, and we will regard it as X axis.
	{
		steep = 'x'; cout << "In this line, the reference axis is X axis" << endl;
	}
	if (MAX(MAX(abs(x1 - x0), abs(y1 - y0)), abs(z1 - z0)) == abs(y1 - y0))
	{
		steep = 'y'; cout << "In this line, the reference axis is Y axis" << endl;
		swap(x0, y0); swap(x1, y1);
	}
	if (MAX(MAX(abs(x1 - x0), abs(y1 - y0)), abs(z1 - z0)) == abs(z1 - z0))
	{
		steep = 'z'; cout << "In this line, the reference axis is Z axis" << endl;
		swap(x0, z0); swap(x1, z1);
	}
	double deltax = abs(x1 - x0), deltay = abs(y1 - y0), deltaz = abs(z1 - z0);
	double errory = -(deltax / 2), errorz = -(deltax / 2);
	double x = x0, y = y0, z = z0, x_step = 1, y_step = 1, z_step = 1;
	if (x0 > x1)
		x_step = -1;
	if (y0 > y1)
		y_step = -1;
	if (z0 > z1)
		z_step = -1;
	for (x; x != x1 + x_step; x += x_step)
	{
		switch (steep) // Reorder the axis to the original order and print it.
		{
		case 'x':
			draw_pixel(x, y, z); cout << endl; break;
		case 'y':
			draw_pixel(y, x, z); cout << endl; break;
		case 'z':
			draw_pixel(z, y, x); cout << endl; break;
		default:
			cout << "error" << endl; break;
		}
		errory += deltay;
		errorz += deltaz;
		if (errory >= 0)
		{
			y += y_step;
			errory -= deltax;
		}
		if (errorz >= 0)
		{
			z += z_step;
			errorz -= deltax;
		}
	}
	cout << "This line is over---------------------------------------------------" << endl << endl;
}


int canleachornot(double x, double y, double z) // Function that tells whether the input point is proper or not.
{
	double c, r, k;
	r = sqrt(x * x + y * y - d_center * d_center);
	k = z - (87 + 48);
	c = sqrt(x * x + y * y + k * k);
	double cosB = (a * a + c * c - b * b) / (2 * a * c);
	double cosC = (a * a + b * b - c * c) / (2 * a * b);
	if (abs(cosB) > 1 || abs(cosC) > 1)
	{
		return 1;  // The point(x, y, z) is out of the robot arm's range.
	}
	return 0;
}


int main()
{
	double x1 = 200, y1 = 19.75, z1 = 0;  // Change your input points at here.
	double x2 = 100, y2 = 50, z2 = 0;
	double x3 = 150, y3 = 70, z3 = 0;
	double no_error = 1;
	if (canleachornot(x1, y1, z1))
	{
		cout << "the robot arm can not reach (" << x1 << ", " << y1 << ", " << z1 << ")" << endl;
		no_error = 0;
	}
	if (canleachornot(x2, y2, z2))
	{
		cout << "the robot arm can not reach (" << x2 << ", " << y2 << ", " << z2 << ")" << endl;
		no_error = 0;
	}
	if (canleachornot(x3, y3, z3))
	{
		cout << "the robot arm can not reach (" << x3 << ", " << y3 << ", " << z3 << ")" << endl;
		no_error = 0;
	}
	if (no_error)    // If every point is proper, draw a line between the points. 
	{
		draw_line(x1, y1, z1 + 50, x1, y1, z1);
		draw_line(x1, y1, z1, x2, y2, z2);
		draw_line(x2, y2, z2, x3, y3, z3);
		draw_line(x3, y3, z3, x1, y1, z1);
	}
	return 0;
}
