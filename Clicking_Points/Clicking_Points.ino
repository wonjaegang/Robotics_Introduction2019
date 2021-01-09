#include <Servo.h>
#include "math.h"
#define MAX(a,b) (((a)>(b))?(a):(b))
#define servo1pin 9  // Servo pins should be PWM pins.
#define servo2pin 5
#define servo3pin 6
Servo servo1;
Servo servo2;
Servo servo3;

double a = 150, b = 94.25, d_center = 19.75;

void draw_pixel(double x, double y, double z)  // Function that calculate backward Kinematics. Refer to PDF file to get more information.
{
  double B, C, D, E, F;
  double c, r, k;
  r = sqrt(x * x + y * y - d_center*d_center);
  k = z - (87 + 48);
  c = sqrt(r * r + k * k);
  B = acos((a * a + c * c - b * b) / (2 * a * c));
  C = acos((a * a + b * b - c * c) / (2 * a * b));
  D = atan2(k , r);
  E = PI - C - B + D;  
  F = atan2(r,d_center) - atan2(x,y);
  servo1.write(int(F  * (180 / PI) + 0.5));   // Change angle(radian) to Servo motor PWM(voltage) input. It includes rounding.
  servo2.write(int((PI/2 - E) * (180 / PI) + 0.5));
  servo3.write(int(C * (180 / PI) + 0.5)-10);
}


void draw_line(double x0,double y0,double z0,double x1,double y1, double z1,int t)
{
  char steep;
  double temp;
  if (MAX(MAX(fabs(x1 - x0), fabs(y1 - y0)), fabs(z1 - z0)) == fabs(x1 - x0))  // We need the reference axis which increasing uniformly, and we will regard it as X axis.
  {
    steep = 'x';
  }
  if (MAX(MAX(fabs(x1 - x0), fabs(y1 - y0)), fabs(z1 - z0)) == fabs(y1 - y0))
  {
    steep = 'y';
    temp = x0; x0 = y0; y0 = temp;    
    temp = x1; x1 = y1; y1 = temp;
  }
  if (MAX(MAX(fabs(x1 - x0), fabs(y1 - y0)), fabs(z1 - z0)) == fabs(z1 - z0))
  {
    steep = 'z';
    temp = x0; x0 = z0; z0 = temp;    
    temp = x1; x1 = z1; z1 = temp;
  } 
  double deltax = fabs(x1 - x0), deltay = fabs(y1 - y0), deltaz = fabs(z1 - z0);
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
      draw_pixel(x, y, z); break;
    case 'y':
      draw_pixel(y, x, z); break;
    case 'z':
      draw_pixel(z, y, x); break;
    default:
      break;
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
    delay(t);
  }
}


void setup() 
{
  servo1.attach(servo1pin,500,2500);
  servo2.attach(servo2pin,500,2500);
  servo3.attach(servo3pin,500,2500);
  //initialize
  //servo1.write(180);
  //servo2.write(0);
  //servo3.write(180);
  double x1 = -66, y1 = 14;  // Change your input points at here.
  double x2 = 50, y2 = 14;
  double x3 = -36 + 1.5, y3 = 124-20;
  double z1 = 0, z2 = 0, z3= 0;
  

  if(y1 <41)
    y1 = y1 + 11/19* (y1 - 22) - 12;
  else if(y1 < 100) 
    y1 = y1 - 10/82* (y1 - 41) - 5;
  else
    {
      y1 = y1 - 10/82* (y1 - 41) +5;
      z1 -= 1;
    }
  if(y2 <41)
    y2 = y2 + 11/19* (y2 - 22) - 12;
  else if(y2 < 100) 
    y2 = y2 - 10/82* (y2 - 41) - 5;
  else
  {
    y2 = y2 - 10/82* (y2 - 41) + 5;
    z2 -= 1;
  }
  if(y3 <41)
    y3 = y3 + 11/19* (y3 - 22) - 12;
  else if(y3 < 100) 
    y3 = y3 - 10/82* (y3 - 41) - 5;
  else
  {
    y3 = y3 - 10/82* (y3 - 41) + 5;
    z3 -= 3;
  }
    
    
  
  //click
  draw_pixel(x1 - (6 / 150) * (75- x1), 70+y1, 9/150 * (35 - x1) + 30);
  delay(1000);
  draw_line(x1 - (6 / 150) * (75- x1) + 3, 70+y1, 9/150 * (45 - x1) + 30 + z1, x1 - (6 / 150) * (75- x1) + 3, 70+y1, 9/150 * (45 - x1)      + z1, 10);
  draw_line(x1 - (6 / 150) * (75- x1) + 3, 70+y1, 9/150 * (45 - x1)      + z1, x1 - (6 / 150) * (75- x1) + 3, 70+y1, 9/150 * (45 - x1) + 30 + z1, 10);
  draw_line(x1 - (6 / 150) * (75- x1) + 3, 70+y1, 9/150 * (45 - x1) + 30 + z2, x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2) + 30 + z2, 10);
  
  draw_line(x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2) + 30 + z2, x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2)      + z2, 10);
  draw_line(x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2)      + z2, x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2) + 30 + z2, 10);
  draw_line(x2 - (6 / 150) * (75- x2) + 3, 70+y2, 9/150 * (45 - x2) + 30 + z2, x3 - (6 / 150) * (75- x3) + 3, 70+y3, 9/150 * (45 - x3) + 50 + z3, 20);

  
  draw_line(x3 - (6 / 150) * (75- x3) + 3, 70+y3, 9/150 * (45 - x3) + 50 + z3, x3 - (6 / 150) * (75- x3) + 3, 70+y3, 9/150 * (45 - x3)      + z3, 20);
  draw_line(x3 - (6 / 150) * (75- x3) + 3, 70+y3, 9/150 * (45 - x3)      + z3, x3 - (6 / 150) * (75- x3) + 3, 70+y3, 9/150 * (45 - x3) + 30 + z3, 10);
  
}


void loop()
{}
