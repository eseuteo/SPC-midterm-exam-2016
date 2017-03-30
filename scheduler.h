/*
 * scheduler.h
 *
 *  Created on: 30 mar. 2017
 *      Author: SrSut
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define highPriority 'A'
#define lowPriority 'B'

typedef struct node {
	char name[20];
	char priority;
	struct node * next;
} Node;
typedef Node* PList;

typedef struct scheduler {
	struct node * high, * low;
} Scheduler;

void Create(Scheduler * scheduler);

void Show(Scheduler scheduler);

void ReadFromFile(char * namef, Scheduler * plf);

void RemoveHighProc(Scheduler * plf, char * name);

void Destroy(Scheduler * plf);

void insert(Scheduler * plf, char pName[20], char pPrio);

void insertHigh(Scheduler * plf, char pName[20]);

void insertLow(Scheduler * plf, char pName[20]);



#endif /* SCHEDULER_H_ */
