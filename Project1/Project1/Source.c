
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
	char* word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word* next;
} Word;

typedef Word* Dictionary;

// kreaira novi prazni rjecnik
Dictionary create();

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str);

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict);

// brise cijeli rjecnik
void destroy(Dictionary dict);

//moje funkcije
int search(Dictionary dict, char* str);

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word* w));

int filter(Word* w);


Dictionary create()
{
	Dictionary dictionary = (Dictionary)malloc(sizeof(Word));
	dictionary->word = NULL;
	dictionary->count = 0;
	dictionary->next = NULL;
	return dictionary;
}

// void add(Dictionary dict, char *str)
// {
//     if (search(dict, str) == 0)
//     {
//         Dictionary new = create();
//         Dictionary temp = create();

//         strcpy(temp->word, str);
//         if(dict == NULL){
//             dict = temp;
//         }
//         else{
//             new  = dict;
//             while(new->next != NULL){
//                 new = new->next;
//             }
//             new->next = temp;
//         }
//     }
// }

void add(Dictionary dict, char* str) {
	Dictionary novi = (Dictionary)malloc(sizeof(Word));
	Dictionary tmp = dict;
	novi->word = _strdup(str);
	novi->count = 1;
	novi->next = NULL;
	while (1)
	{
		if (tmp->next == NULL)
		{
			tmp->next = novi;
			return;
		}
		else if (strcmp(tmp->next->word, str) == 0)
		{
			tmp->next->count++;
			free(novi->word);
			free(novi);
			return;
		}
		else if (strcmp(tmp->next->word, str) > 0)
		{
			novi->next = tmp->next;
			tmp->next = novi;
			return;
		}
		else
		{
			tmp = tmp->next;
		}
	}
}

// void print(Dictionary dict)
// {
//     FILE *f;
//     f=fopen("newDictionary.txt", "w");
//     Dictionary current = dict;
//     while (current != NULL)
//     {
//         if (strcmp(current->word, "") != 0)
//         {
//             fprintf(f,"%s, count = %d\n", current->word, current->count);
//         }
//         current = current->next;
//     }
//     fclose(f);
// }

void print(Dictionary dict) {
	Dictionary tmp = dict;
	while (tmp != NULL) {
		printf("Word: %s i Count %d\n", tmp->word, tmp->count);
		tmp = tmp->next;
	}
}

void destroy(Dictionary dict)
{
	Dictionary current = dict;
	Dictionary next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	dict = NULL;
}

int search(Dictionary dict, char* str)
{
	Dictionary current = dict;
	while (current != NULL)
	{
		if (strcmp(current->word, str) == 0)
		{
			//printf("found %s\n", str);
			current->count++;
			return 1;
		}
		else
		{
			current = current->next;
			//printf("word didn't match\n");
		}
	}
	return 0;

}

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word* w))
{
	Dictionary tmp = indict;
	Dictionary nxt = indict->next;
	while (nxt->next != NULL) {
		if (filter(nxt) == 0) {
			Dictionary novi = nxt;
			nxt = nxt->next;
			free(novi->word);
			free(novi);

			tmp->next = nxt;
		}
		else {
			tmp = nxt;
			nxt = nxt->next;
		}
	}
	return indict;
}

int filter(Word* w) {
	int len = strlen(w->word);
	if (len > 3 && (w->count >= 5 && w->count <= 10)) {
		return 1;
	}
	return 0;
}


