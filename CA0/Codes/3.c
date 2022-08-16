#include <stdio.h>

int main() {
	float a, b, c;
	int n, i, x, y, z, u;
	x = y = z = u = 0;
	printf("Enter n:\n");
	x = scanf_s("%d", &n);                                  //getting input n and checking if it is valid or not
	if (n <= 0) {
		printf("wrong input");
		return (0);
	}
	printf("Enter a:\n");
	y = scanf_s("%f", &a);                                  //getting input a
	if (y != 1) {                                           //checking if input is valid. if not, print "inputs are not accepted" and stop the program
		printf(" input is not accepted\n");
		return (0);
	}
	printf("Enter b:\n");
	z = scanf_s("%f", &b);                                  //getting input b
	if (z != 1) {
		printf(" input is not accepted\n");
		return (0);
	}
	printf("Enter c:\n");
	u = scanf_s("%f", &c);                                  //getting input c
	if (u != 1) {
		printf(" input is not accepted\n");
		return (0);
	}
	printf("the series is:\n");
	if (n == 1) {
		printf("%f\n", a);                                   //if you want just the first 4 numbers, print first number (a) and then stop the program
		return (0);
	}
	if (n == 2) {
		printf("%f\n", a);                                   //if you want just the first 5 numbers, print 2 first numbers (a,b) and then stop the progra,
		printf("%f\n", b);
		return (0);
	}
	printf("%f\n", a);                                       //print 3 first numbers (a,,b,c)
	printf("%f\n", b);
	printf("%f\n", c);

	for (i = 0; i < n - 3; i = i + 3) {                     //a loop to build the next three numbers
		a = a + b + c;                                      //now we are building the next numbers in threebonacci and we save them in integers
		b = a + b + c;
		c = a + b + c;
		if (n - 3 - i >= 3) {                              //if we need the next three numbers, print a,b and c
			printf("%f\n", a);
			printf("%f\n", b);
			printf("%f\n", c);
		}
		if (n - 3 - i == 2) {                              //if we need the next two numbers, print a and b
			printf("%f\n", a);
			printf("%f\n", b);
		}
		if (n - 3 - i == 1) {                              //if we need just the next number, we print a
			printf("%f\n", a);
		}
	}
	return 0;
}