/**
 * Tiny vi clone.
 *
 * nvr 2023-02-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *filename = "sample.txt";

/**
 * Doubly linked list implementation.
 */
typedef struct list_t {
	char *data;
	struct list_t *next;
	struct list_t *prev;
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
	if (!head) {
		return;
	}
	while (head) {
		print_cell(head);
		if (head->next) {
			printf(" -> ");
		}
		head = head->next;
	}
}

/**
 * Appends data to end of list, given the head
 */
list_t *append(list_t *head, void *data) {
	list_t *cell = (list_t *)malloc(sizeof(list_t));
	cell->data = data;
	cell->next = NULL;
	cell->prev = NULL;

	if (!head) {
		return cell;
	}

	list_t *cur = head;
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = cell;
	cell->prev = cur;

	return head;
}

/**
 * Prepends data to begining of list, given the head
 */
list_t *prepend(list_t *head, void *data) {
        list_t *cell = (list_t *)malloc(sizeof(list_t));
        cell->data = data;
        cell->next = head;
	cell->prev = NULL;

	head->prev = cell;
	
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
	
	list_t *to_delete = cur->next;
	if (!to_delete) {
		return NULL;
	} else {
		free((void *)to_delete->data);
	}

	cur->next = cur->next->next;
	cur->next->next->prev = cur->next;

	return head;
}

/**
 * String <-> List serialization
 */


/**
 * Creates list from text. Each line, delimited by \n,
 * is placed in a cell.
 */
list_t *make_list_from_text(char *text) {
	list_t *lis = NULL;

	int idx = 0;
	int line_idx = 0;
	char line[256]; // TODO make dynamic
	memset(line, '\0', 256);
	while (text[idx] != '\0') {
		if (text[idx] == '\n') {
			lis = append(lis, strdup(line));
			line_idx = 0;
			memset(line, '\0', 256);
		} else {
			line[line_idx] = text[idx];
			line_idx++;
		}
		idx++;
	}

	return lis;
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
	list_t *lis; // head of data
	list_t *cur; // cursor
	int num_lines;
	int row_idx;
} editor_file;


/**
 * Creates the file content list given a filename
 */
editor_file read_file(char *filename) {
	editor_file ef;
	ef.fd = fopen(filename, "r+");
	ef.num_lines = 0;
	
	size_t num_bytes = 0;
	int ch;
	while ((ch = fgetc(ef.fd)) != EOF) {
		num_bytes++;
		if (ch == '\n') {
			ef.num_lines++;
		}
	}
	ef.num_lines++; // always one more than number of newlines

	ef.buffer = (char *)malloc(num_bytes);
	ef.lis = make_list_from_text(ef.buffer);
	ef.cur = ef.lis;
	ef.row_idx = 0;

	return ef;
}

/**
 * Updates the buffer to match the list.
 */
void sync_structure(editor_file *file) {
	file->buffer = make_buffer_from_list(file->lis);
}

/**
 * Updates the file to match the buffer.
 */
size_t sync_disk_file(editor_file *file) {
	sync_structure(file);
	return fwrite(file->buffer, sizeof(char), strlen((char *)file->buffer), file->fd);
}

/**
 * Updates the cur and row_idx to go down.
 */
void go_down(editor_file *file) {
	if (file->row_idx == file->num_lines-1) {
		return;
	}
	file->row_idx++;
	file->cur = file->cur->next;
}

/**
 * Updates the cur and row_idx to go up.
 */
void go_up(editor_file *file) {
	if (file->row_idx == 0) {
		return;
	}
	file->row_idx--;
	file->cur = file->cur->prev;
}

/**
 * Ncurses stuff
 */
// TODO


int main(int argc, char **argv) {
	return 0;
}

