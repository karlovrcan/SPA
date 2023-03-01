#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Array {
	void* data;
	int prioritet;
}Array;

typedef struct {
	Array* niz;
}Red;


void add(Red* r, int n);
Array* fix_from_below(Red* r, int child);
void switchele(Red* r, int l, int d);
void delete_first(Red* r);
Array* fix_from_top(Red* r, int n);



void add(Red* r, int n) {
	printf("Unesite prioritet: ");
	scanf("%d", &r->niz[n].prioritet);
	fix_from_below(r, n);
}

Array* fix_from_below(Red* r, int child) {
	int parent = floor((child - 1) / 2);

	if (child == 0) {
		return r;
	}
	else if (r->niz[parent].prioritet < r->niz[child].prioritet) {
		switchele(r, parent, child);
		fix_from_below(r, parent);
	}
}

void switchele(Red* r, int parent, int child) {
	Array tmp;
	tmp.data = r->niz[parent].data;
	tmp.prioritet = r->niz[parent].prioritet;
	r->niz[parent].data = r->niz[child].data;
	r->niz[parent].prioritet = r->niz[child].prioritet;
	r->niz[child].data = tmp.data;
	r->niz[child].prioritet = tmp.prioritet;
}

void delete_first(Red* r) {
	int duzina = 10;
	r->niz[0].prioritet = r->niz[duzina - 1].prioritet;
	duzina -= 1;
	fix_from_top(r, 0);
}

Array* fix_from_top(Red* r, int n) {
	int l = 2 * n + 1;
	int d = 2 * n + 2;
	if (d >= 10 && l >= 10) {
		return r;
	}

	else if (l < 10 && d >= 10) {
		if (r->niz[l].prioritet >= r->niz[n].prioritet) {
			switchele(r, n, l);
			fix_from_top(r, l);
		}
	}

	if (r->niz[n].prioritet < r->niz[l].prioritet && r->niz[l].prioritet >= r->niz[d].prioritet) {
		switchele(r, n, l);
		fix_from_top(r, l);
	}
	else if (r->niz[n].prioritet < r->niz[d].prioritet && r->niz[d].prioritet >= r->niz[l].prioritet) {
		switchele(r, n, d);
		fix_from_top(r, d);
	}
}



int main() {
	Red* r = (Red*)malloc(sizeof(Red));
	r->niz = (Array*)malloc(1000 * sizeof(Array));

	for (int i = 0; i < 10; i++) {
		add(r, i);
	}

	printf("\tprije uklanjanja s vrha\n");
	for (int i = 0; i < 10; i++) {
		printf("Element: %d\n", r->niz[i].prioritet);
	};

	printf("\tposlje uklanjanja s vrha\n");
	delete_first(r);
	for (int i = 0; i < 10; i++) {
		printf("Element: %d\n", r->niz[i].prioritet);
	};

	delete_first(r);
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("Element: %d\n", r->niz[i].prioritet);
	}

	delete_first(r);
	printf("\n");

	for (int i = 0; i < 10; i++) {
		printf("Element: %d\n", r->niz[i].prioritet);
	};

	free(r->niz);
	free(r);

	return 0;
}