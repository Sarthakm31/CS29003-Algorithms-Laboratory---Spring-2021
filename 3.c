#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct pnt{
    float x;
    float y;
    struct pnt *next;
}pnt;

void assign(pnt *f,float a,float b,float c,float d)
{
    pnt *first = f;
    f->x = a;
    f->y = b;
    f->next = (struct pnt*)malloc(sizeof(pnt));
    f = f->next;
    f->x = a;
    f->y = b+d;
    f->next = (struct pnt*)malloc(sizeof(pnt));
    f = f->next;
    f->x = a+c;
    f->y = b+d;
    f->next = (struct pnt*)malloc(sizeof(pnt));
    f = f->next;
    f->x = a+c;
    f->y = b;
    f->next = first;
}

void merge(struct pnt **arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    pnt *L[n1], *R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i]->y <= R[j]->y) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void sort(pnt p[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        sort(p, l, m);
        sort(p, m + 1, r);
        merge(p, l, m, r);
    }
}
void printshape(pnt *f)
{
    pnt *first = f;
    printf("(%f,%f) ",f->x,f->y);
    f = f->next;
    while(f != first)
    {
        printf("(%f,%f)\t",f->x,f->y);
        f = f->next;
    }
    printf("(%f,%f)\n",f->x,f->y);
}
int intersect(pnt *a, pnt *b, pnt *c, pnt *d)
{
    if(a->x == b->x)                //a b vertical
    {
        if(c->x == d->x)            //c d vertical
        {
            return 0;
        }
        if(c->y == d->y)            //c d horizontal
        {
            if(b->y < a->y)
            {
                pnt *f = a;
                a = b;
                b = f;
            }
            if(c->x > d->x)
            {
                pnt *f = c;
                c = d;
                d = f;
            }
            if(c->x < a->x && a->x < d->x && a->y < c->y && c->y < b->y)
            {
                return 1;
            }
            else
                return 0;
        }
    }
    if(a->y == b->y)                //a b horizontal
    {
        if(c->x == d->x)            //c d vertical
        {
            if(a->x > b->x)
            {
                pnt *f = a;
                a = b;
                b = f;
            }
            if(c->y > d->y)
            {
                pnt *f = c;
                c = d;
                d = f;
            }
            if(a->x < d->x && d->x < b->x && c->y < a->y && a->y < d->y)
            {
                return 1;
            }
            else
                return 0;
        }
        if(c->y == d->y)            //c d horizontal
        {
            return 0;
        }
    }
    return 0;
}
void combine(pnt *d, pnt *u, float vl)
{
    pnt *prevd = d, *prevu = u;
    while(u->x < vl)
    {
        if(intersect(prevd,d,prevu,u))
        {
            pnt *i,*s;
            i = (pnt*)malloc(sizeof(pnt));
            if(prevd->x == d->x)
            {
                i->x = d->x;
                i->y = u->y;
            }
            else
            {
                i->x = u->x;
                i->y = d->y;
            }
            s = d;
            d = u;
            u = s;
            prevd->next = i;
            i->next = d;
            prevd = i;
            prevu = i;
            continue;
        }
        if(d->y < u->y)
        {
            prevd = d;
            d = d->next;
            continue;
        }
        if(d->y > u->y)
        {
            prevu = u;
            u = u->next;
            continue;
        }
    }
    while(d->x < vl)
    {
        d = d->next;
    }
    while(u->x > vl)
    {
        if(intersect(prevd,d,prevu,u))
        {
            pnt *i,*s;
            i = (pnt*)malloc(sizeof(pnt));
            if(prevd->x == d->x)
            {
                i->x = d->x;
                i->y = u->y;
            }
            else
            {
                i->x = u->x;
                i->y = d->y;
            }
            s = d;
            d = u;
            u = s;
            prevd->next = i;
            i->next = d;
            prevd = i;
            prevu = i;
        }
        if(d->y > u->y)
        {
            prevd = d;
            d = d->next;
            continue;
        }
        if(d->y < u->y)
        {
            prevu = u;
            u = u->next;
            continue;
        }
    }
}

void shape(pnt **p, int d, int u, float vl)
{
    if(d < u){
        int m = d + (u - 1) / 2;
        shape(p,d,m,vl);
        shape(p,m+1,u,vl);
        combine(p[d],p[m+1],vl);
    }
}
float VerticalLine(pnt **p, int n)
{
    float left = p[0]->x, right = p[0]->next->next->x;
    for(int i = 1;i < n;i++)
    {
        if(p[i]->x > left)
            left = p[i]->x;
        if(p[i]->next->next->x < right)
            right = p[i]->next->next->x;
    }
    return (left + right)/2;
}
int main()
{
    int n,i;
    scanf("%d",&n);
    pnt **p,*f;
    p = (pnt**)malloc(n * sizeof(pnt*));
    for(i = 0;i < n;i++)
    {
        p[i] = (pnt*)malloc(sizeof(pnt));
        float a,b,c,d;
        scanf("%f%f%f%f",&a,&b,&c,&d);
        assign(p[i],a,b,c,d);
    }
    sort(p,0,n-1);
    float vl = VerticalLine(p,n);
    int d = 0,u = -1,h = 0;
    for(i = 0;i < n;i++)
    {
        if(p[i]->y < p[h]->next->y)
        {
            u++;
            if(p[i]->next->y > p[h]->next->y)
                h = i;
        }
        if(p[i]->y > p[h]->next->y)
        {
            shape(p,d,u,vl);                //fun d u
            printshape(p[d]);
            d = i;
            u = i;
            h = i;
        }
    }
    shape(p,d,u,vl);
    printshape(p[d]);
}
