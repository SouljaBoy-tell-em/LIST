#include <stdio.h>
#include <stdlib.h>


enum errors {

	ERROR_OFF,
	ERROR_ON
};


typedef int Elem_t;
typedef struct queue {

	Elem_t * data;
	int    * next;
	int    * prev;
	int 	 head;
	int 	 tail;
	int 	 size;
	int 	 capacity;
	int 	 free;
} Queue;


void startInitialize (Queue * queue);
int ListCreator (Queue * queue, int capacity);
void ListPush (Queue * sp, int index, int arg);


#define CHECK_ERROR(condition, message_error) 			  \
            do {                                          \
               if  (condition) {                          \
                   printf ("%s", message_error);          \
                   return ERROR_ON;                       \
               }                                          \
            } while(false)


int main (void) {

	Queue queue = {};
	int capacity = 20;
	CHECK_ERROR (ListCreator (&queue, capacity), "Problem with creating QUEUE.");
	ListPush (&queue, 5, 228);
	ListPush (&queue, 7, 229);
	//ListPush (&queue, 4, 230);
	//ListPush (&queue, 6, 231);
	//ListPush (&queue, 7, 232);
	//ListPush (&queue, 9, 233);

	printf ("data: ");
	for (int i = 0; i < queue.capacity; i++)
		printf ("%d ", queue.data[i]);
	printf ("\nnext: ");
	for (int i = 0; i < queue.capacity; i++)
		printf ("%d ", queue.next[i]);
	printf ("\nprev: ");
	for (int i = 0; i < queue.capacity; i++)
		printf ("%d ", queue.prev[i]);


	return 0;
}


void startInitialize (Queue * queue) {

	queue->next[0] = 				   0;
	queue->data[0] = 				   0;
	queue->data[queue->capacity - 1] = 0;
	queue->prev[0] =				   0;

	int i = 0;
	for (i = 1; i < queue->capacity; i++) {

		queue->prev[i] = -1;
		queue->next[i] = -1 - i;
	}
}


int ListCreator (Queue * queue, int capacity) {

	if (queue == NULL)	return ERROR_ON;

	queue->head     		   = 		0;
	queue->tail     		   =        0;
	queue->size 			   = 		0;
	queue->free = 		1;
	queue->capacity 		   = capacity;

	queue->prev = (int * ) calloc (capacity, sizeof (int)	);
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->prev.");
	queue->next = (int * ) calloc (capacity, sizeof (int)	);
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->next.");
	queue->data = (int * ) calloc (capacity, sizeof (Elem_t));
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->data.");

	startInitialize (queue);

	return ERROR_OFF;
}


void ListPush (Queue * sp, int index, int arg) {

}