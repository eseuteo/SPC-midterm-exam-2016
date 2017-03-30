/*
 * scheduler.c
 *
 *  Created on: 30 mar. 2017
 *      Author: SrSut
 */

#include "scheduler.h"

void Create(Scheduler * scheduler) {
	scheduler->high = NULL;
	scheduler->low = NULL;
}

void Show(Scheduler scheduler) {
	PList aux = scheduler.high == NULL ? scheduler.low : scheduler.high;
	size_t i = 0;
	printf("- SCHEDULER CONTENTS ------\n");
	while (aux != NULL) {
		printf("%d. Process: '%s' Priority: %c\n", i++, aux->name, aux->priority);
		aux = aux->next;
	}
	printf("---------------------------\n");
}

void ReadFromFile(char * namef, Scheduler * plf) {
	FILE * fin;
	unsigned long numP, i = 0;
	unsigned long naruto;
	char auxName[20];
	char auxPrio;

	if ((fin = fopen(namef, "rb")) == NULL) {
		perror("kusha kiyo ka liao ya");
		return;
	}
	fread(&numP, sizeof(unsigned long), 1, fin);
	fread(&naruto, sizeof(unsigned long), 1, fin);
	while (i < numP && !feof(fin)) {
		fread(&auxName, sizeof(char), 20, fin);
		fread(&auxPrio, sizeof(char), 1, fin);
		insert(plf, auxName, auxPrio);
		i++;
	}

	fclose(fin);
}

void RemoveHighProc(Scheduler * plf, char * name) {
	PList aux = plf->high;
	PList prev = NULL;
	int cmp;

	while (aux != plf->low) {
		cmp = strcmp(name, aux->name);
		if (!cmp) {
			if (prev == NULL)
				plf->high = aux->next == plf->low ? NULL : aux->next;
			else
				prev->next = aux->next;
			free(aux);
		}
		prev = aux;
		aux = aux->next;
	}
}

void Destroy(Scheduler * plf) {
	PList aux = plf->high == NULL ? plf->high : plf->low;
	PList lib;

	while (aux != NULL) {
		lib = aux;
		aux = aux->next;
		free(lib);
	}
	plf->high = NULL;
	plf->low = NULL;
}

void insert(Scheduler * plf, char pName[20], char pPrio) {
	if (pPrio == highPriority)
		insertHigh(plf, pName);
	else {
		insertLow(plf, pName);
	}
}

void insertHigh(Scheduler * plf, char pName[20]) {
	PList newN = (PList) malloc(sizeof(Node));

	strcpy(newN->name, pName);
	newN->priority = 'A';
	newN->next = plf->high;
	plf->high = newN;
}

void insertLow(Scheduler * plf, char pName[20]) {
	PList newN = (PList) malloc(sizeof(Node));
	PList auxN;

	strcpy(newN->name, pName);
	newN->priority = 'B';
	newN->next = NULL;

	if (plf->low == NULL) {
		if (plf->high == NULL)
			plf->low = newN;
		else {
			auxN = plf->high;
			while (auxN->next != NULL)
				auxN = auxN->next;
			auxN->next = newN;
		}
	} else {
		auxN = plf->low;
		while (auxN->next != NULL)
			auxN = auxN->next;
		auxN->next = newN;
	}
}

