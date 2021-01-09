#include "pch.h"
#include <iostream>
#include <math.h>
using namespace std;


double(*Matrix_mul(double(*x)[4], double(*y)[4]))[4]
{	
	static double mul[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			mul[i][k] = 0;
			for (int n = 0; n < 4; n++)
			{
				mul[i][k] += x[i][n] * y[n][k];
			}
		}
	}
	return mul;
}


void making_arr(double(*x)[4], double(*y)[4])//x = y
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			x[i][k] = y[i][k];
		}
	}
}


void DH_parameter(double theta, double d, double a, double alpha)//angle : radian
{
	double theta_M[4][4] = {{cos(theta),-sin(theta),0,0},{sin(theta),cos(theta),0,0},{0,0,1,0},{0,0,0,1}};
	double     d_M[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,d},{0,0,0,1}};
	double     a_M[4][4] = {{1,0,0,a},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	double alpha_M[4][4] = {{1,0,0,0},{0,cos(alpha),-sin(alpha),0},{0,sin(alpha),cos(alpha),0},{0,0,0,1}};
	double theta_d[4][4] = { 0 }, theta_d_a[4][4] = { 0 }, theta_d_a_alpha[4][4] = { 0 };
	making_arr(theta_d, Matrix_mul(theta_M,d_M));
	making_arr(theta_d_a, Matrix_mul(theta_d, a_M));
	making_arr(theta_d_a_alpha, Matrix_mul(theta_d_a, alpha_M));
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			//making exact same output with MATLAB
			if (theta_d_a_alpha[i][k] > 0)
				printf(" ");
	    	if (theta_d_a_alpha[i][k] == 0)
				printf("%7d ", 0);
			else
				printf("%.4f ", theta_d_a_alpha[i][k]);
		}
		cout << endl;
	}
	cout << endl;
}


int main()
{
	double theta, d, a, alpha;
	cin >> theta >> d >> a >> alpha;
	DH_parameter(theta, d, a, alpha);
	return 0;
}
