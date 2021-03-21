#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int part_a(char s[], int l, int r)                  //function for part 1
{
    int i,m = (r + l + 1) / 2;
    while(m <= r)
    {
        if(s[l] != s[m])                            //if both halves differ at any point return 0
            return 0;
        l++;
        m++;
    }
    return 1;
}

int part_b(char s[], int l, int r, int n, int **dp) //function for part 2
{
    if(dp[l][r] != -1)                              //checking if already computed by dp
        return dp[l][r];

    if(n - r == 1)                                  //base condition
    {
        dp[l][r] = part_a(s,l,r);
        return dp[l][r];
    }

    if(part_a(s,l,r) == 0)                          //recursive call
    {
        dp[l][r] = part_b(s,l,r+2,n,dp);
        return dp[l][r];
    }
    else
    {
        dp[l][r] = part_b(s,l,r+2,n,dp) || part_b(s,r+1,r+2,n,dp);
        return dp[l][r];
    }
}

int main(void)
{
    char s[5000];
    scanf("%s",s);                                  //scanning the input

    int n = strlen(s);                              //n is the length of string
	if(n%2 == 1)                                    //if length is odd then return NO
    {
        printf("NO");
        return 0;
    }

    int **dp;                                       //matrix dp for dynamic programming
    dp = (int**)malloc(n * sizeof(int*));           //of size (length of string)*(length of string)
    for(int i = 0;i < n;i++)
    {
        dp[i] = (int*)malloc(n * sizeof(int));
        for(int j = 0;j < n;j++)
            dp[i][j] = -1;                          //initialize all values in dp to be -1
    }

    if(part_b(s,0,1,n,dp))                          //calling function for part b
    {
        printf("YES");                              //if part b returns 1 print YES
    }
    else
    {
        printf("NO");                               //if part b returns 0 print NO
    }
	return 0;
}
