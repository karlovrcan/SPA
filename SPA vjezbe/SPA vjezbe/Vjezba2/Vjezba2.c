#include <stdio.h>
#include <stdlib.h>

/*int* podniz(int *niz, int start, int stop) – vraca novi niz
koji je kopija dijela niza od indeksa start do indeksa stop.*/

//int* podniz(int* niz, int start, int stop)
//{
//    int* niz2;
//    int a = stop - start;
//    niz2 = (int*)malloc(sizeof(int) * a);
//    for (int i = 0; i < a; i++)
//    {
//        niz2[i] = niz[start];
//        start += 1;
//    }
//    return niz2;
//}
//
//int main()
//{
//    int niz[9] = { 1,2,3,4,5,6,7,8,9 };
//    int start = 3;
//    int stop = 6;
//    int* c = podniz(&niz, start, stop);
//    for (int i = 0; i < (stop - start); i++)
//    {
//        printf("%d\n", c[i]);
//    }
//    free(c);
//    return 0;
//}


/*int* filtriraj(int *niz, int n, int th, int *nth) – vraæa novi niz koji sadrži 
brojeve iz originalnog niza koji su manji od th. Originalni niz ima dužinu n. 
Dužinu novog niza sa brojevima koji su prošli filter treba spremiti u nth. */

/*
int* filtriraj(int* niz, int n, int th, int* nth)
{
    int i = 0;
    int j = 0;
    while (n > 0)
    {
        if (niz[i] < th)
        {
            nth[j] = niz[i];
            j++;
        }
        i++;
        n--;
    }
    int* nth2 = (int*)realloc(nth, sizeof(int) * j);
    nth = nth2;
    return  nth;
}

int main()
{
    int niz[] = { 2,34,12,100,5,8,15,1,7 };
    int th = 20;
    int n = sizeof(niz) / sizeof(niz[0]);
    int brojac = 0;
    for (int i = 0; i < brojac; i++)
    {
        if (niz[i] < th)
            brojac++;
    }
    int* nth = (int*)malloc(sizeof(int) * n);
    int* c = filtriraj(&niz, n, th, nth);
    nth = c;
    for (int i = 0; i < brojac; i++)
    {
        printf("%d\n", &nth[i]);
    }
    free(c);
    free(nth);
    return 0;
}*/

/*int** podijeli(int *niz, int n) - dijeli niz dužine n na dva jednaka dijela
i stvara kopije prvog i drugog dijela. Funkcija vraæa dva pokazivaèa koji 
pokazuju na prvi i na drugi dio.*/

/*
int** podijeli(int* niz, int n)
{
    int* prviNiz;
    int* drugiNiz;
    prviNiz = (int*)malloc(sizeof(int) * (n / 2));
    drugiNiz = (int*)malloc(sizeof(int) * (n / 2));
    for (int i = 0; i < n / 2; i++)
    {
        prviNiz[i] = niz[i];
    }
    int j = 0;
    for (int i = n / 2; i < n; i++)
    {
        drugiNiz[j] = niz[i];
        j++;
    }
    int** p = ((int**)malloc(sizeof(int*) * 2));
    p[0] = prviNiz;
    p[1] = drugiNiz;
    return p;
}

int main()
{
    int niz[] = { 1,2,3,4,5,6,7,8,9,10 };
    int n = sizeof(niz) / sizeof(niz[0]);
    int** funkcija = podijeli(&niz, n);
    for (int i = 0; i < n / 2; i++)
    {
        printf("%d %d\n", funkcija[0][i], funkcija[1][i]);
    }
    return 0;
}*/

/*Cetvrti zadatak*/

typedef struct _tocka {
    float x;
    float y;
}tocka;

typedef struct _poligon {
    tocka* niz;
    int n;
}poligon;

poligon* novi_poligon(float* niz_x, float* niz_y, int n)
{
    poligon* poligon1;
    poligon1 = (poligon*)malloc(sizeof(poligon));
    poligon1->niz = (tocka*)malloc(sizeof(tocka) * n);
    poligon1->n = n;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        poligon1->niz[i].x = niz_x[i];
        poligon1->niz[i].y = niz_y[i];
    }
    return poligon1;
}

tocka** pozitivni(poligon* p, int* np)
{

    int i;
    *np = 0;
    int j = 0;
    for (int i = 0; i < p->n; i++)
    {
        if (p->niz[i].x > 0 && p->niz[i].y > 0)
        {
            j++;
        }
    }
    *np = j;
    tocka** niz1 = (tocka**)malloc(sizeof(tocka*) * (*np));
    int k = 0;
    for (i = 0; i < p->n; i++)
    {
        if (p->niz[i].x > 0 && p->niz[i].y > 0)
        {
            niz1[k] = p->niz + i;
            k++;
        }
    }
    return niz1;
}
int main()
{
    float niz1[] = { 1,2,-3,4,5 };
    float niz2[] = { 1,2,3,4,-5 };
    int n = 5;
    poligon* poligon1 = novi_poligon(niz1, niz2, n);

    for (int i = 0; i < n; i++)
    {
        printf("%f %f\n", poligon1->niz[i].x, poligon1->niz[i].y);
    }
    printf("-------------------\n");
    tocka** poz = pozitivni(poligon1, &n);
    for (int i = 0; i < n; i++)
    {
        printf("%f %f\n", poz[i]->x, poz[i]->y);
    }
    return 0;
}

