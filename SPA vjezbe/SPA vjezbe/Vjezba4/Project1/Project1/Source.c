#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#define BIGRAND (rand()*rand())

int cmpfunc(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}



void shuffle(int* niz, int n) {
	for (int i = 0; i < n - 1; i++) {
		int j = i + BIGRAND % (n - i);
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int* generate(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = 1 + BIGRAND % 3;
	for (int i = 1; i < n; i++)
		niz[i] = niz[i - 1] + BIGRAND % 3 + 1;
	shuffle(niz, n);
	return niz;
}

int* presjek(int* niz1, int* niz2, int n1, int n2)
{
	int brojac = 0;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (niz1[i] == niz2[j])
				brojac++;
		}
	}
	int* presjek1 = (int*)malloc(sizeof(int) * brojac);

	brojac = 0;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (niz1[i] == niz2[j])
			{
				presjek1[brojac] = niz1[i];
				brojac++;
			}
		}
	}
	return presjek1;
}


int* presjek_jedan_sortiran(int* niz1, int* niz2, int n)
{
	qsort(niz2, n, sizeof(int), cmpfunc);

	int brojac = 0;
	int* bin2;
	for (int i = 0; i < n; i++) {
		bin2 = (int*)bsearch(&niz1[i], niz2, n, sizeof(int), cmpfunc);
		if (bin2 != NULL) {
			brojac++;
		}
	}
	int* presjek = (int*)malloc(sizeof(int) * brojac);
	brojac = 0;
	int* bin;
	for (int i = 0; i < n; i++) {
		bin = (int*)bsearch(&niz1[i], niz2, n, sizeof(int), cmpfunc);
		if (bin != NULL) {
			presjek[brojac] = *bin;
			brojac++;
		}
	}
	return presjek;
}

int* presjek_oba_sortirana(int* niz1, int* niz2, int n1, int n2)
{
	qsort(niz1, n1, sizeof(int), cmpfunc);
	qsort(niz2, n2, sizeof(int), cmpfunc);

	int brojac = 0;
	int* bin1;
	for (int i = 0; i < n1; i++) {
		bin1 = (int*)bsearch(&niz1[i], niz2, n2, sizeof(int), cmpfunc);
		if (bin1 != NULL) {
			brojac++;
		}
	}

	int* presjek = (int*)malloc(sizeof(int) * brojac);

	int i = 0;
	int j = 0;
	int k = 0;
	while (i < n1 && j < n2) {
		if (niz1[i] < niz2[j])
		{
			i++;
		}
		else if (niz2[j] < niz1[i])
		{
			j++;
		}
		else if (niz1[i] == niz2[j])
		{
			presjek[k] = niz1[i];
			k++;
			i++;
			j++;
		}
	}
	return presjek;
}

int* presjek_po_indeksima(int* niz1, int* niz2,int n1,int n2)
{

}

int main()
{
	FILE* f1 = fopen("nijedan.txt", "w");
	int n1 = 10000;
	int n2 = 300000;
	for (int i = 0; i < 9; i++)
	{
		printf("Trenutacna velicina: \nniz1:%d \nniz2:%d\n", n1, n2);
		int* niz1 = generate(n1);
		shuffle(niz1, n1);
		int* niz2 = generate(n2);
		shuffle(niz2, n2);
		int start = clock();
		int* presjek_test = presjek(niz1, niz2, n1, n2);
		int stop = clock();
		fprintf(f1, "%d,%lf\n", n1, (double)(stop - start) / CLOCKS_PER_SEC);
		printf("Vrijeme dva nesortirana niza: %2lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
		n1 += 30000;
		free(niz1);
		free(niz2);
	}
	fclose(f1);
	printf("\nNova funkcija: Jedan sortiran\n\n");

	FILE* f2 = fopen("jedan.txt", "w");
	n1 = 10000;
	n2 = 300000;
	for (int i = 0; i < 9; i++)
	{
		printf("Trenutacna velicina: \nniz1:%d \nniz2:%d\n", n1, n2);
		int* niz1 = generate(n1);
		shuffle(niz1, n1);
		int* niz2 = generate(n2);
		shuffle(niz2, n2);
		int start = clock();
		int* presjek_test1 = presjek_jedan_sortiran(niz1, niz2, n1);
		int stop = clock();
		fprintf(f2, "%d,%f\n", n1, (double)(stop - start) / CLOCKS_PER_SEC);
		printf("Vrijeme jednog sortiranog niza: %2lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
		n1 += 30000;
		free(niz1);
		free(niz2);
	}
	fclose(f2);
	printf("\nNova funkcija: Oba sortirana\n\n");
	FILE* f3 = fopen("oba.txt", "w");
	n1 = 10000;
	n2 = 300000;
	for (int i = 0; i < 9; i++)
	{
		printf("Trenutacna velicina: \nniz1:%d \nniz2:%d\n", n1, n2);
		int* niz1 = generate(n1);
		shuffle(niz1, n1);
		int* niz2 = generate(n2);
		shuffle(niz2, n2);
		int start = clock();
		int* presjek_test2 = presjek_oba_sortirana(niz1, niz2, n1, n2);
		int stop = clock();
		fprintf(f3, "%d,%lf\n", n1, (double)(stop - start) / CLOCKS_PER_SEC);
		printf("Vrijeme oba sortirana niza: %2lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
		n1 += 30000;
		free(niz1);
		free(niz2);
	}
	fclose(f3);
	printf("\nNova funkcija: Indexi\n\n");
	FILE* f4 = fopen("indexi.txt", "w");
	n1 = 10000;
	n2 = 300000;
	for (int i = 0; i < 9; i++)
	{
		printf("Trenutacna velicina: \nniz1:%d \nniz2:%d\n", n1, n2);
		int* niz1 = generate(n1);
		shuffle(niz1, n1);
		int* niz2 = generate(n2);
		shuffle(niz2, n2);
		int start = clock();
		int* presjek_po_ind = presjek_po_indeksima(niz1, niz2, n1, n2);
		int stop = clock();
		fprintf(f4, "%d,%lf\n", n1, (double)(stop - start) / CLOCKS_PER_SEC);
		printf("Vrijeme nizova: %2lf\n", (double)(stop - start) / CLOCKS_PER_SEC);
		n1 += 30000;
		free(niz1);
		free(niz2);
	}

	return 0;
}


