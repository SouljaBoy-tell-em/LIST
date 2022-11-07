#include "head_list.h"
#include "list.h"


int main (void) {

	Queue queue = {};
	int capacity = 7;
	CHECK_ERROR (ListCreator (&queue, capacity), "Problem with creating QUEUE.");

	FILE * dumpFile = dumpFile = fopen ("dumpfile.txt", "w");
	CHECK_ERROR(dumpFile == NULL, "Problem with opening DUMPFILE.");

	ListPush (&queue, 5, 228);
	ListPush (&queue, 7, 229);
	ListPush (&queue, 4, 230);
	ListPush (&queue, 6, 231);
	ListPush (&queue, 2, 232);
	ListPush (&queue, 3, 233);
	ListPush (&queue, 5, 234);
	ListPush (&queue, 8, 235);
	ListPush (&queue, 11, 2232);
	ListPop (&queue, 11);
	ListPop (&queue, 8);
	ListPop (&queue, 1);
	ListPop (&queue, 7);
	shift (&queue);


	printf ("\nCAPACITY: %d\n", queue.capacity);
	printf ("SIZE: %d\n", queue.size);
	printf ("HEAD: %d\n", queue.head);
	printf ("TAIL: %d\n", queue.tail);
	printf ("\nLIST: ");
	for (int i = 0; i < queue.size; i++)
		printf ("%3d ", queue.data[i]);
	printf ("\nNEXT: ");
	for (int i = 0; i < queue.size; i++)
		printf ("%3d ", queue.next[i]);
	printf ("\nPREV: ");
	for (int i = 0; i < queue.size; i++)
		printf ("%3d ", queue.prev[i]);


	ListDump (&queue, dumpFile);
	return 0;
}
