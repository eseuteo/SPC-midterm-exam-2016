/*
 * main.c
 *
 *  Created on: 29 mar. 2017
 *      Author: SrSut
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "scheduler.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments. Usage: main fileName)\n") ;
        exit(-1) ;
    }

    Scheduler scheduler ;

    Create(&scheduler) ;
    Show(scheduler) ;

    ReadFromFile(argv[1], &scheduler) ;
    Show(scheduler) ;

    RemoveHighProc(&scheduler, "Memory Manager") ;
    RemoveHighProc(&scheduler, "HTTP daemon") ;
    Show(scheduler) ;

    Destroy(&scheduler) ;
    Show(scheduler) ;
    return EXIT_SUCCESS;
}
