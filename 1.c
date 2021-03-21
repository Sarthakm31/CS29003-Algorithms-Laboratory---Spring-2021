//19EC30039
//Sarthak Goyal
//Assignment 1
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
double mtd1(int n)                      //method 1
{
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    double curr = 1,pre = 0,nxt;
    for(int i = 1;i < n;i++)
    {
        nxt = 2*curr + pre;
        pre = curr;
        curr = nxt;
    }
    return curr;
}
double mtd2(int n)                      //method 2
{
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return 2*mtd2(n-1) + mtd2(n-2);
}
double power(double x, int y)           //power function for method 3
{
    if (y == 0)
        return 1;
    else if (y % 2 == 0)
    {
        double b = power(x, y / 2);
        return b * b;
    }
    else
    {
        double b = power(x, y / 2);
        return x * b * b;
    }
}
double mtd3(int n)                      //method 3
{
    double s = sqrt(2);
    double a = power(1+s, n);
    double b = power(1-s, n);
    double c = (a - b) / (2*s);
    return c;
}
void multi(double A[],double B[])       //helper method for method 4
{
    double a = A[0]*B[0] + A[1]*B[2];
    double b = A[0]*B[1] + A[1]*B[3];
    double c = A[2]*B[0] + A[3]*B[2];
    double d = A[2]*B[1] + A[3]*B[3];
    B[0] = a;
    B[1] = b;
    B[2] = c;
    B[3] = d;
}
void mtd4(int n,double A[],double B[]) //method 4
{
    if (n == 1)
        multi(A,B);
    else if (n % 2 == 0)
    {
        mtd4(n/2, A, B);
        multi(B,B);
    }
    else
    {
        mtd4(n/2, A, B);
        multi(B,B);
        multi(A,B);
    }
}

int main() {

	int n;
	printf("Write n:");
	scanf("%d",&n);

	//code for method 1
	clock_t begin = clock();
	double ans1 = mtd1(n);
	clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("I_%d (computed using iterative method) %f\n",n,ans1);
    printf("Time taken in iterative method = %f\n",time_spent);

    //code for method 2
    begin = clock();
	double ans2 = mtd2(n);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("I_%d (computed using recursive method) %f\n",n,ans2);
    printf("Time taken in recursive method = %f\n",time_spent);

    //code for method 3
	begin = clock();
	double ans3 = mtd3(n);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("I_%d (computed using formula) %f\n",n,ans3);
    printf("Time taken in formula = %f\n",time_spent);

    //code for method 4
    begin = clock();
    double A[4] = {2,1,1,0};
    double B[4] = {1,0,0,1};
	if(n != 0) mtd4(n,A,B);
	end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("I_%d (computed using matrix multiplication) %f\n",n,B[1]);
    printf("Time taken in matrix = %f\n",time_spent);

	return 0;
}
