#include <stdio.h>
#include <stdlib.h>

struct InputBuffer_t {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
};
typedef struct InputBuffer_t InputBuffer;

InputBuffer* new_input_buffer() {
	InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;
	
	return input_buffer;
}

void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
	ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}

	input_buffer->input_length = bytes_read -1;
	input_buffer->buffer[bytes_read -1] = 0;
}

int main (void) {
	InputBuffer* input_buffer = new_input_buffer();
	while (1) {
		print_prompt();
		read_input(input_buffer);
		if (input_buffer->buffer[0] == '.') {
			switch (do_meta_command(input_buffer)) {
				case (META_COMMAND_SUCCESS):
					continue;
				case (META_COMMAND_UNRECOGNIZED_COMMAND):
					printf("Unrecognized command '%s'\n", input_buffer->buffer);
					continue;
			}
		}

		Statement statement;
		switch (prepare_stateemnt(input_buffer, &statement)) {
			case (PREPARE_SUCCESS):
				break;
			case (PREPARE_UNRECOGNIZED_STATEMENT):
				printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
				continue;
		}

		execute_statement(&statement);
		printf("Executed.\n");
	}
}
