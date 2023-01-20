#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct node {
	char *data;
	struct node *next;
};


int main(int argc, char *argv[])
{
	if((argc != 2) && (argc != 3)) {
		fprintf(stderr, "usage: reverse <input> <output> \n");
		return 1;
	}


	FILE *stream;
	FILE *output;
	char *line;
	size_t len = 0;
	struct node *head = NULL;

	stream = fopen(argv[1], "r");
	if (errno == ENOMEM) {
		fprintf(stderr, "error: cannot open file '%s' \n", argv[1]);
		return 1;
	}

	if (argc == 3) {
		output = fopen(argv[2], "w");
		if (errno == ENOMEM) {
			fprintf(stderr, "error: cannot open file '%s' \n", argv[2]);
			return 1;
		}

		int str_len = strlen(argv[1]);

		if (strncmp(argv[1], argv[2], str_len) == 0) {
			fprintf(stderr, "error: input and output must differ \n");
			return 1;
		}
	}


	while (getline(&line, &len, stream) != -1) {
		char* new_line = malloc(sizeof(char) * (len+1));
		if (errno == ENOMEM) {
			fprintf(stderr, "error: malloc failed \n");
			free (new_line);
			return 1;
		}
		strncpy(new_line, line, len);

		struct node *new_node = (struct node*)malloc(sizeof(struct node));
		if (errno == ENOMEM) {
			fprintf(stderr, "error: malloc failed \n");
			free (new_node);
			return 1;
		}

		new_node->data=new_line;
		new_node->next=head;
		head = new_node;

		
	}
	free(line);

	while (head != NULL) {
		if (argc == 3) {
			fprintf(output, "%s", head->data);
		} else if (argc == 2) {
			fprintf(stdout, "%s", head->data);
		}


		struct node *cur_node = head;
		head = head->next;
		free(cur_node->data);
		free(cur_node);
	}

	fclose(stream);
	return 0;
}
