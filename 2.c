#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//function to print the winning possibility
void print(int *P, int p, int *C, int c, int tot)
{
    int csum = 0;                                                   //sum of votes of coalition parties
    for(int i = 0;i < c;i++)
    {
        csum += P[C[i] - 1];
    }
    float fract = (float)csum / tot;
    if(fract > 0.5)                                                 //condition to check percentage is more than 50%
    {
        for(int i = 0;i < p;i++)
            printf("%d: %d   ",i+1,P[i]);
        printf("\tTotal votes for the coalition: %d\n",csum);
    }
}

//A recursive vote distribution function
void vote_dist(int *P, int p, int v,int *C, int c, int ind, int tot)
{
    if(v == 0)                                                      //base condition which is true when no. of votes remaining is 0
        print(P,p,C,c,tot);
    else
    {
        for(int i = ind;i < p;i++)
        {
            P[i]++;
            vote_dist(P,p,v-1,C,c,i,tot);                           //recursive call to the function where no. of votes remaining is less than 1
            P[i]--;
        }
    }
}

int main(void)
{
    int i,p,v,c=0;
    printf("#Voters: ");
    scanf("%d",&v);
    printf("#Parties: ");
    scanf("%d",&p);
    int *P,*C;
    P = (int*)malloc(sizeof(int) * p);                              //dynamically allocating memory
    C = (int*)malloc(sizeof(int) * p);
    for(i = 0;i < p;i++)
        P[i] = 0;                                                   //initializing all elements of array to 0
    printf("Coalition: \n");
    for(i = 0;i < p+1;i++)
    {
        scanf("%d",&C[i]);
        if(C[i] > p || C[i] < 1)                                    //if value is not between 1 & p break;
            break;
    }
    c = i;
    vote_dist(P,p,v,C,c,0,v);

	return 0;
}
