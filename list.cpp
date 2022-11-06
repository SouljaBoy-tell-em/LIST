#include <stdio.h>
#include <stdlib.h>


enum errors {

	ERROR_OFF,
	ERROR_ON
};


#define RATIOQUEUECOEFFICIENT 2
#define CHECK_ERROR(condition, message_error) 			  \
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
bool ListPop (Queue * queue, int indexArgument);
bool ListPush (Queue * sp, int indexArgument, Elem_t argument);
bool ListResize (Queue * queue);
void shift (Queue * queue);
void UninitializeElements (Queue * queue);


int main (void) {

	Queue queue = {};
	int capacity = 7;
	CHECK_ERROR (ListCreator (&queue, capacity), "Problem with creating QUEUE.");
	ListPush (&queue, 5, 228);
	ListPush (&queue, 7, 229);
	ListPush (&queue, 4, 230);
	ListPush (&queue, 6, 231);
	ListPush (&queue, 2, 232);
	ListPush (&queue, 3, 233);
	ListPush (&queue, 5, 234);
	ListPush (&queue, 8, 235);
	ListPush (&queue, 11, 2232);
	ListPop (&queue, 6);
	ListPop (&queue, 11);


	printf ("\nCAPACITY: %d\n", queue.capacity);
	printf ("SIZE: %d\n", queue.size);

	shift (&queue);
	printf ("\nLIST: ");
	for (int i = 0; i < queue.size; i++)
		printf ("%d ", queue.data[i]);
	printf ("\nNEXT: ");
	for (int i = 0; i < queue.size; i++)
		printf ("%d ", queue.next[i]);
	printf ("\nPREV: ");
	for (int i = 0; i < queue.size; i++)
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
		queue->next[i] = -1;
		queue->data[i] = 0;
	}
}


int ListCreator (Queue * queue, int capacity) {


	queue->head     		   = 		0;
	queue->tail     		   =        0;
	queue->size 			   = 		0;
	queue->capacity 		   = capacity;

	queue->prev = (int * ) calloc (capacity, sizeof (int)	);
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->prev.");
	queue->next = (int * ) calloc (capacity, sizeof (int)	);
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->next.");
	queue->data = (Elem_t * ) calloc (capacity, sizeof (Elem_t));
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->data.");

	startInitialize (queue);

	return ERROR_OFF;
}


bool ListPush (Queue * queue, int indexArgument, Elem_t argument) {

	if (queue->size == 0) {

		queue->size++;
		queue->data[queue->size] =        argument;
		queue->next[queue->size] =               0;
		queue->prev[queue->size] =               0;
		queue->head              =     queue->size;
		queue->tail              =     queue->size;

		return true;
	}

	if (queue->size == queue->capacity)
		ListResize (queue);

	if (queue->data[indexArgument] == 0) {

		queue->prev[indexArgument]              =   queue->tail;
		queue->next[indexArgument]              =             0;
		queue->next[queue->prev[indexArgument]] = indexArgument;
		queue->tail                             = indexArgument;
		queue->data[indexArgument]              =      argument;
		queue->size++;
	}

	return true;
}


bool ListPop (Queue * queue, int indexArgument) {

	if (queue->head == indexArgument) {

		queue->head    =  queue->next[indexArgument];
		queue->data[1] = queue->data[queue->next[1]];
		queue->next[1] = queue->next[queue->next[1]];
		queue->prev[1] = 0;
		return true;
	}

	if (queue->tail == indexArgument) {

		queue->data[indexArgument] = 0;
		queue->next[indexArgument] = -1;
		queue->prev[indexArgument] = -1;
		queue->tail = queue->prev[queue->tail];
		queue->next[queue->prev[indexArgument]] = 0;
		queue->prev[queue->next[indexArgument]] = -1;
		return true;
	}

	queue->next[queue->prev[indexArgument]] = queue->next[indexArgument];
	queue->prev[queue->next[indexArgument]] = queue->prev[indexArgument];
	queue->data[indexArgument] = 0;
	queue->prev[indexArgument] = -1;
	queue->next[indexArgument] = -1;
	return true;
}


bool ListResize (Queue * queue) {

	queue->capacity = RATIOQUEUECOEFFICIENT * queue->capacity;
	printf ("queue->capacity: %d\n", queue->capacity);

	queue->data = (Elem_t * ) realloc (queue->data, RATIOQUEUECOEFFICIENT * sizeof (Elem_t) * queue->capacity);
	CHECK_ERROR (queue->data == NULL, "Problem with allocating memory for queue->data. (realloc)"			 );
	queue->next = (Elem_t * ) realloc (queue->next, RATIOQUEUECOEFFICIENT * sizeof (Elem_t) * queue->capacity);
	CHECK_ERROR (queue->next == NULL, "Problem with allocating memory for queue->next. (realloc)"    		 );
	queue->prev = (Elem_t * ) realloc (queue->prev, RATIOQUEUECOEFFICIENT * sizeof (Elem_t) * queue->capacity);
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->prev. (realloc)"			 );

	UninitializeElements (queue);

	return true;
}


void shift (Queue * queue) {

	Queue capacityQueue = 													 {};
	capacityQueue.data  = (Elem_t * ) calloc (queue->capacity, sizeof (Elem_t));
	capacityQueue.next  = (int    * ) calloc (queue->capacity, sizeof (Elem_t));
	capacityQueue.prev  = (int    * ) calloc (queue->capacity, sizeof (Elem_t));

	int i = 0, index = 1;
	for (i = 0; i < queue->size; i++) {

		capacityQueue.data[i] = queue->data[index];
		capacityQueue.next[i] = queue->next[index];
		capacityQueue.prev[i] = queue->prev[index];
		index                 = queue->next[index];
	}

	for (i = 0; i < queue->size; i++) {

		queue->data[i] = capacityQueue.data[i];
		queue->next[i] = capacityQueue.next[i];
		queue->prev[i] = capacityQueue.prev[i];
	}

	free (capacityQueue.data);
	free (capacityQueue.next);
	free (capacityQueue.prev);
}


void UninitializeElements (Queue * queue) {

	int i = 0;
	for (i = queue->size + 1; i < queue->capacity; i++) {

		queue->next[i] = -1;
		queue->prev[i] = -1;
		queue->data[i] =  0;
	}
}
