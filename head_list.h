#ifndef _FUNC_H__
#define _FUNC_H__


#include <stdio.h>
#include <stdlib.h>


enum errors {

	ERROR_OFF,
	ERROR_ON
};


#define RATIOQUEUECOEFFICIENT 2
#define CHECK_ERROR(condition, message_error) 		    	 \
            do {                                          \
               if  (condition) {                          \
                   printf ("%s", message_error);          \
                   return ERROR_ON;                       \
               }                                          \
            } while(false)


typedef int Elem_t;
typedef struct queue {

	Elem_t * data;
	int    * next;
	int    * prev;
	int 	 head;
	int 	 tail;
	int 	 size;
	int 	 capacity;
} Queue;


void startInitialize (Queue * queue);
int  ListCreator (Queue * queue, int capacity);
void ListDump (Queue * queue, FILE * dumpFile);
bool ListPop (Queue * queue, int indexArgument);
bool ListPush (Queue * sp, int indexArgument, Elem_t argument);
bool ListResize (Queue * queue, int indexArgument);
void shift (Queue * queue);
void UninitializeElements (Queue * queue);


#endif