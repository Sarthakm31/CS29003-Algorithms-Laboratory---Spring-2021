#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct list{
    int num;
    int index;
    struct list *next;
}list;

int wait_time(list **cntr, int k)
{
    int i,waitime = 0;
    for(i = 0;i < k;i++)
    {
        list *f = cntr[i];
        int timespent = f->num;
        f = f->next;
        while(f != NULL)
        {
            waitime += timespent;
            timespent += f->num;
            f = f->next;
        }
    }
    return waitime;
}
void printc(list **cntr, int k)
{
    int i,waitime,closetime = -1;
    waitime = wait_time(cntr,k);
    for(i = 0;i < k;i++)
    {
        list *f = cntr[i];
        printf("\nCounter %d\t",i+1);
        int timespent = f->num;
        printf("%d(%d)\t",f->index,f->num);
        f = f->next;
        while(f != NULL)
        {
            timespent += f->num;
            printf("%d(%d)\t",f->index,f->num);
            f = f->next;
        }
        if(timespent > closetime)
            closetime = timespent;
    }
    printf("\nCafe Closes at time = %d\nTotal Waiting Time = %d",closetime,waitime);
}
list** schedule_orders_a(int t[], int n, int k, int *wtw)
{
    int i,*tSpent;
    tSpent = (int*)malloc(k * sizeof(int));
    list **cntr,**pos;
    cntr = (list**)malloc(k * sizeof(list*));
    pos = (list**)malloc(k * sizeof(list*));
    int ind = 0;
    for(;ind < k;ind++)
    {
        cntr[ind] = (list*)malloc(sizeof(list));
        pos[ind] = cntr[ind];
        pos[ind]->num = t[ind];
        pos[ind]->index = wtw[ind]+1;
        pos[ind]->next = NULL;
        tSpent[ind] = t[ind];
    }
    while(ind < n)
    {
        int j,i = 0;
        for(j=1;j<k;j++)
        {
            if(tSpent[j] < tSpent[i])
                i = j;
        }
        tSpent[i] += t[ind];
        pos[i]->next = (list*)malloc(sizeof(list));
        pos[i] = pos[i]->next;
        pos[i]->num = t[ind];
        pos[i]->index = wtw[ind]+1;
        pos[i]->next = NULL;
        ind++;
    }
    return cntr;
}

void merge(int p[], int l, int m, int r, int wtw[])
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L, *R;
    L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));
    int *Lw, *Rw;
    Lw = (int*)malloc(n1 * sizeof(int));
    Rw = (int*)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++)
    {
        L[i] = p[l + i];
        Lw[i] = wtw[l+i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = p[m + 1 + j];
        Rw[j] = wtw[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            p[k] = L[i];
            wtw[k] = Lw[i];
            i++;
        }
        else {
            p[k] = R[j];
            wtw[k] = Rw[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        p[k] = L[i];
        wtw[k] = Lw[i];
        i++;
        k++;
    }
    while (j < n2) {
        p[k] = R[j];
        wtw[k] = Rw[j];
        j++;
        k++;
    }
}

void sort(int p[], int l, int r, int *wtw)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        sort(p, l, m, wtw);
        sort(p, m + 1, r, wtw);
        merge(p, l, m, r, wtw);
    }
}
list** schedule_orders_b(int t[], int n, int k, int *wtw)
{
    sort(t,0,n-1,wtw);
    return schedule_orders_a(t,n,k,wtw);
}
list** schedule_orders_c(list **cntr,int k)
{
    list **revc = (list**)malloc(k * sizeof(list*));
    int i;
    for(i = 0;i < k;i++)
    {
        revc[i] = cntr[i];
        cntr[i] = cntr[i]->next;
        revc[i]->next = NULL;
        while(cntr[i] != NULL)
        {
            list *f;
            f = (list*)malloc(sizeof(list));
            f = cntr[i];
            cntr[i] = cntr[i]->next;
            f->next = revc[i];
            revc[i] = f;
        }
    }
    return revc;
}
int main()
{
    int i,k,n,*t,*wtw;
    printf("n = ");
    scanf("%d",&n);
    printf("k = ");
    scanf("%d",&k);
    t = (int*)malloc(n * sizeof(int));
    wtw = (int*)malloc(n * sizeof(int));
    printf("Enter order processing times:\n");
    for(i = 0;i < n;i++)
    {
        scanf("%d",&t[i]);
        wtw[i] = i;
    }
    list **cntr = schedule_orders_a(t,n,k,wtw);
    printf("\n\nPart (a)\n");
    printc(cntr,k);
    cntr = schedule_orders_b(t,n,k,wtw);
    printf("\n\nPart (b)\n");
    printc(cntr,k);
    cntr = schedule_orders_c(cntr,k);
    printf("\n\nPart (c)\n");
    printc(cntr,k);
}
