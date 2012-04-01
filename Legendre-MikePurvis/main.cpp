#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
 
#define N 1
double Pi;
double root[N];
double coefficient[N];
double coeffArray[N + 1][N + 1]; //{{0}};

void lege_coef()
{
	cout << "BUILDING COEFFICIENTS\n";
	int n, i;
	coeffArray[1][1] = 1;
	coeffArray[0][0] = 1;
	for (n = 2; n <= N; n++) {
		coeffArray[n][0] = -(n - 1) * coeffArray[n - 2][0] / n;
		for (i = 1; i <= n; i++){
			cout << "coeffArray[" << n << "][" << i << "] = ((2*" << n << " - 1) * coeffArray[" << (n-1) << "][" << (i-1) << " - " << (n-1) << "* coeffArray[" << (n-2) << "][" << i << "]) / " << n << endl;
			coeffArray[n][i] = ((2 * n - 1) * coeffArray[n - 1][i - 1] - (n - 1) * coeffArray[n - 2][i] ) / n;
			cout << "coeffArray[" << n << "][" << i << "] => " << coeffArray[n][i] << endl;
		}
	}
}
double lege_eval(int n, double x)
{
	int i;
	double s = coeffArray[n][n];
	for (i = n; i; i--){
		cout << "s(" << s << ") * x(" << x << ") + coeffArray[n][i-1](" << coeffArray[n][i - 1] << ")\n";
		s = s * x + coeffArray[n][i - 1];
	}
	return s;
}
 
double lege_diff(int n, double x)
{
	return n * (x * lege_eval(n, x) - lege_eval(n - 1, x)) / (x * x - 1);
}
 
void lege_roots()
{
	cout << "\nBUILDILNG ROOTS\n";
	int i;
	double x, x1;
	for (i = 1; i <= N; i++) {
		x = cos(Pi * (i - .25) / (N + .5));
		do {
			x1 = x;
			x -= lege_eval(N, x) / lege_diff(N, x);
		} while (x != x1);
		root[i - 1] = x;
 
		x1 = lege_diff(N, x);
		coefficient[i - 1] = 2 / ((1 - x * x) * x1 * x1);
	}
}
 
double lege_inte(double (*f)(double), double a, double b)
{
	double c1 = (b - a) / 2, c2 = (b + a) / 2, sum = 0;
	int i;
	for (i = 0; i < N; i++)
		sum += coefficient[i] * f(c1 * root[i] + c2);
	return c1 * sum;
}

 
int main()
{
	int i;
	Pi = atan2((double)1, (double)1) * 4;
	//Pi = 
 
	
	lege_coef();
	lege_roots();
 
	printf("Roots: ");
	for (i = 0; i < N; i++)
		printf(" %g", root[i]);
 
	printf("\nWeight:");
	for (i = 0; i < N; i++)
		printf(" %g", coefficient[i]);

	/*
	printf("\nintegrating Exp(x) over [-1, 1]:\n\t%10.8f,\n"
		"compred to actual\n\t%10.8f\n",
		lege_inte(exp, -1, 1), exp((double)1) - exp((double)-1));
		
	cout << "gahh";
	*/
	


	// Press any key to exit stuff
	printf("\n\nPress Enter to exit.");
	fflush(stdout);
	while ( getchar() != '\n' );
	
	return 0;
}