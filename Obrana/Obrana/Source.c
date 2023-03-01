
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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

// briše cijeli rječnik
void destroy(Dictionary dict);

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w));

int filter(Word* w);

Dictionary create() {
	Dictionary dict = (Word*)malloc(sizeof(Word));
	dict->word = "Novi rjecnik";
	dict->count = 0;
	dict->next = NULL;
	return dict;
}

void add(Dictionary dict, char* str) {
	Dictionary novi = (Dictionary)malloc(sizeof(Word));
	Dictionary tmp = dict;
	novi->word = _strdup(str);
	novi->count = 1;
	novi->next = NULL;
	while (1) {
		if (tmp->next == NULL) {
			tmp->next = novi;
			return;
		}
		else if (strcmp(tmp->next->word, str) == 0) {
			tmp->next->count++;
			return;
		}
		else if (strcmp(tmp->next->word, str) > 0) {
			novi->next = tmp->next;
			tmp->next = novi;
			return;
		}
		else {
			tmp = tmp->next;
		}
	}
}

void print(Dictionary dict) {
	Dictionary tmp = dict;
	while (tmp != NULL) {
		printf("Rijec->%s i Broj->%d\n", tmp->word, tmp->count);
		tmp = tmp->next;
	}
}

void destroy(Dictionary dict) {
	Dictionary tmp;
	while (dict) {
		Dictionary novi = dict->next;
		free(novi->word);
		tmp = dict->next;
		free(dict);
		dict = tmp;
	}
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w)) {
	Dictionary tmp = indict;
	Dictionary nxt = indict->next;
	while (nxt->next != NULL) {
		if (filter(nxt) == 0) {
			Dictionary novi = nxt;
			free(novi->word);
			nxt = nxt->next;
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

Dictionary predzadnje(Dictionary dict, char* str)
{
	Dictionary predzadnji = (Dictionary)malloc(sizeof(Word));
	predzadnji->word = _strdup(str);
	predzadnji->count = 1;
	predzadnji->next = NULL;
	Dictionary zadnji = dict->next;
	Dictionary set = dict;
	while (zadnji->next != NULL)
	{
		zadnji = zadnji->next;
		set = set->next;
	}
	set->next = predzadnji;
	predzadnji->next = zadnji;
	return dict;
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

void main()
{
	FILE* fd;
	char buffer[1024];
	Dictionary dict;
	char str[8] = "aaaaaaa";

	fd = fopen("liar.txt", "rt");
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

	/*print(dict);

	printf("Filtrirane rijeci\n");
	filterDictionary(dict, *filter);
	*/
	Dictionary brr = predzadnje(dict, str);
	print(dict);

	destroy(dict);
}