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


void ListDump (Queue * queue, FILE * dumpFile) {

	shift (queue);

	fprintf (dumpFile, "digraph G {\n rankdir=LR\n");

	int i = 0;
	for (i = 0; i < queue->size; i++) 	{

		fprintf (dumpFile, "block%d [shape=record, label=\"block %d| {data %d | next %d | prev %d }\""
				   "];\n", i, i + 1, queue->data[i], queue->next[i], queue->prev[i]);
	}

	for (i = 0; i < queue->size; i++)   {

		if (queue->next[i] == 0) {

			fprintf (dumpFile, "block%d -> block%d;\n", i, 0);
			break;
		}

		fprintf (dumpFile, "block%d -> block%d;\n", i, i + 1);
	}

	fprintf (dumpFile, "head [shape=record, label=\"head\"];\n");
	fprintf (dumpFile, "tail [shape=record, label=\"tail\"];\n");
	fprintf (dumpFile, "head -> block%d;\n", 0);
	fprintf (dumpFile, "tail -> block%d;\n", queue->size - 1);	
	fprintf (dumpFile, "}");
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

	if (queue->size == queue->capacity || indexArgument > queue->capacity) // !!!
		ListResize (queue, indexArgument);

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

		queue->head = queue->next[indexArgument];
		queue->prev[queue->next[indexArgument]] = 0;
		queue->data[indexArgument] = 0;
		queue->next[indexArgument] = 0;
		queue->size--;

		return true;
	}

	if (queue->tail == indexArgument) {

		queue->tail = queue->prev[queue->tail];
		queue->next[queue->prev[indexArgument]] = 0;
		queue->prev[queue->next[indexArgument]] = 0;
	}

	queue->next[queue->prev[indexArgument]] = queue->next[indexArgument];
	queue->prev[queue->next[indexArgument]] = queue->prev[indexArgument];
	queue->data[indexArgument] = 0;
	queue->prev[indexArgument] = -1;
	queue->next[indexArgument] = -1;
	queue->size--;
	return true;
}


bool ListResize (Queue * queue, int indexArgument) {

	queue->capacity = (queue->capacity > indexArgument) ? RATIOQUEUECOEFFICIENT * queue->capacity : indexArgument;

	queue->data = (Elem_t * ) realloc (queue->data, sizeof (Elem_t) * queue->capacity            );
	CHECK_ERROR (queue->data == NULL, "Problem with allocating memory for queue->data. (realloc)");
	queue->next = (Elem_t * ) realloc (queue->next, sizeof (Elem_t) * queue->capacity            );
	CHECK_ERROR (queue->next == NULL, "Problem with allocating memory for queue->next. (realloc)");
	queue->prev = (Elem_t * ) realloc (queue->prev, sizeof (Elem_t) * queue->capacity            );
	CHECK_ERROR (queue->prev == NULL, "Problem with allocating memory for queue->prev. (realloc)");

	UninitializeElements (queue);

	return true;
}


void shift (Queue * queue) {

	Queue capacityQueue = 													 {};
	capacityQueue.data  = (Elem_t * ) calloc (queue->capacity, sizeof (Elem_t));
	capacityQueue.next  = (int    * ) calloc (queue->capacity, sizeof (Elem_t));
	capacityQueue.prev  = (int    * ) calloc (queue->capacity, sizeof (Elem_t));

	int i = 0, index = queue->head;
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