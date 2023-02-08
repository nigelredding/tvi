#include <stdio.h>

char *filename = "sample.txt";

/**
 * Doubly linked list implementation.
 */
typedef struct list_t = {
	char *data;
	list_t *next;
} list_t;

/**
 * Prints the cell
 */
void print_cell(list_t *cell) {
	printf("%s", cell->data);
}

/**
 * Prints the list, given the head
 */
void print_list(list_t *head) {
	while ((head=head->next)) {
		print_cell(head);
		if (head->next) {
			printf(" -> ");
		}
	}
}

/**
 * Appends data to end of list, given the head
 */
list_t *append(list_t *head, void *data) {
	list_t *cell = (list_t *)malloc(sizeof(list_t));
	cell->data = data;
	cell->next = NULL;

	if (!head) {
		return cell;
	}

	list_t *cur = head;
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = cell;

	return head;
}

/**
 * Prepends data to begining of list, given the head
 */
list_t *prepend(list_t *head, void *data) {
        list_t *cell = (list_t *)malloc(sizeof(list_t));
        cell->data = data;
        cell->next = head;
	return cell;
}

/**
 * Deletes the cell at index n.
 *
 * NULL if idx < 0 or if idx > len(list)
 * Returns the head (new head if n=0)
 */
list_t *delete(list_t *head, int idx) {
	if (!head) {
		return NULL;
	}

	list_t *cur;
	int i;
	for (i = 0; i < idx-1; i++) {
		if (!cur) {
			return NULL;
		}
		cur = cur->next;
	}
	// FINISH
}

/**
 * String <-> List serialization
 */


/**
 * Creates list from text. Each line, delimited by \n,
 * is placed in a cell.
 */
list_t *make_list_from_text(char *text) {
	return NULL;
}

/**
 * Creates a char * buffer from a list. Each cell corresponds
 * to a line in the buffer.
 */
char *make_buffer_from_list(list_t *file_content) {
	return NULL;
}


/**
 * File I/O
 */

typedef struct editor_file {
	FILE *fd;
	char *buffer;
	list_t *lis;
} editor_file;


/**
 * Creates the file content list given a filename
 */
editor_file read_file(char *filename) {
	return NULL;
}

/**
 * Updates the buffer to match the list.
 */
void sync_structure(editor_file *file) {
	file->buffer = make_buffer_from_list(file->lis);
}






/**
 * Ncurses stuff
 */

int main(int argc, char **argv) {
	return 0;
}