int readWord(FILE* fd, char* buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

//char* najduza(Dictionary dict)
//{
//	dict = dict->next;
//	char* ric = dict->word;
//	while (dict->next != NULL) {
//		if (strlen(dict->word) > strlen(ric)) {
//			ric = dict->word;
//		}
//		dict = dict->next;
//	}
//	return ric;
//}


//int broj_rici(Dictionary dict) {
//	int brojac = 0;
//	while (dict != NULL)
//	{
//		brojac += dict->count;
//		dict = dict->next;
//	}
//	return brojac;
//}

//void dodaj_na_pocetak(Dictionary dict, char* str)
//{
//	Dictionary novi = (Dictionary*)malloc(sizeof(Word));
//	novi->word = str;
//	novi->count = 1;
//	novi->next = dict->next;
//	dict->next = novi;
//}
//
//void dodaj_na_kraj(Dictionary dict, char* str)
//{
//	Dictionary novi = (Dictionary*)malloc(sizeof(Word));
//	novi->count = 1;
//	novi->word = str;
//	novi->next = NULL;
//	while (dict->next != NULL) {
//		dict = dict->next;
//	}
//	dict->next = novi;
//}
//
//void prije_elementa(Dictionary dict, char* str1, char* str2)
//{
//	Dictionary novi = (Dictionary*)malloc(sizeof(Word));
//	novi->count = 1;
//	novi->word = str1;
//	novi->next = NULL;
//	while (dict->next != NULL)
//	{
//		if (strcmp(dict->next->word,str2) == 0)
//		{
//			novi->next = dict->next;
//			dict->next = novi;
//			break;
//		}
//		dict = dict->next;
//	}
//}
//
//void dodaj_na_index(Dictionary dict, char* str, int br)
//{
//	int i = 0;
//	Dictionary novi = (Dictionary*)malloc(sizeof(Word));
//	novi->count = 1;
//	novi->word = str;
//	novi->next = NULL;
//	while (i != br)
//	{
//		dict = dict->next;
//		i++;
//	}
//	Dictionary temp = dict;
//	novi->next = dict->next;
//	dict->next = novi;
//}
//
//void prvi_zadnji(Dictionary dict) {
//	Dictionary dummy = dict;
//	Dictionary prvi = dict->next;
//	Dictionary drugi = dict->next->next;
//	while (dict->next->next != NULL)
//	{
//		dict = dict->next;
//	}
//	Dictionary predzadnji = dict;
//	Dictionary zadnji = dict->next;
//	dummy->next = zadnji;
//	zadnji->next = drugi;
//	predzadnji->next = prvi;
//	prvi->next = NULL;
//}
//
//void brisanje_prve(Dictionary dict) {
//	Dictionary prvi = dict->next;
//	dict->next = dict->next->next;
//	free(prvi);
//}
//
//void brisanje_zadnje(Dictionary dict) {
//	while (dict->next->next != NULL)
//		dict = dict->next;
//	Dictionary zadnji = dict->next;
//	dict->next = NULL;
//	free(zadnji);
//}

//void drugo_trece(Dictionary dict, char* str1, char* str2)
//{
//	Dictionary druga = (Dictionary*)malloc(sizeof(Word));
//	Dictionary treca = (Dictionary*)malloc(sizeof(Word));
//	druga->count = 1;
//	druga->word = str1;
//	treca->count = 1;
//	treca->word = str2;
//	Dictionary temp = dict->next;
//	treca->next = temp->next;
//	druga->next = treca;
//	temp->next = druga;
//}

//void uklanjanje_dva_slova(Dictionary dict) {
//	while (dict->next != NULL)
//	{
//		if (strlen(dict->next->word) == 1)
//		{
//			Dictionary temp = dict->next;
//			dict->next = dict->next->next;
//			free(temp);
//		}
//		dict = dict->next;
//	}
//}

//void dodavanje_isprid_tri_slova(Dictionary dict, char* str)
//{
//	while (dict->next != NULL) {
//		if (strlen(dict->next->word) == 3)
//		{
//			Dictionary nova = (Dictionary*)malloc(sizeof(Word));
//			nova->count = 1;
//			nova->word = str;
//			nova->next = dict->next;
//			dict->next = nova;
//			dict = dict->next;
//		}
//		dict = dict->next;
//	}
//}

//void drugi_predzadnji(Dictionary dict) {
//	Dictionary prvi = dict->next;
//	Dictionary drugi = prvi->next;
//	Dictionary treci = drugi->next;
//	while (dict->next->next->next != NULL)
//		dict = dict->next;
//	Dictionary ppzadnji = dict;
//	Dictionary predzadnji = ppzadnji->next;
//	Dictionary zadnji = predzadnji->next;
//	prvi->next = predzadnji;
//	predzadnji->next = treci;
//	ppzadnji->next = drugi;
//	drugi->next = zadnji;
//}

//char* najduza_ric(Dictionary dict)
//{
//	dict = dict->next;
//	char* najduza = dict->word;
//	while (dict->next != NULL)
//	{
//		if (strlen(najduza) < strlen(dict->word)) {
//			najduza = dict->word;
//		}
//		dict = dict->next;
//	}
//	return najduza;
//}

//void izmini_prvi_drugi(Dictionary dict) {
//	Dictionary dummy = dict;
//	Dictionary prvi_element = dict->next;
//	Dictionary drugi_element = dict->next->next;
//	Dictionary treci_element = dict->next->next->next;
//	prvi_element->next = treci_element;
//	drugi_element->next = prvi_element;
//	dummy->next = drugi_element;
//}


void main()
{
	FILE* fd;
	char buffer[1024];
	Dictionary dict;
	char* str1 = ("aaaaaa");
	char* str2 = ("bbbbbbb");
	int index = 6;
	fd = fopen("liar2.txt", "rt");
	if (fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}
	dict = create();

	while (readWord(fd, buffer))
	{
		printf("%s\n", buffer);
		add(dict, buffer);
	}

	fclose(fd);
	print(dict);
	destroy(dict);
}