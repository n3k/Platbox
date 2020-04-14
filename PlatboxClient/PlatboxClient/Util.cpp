// Written by Enrique Nissim (IOActive) 06/2018

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char **parse_arguments(char *command_line, char arg_delim) {
	char delim[2] = { 0 };
	if (arg_delim == NULL) {
		delim[0] = ' ';
	}
	else {
		delim[0] = arg_delim;
	}
	char **args = (char **)calloc(1, 0x40);
	char *token;
	char **p = args;
	unsigned int argc = 1;

	p++;
	token = strtok(command_line, delim);
	while (token != NULL) {
		*p = token;
		token = strtok(NULL, delim);
		p++;
		argc++;
	}

	*(unsigned int *)&args[0] = argc;

	return args;
}

void get_user_input(char *input, int size) {
	memset(input, 0x00, size);
	fgets(input, size, stdin);

	// clean the trailing '\n'
	char *pos;
	if ((pos = strchr(input, '\n')) != NULL)
		*pos = '\0';
}

void hexstring_to_opcodes(char *hexstring, unsigned char **ppOpcodes, unsigned int *size) {
	char *pos = hexstring;
	unsigned int len = (strlen(hexstring) / 2) + 1;
	*size = len - 1;
	unsigned char *val = (unsigned char *) malloc(len);
	memset(val, 0x00, len);

	int i = 0;
	for (i = 0; i < *size; i++) {
		sscanf(pos, "%2hhx", &val[i]);
		pos += 2;
	}

	printf("0x");
	for (i = 0; i < *size; i++) {
		printf("%02x", val[i]);
	}
	printf("\n");

	*ppOpcodes = val;
}

// Economou function
void print_memory(unsigned long address, char *buffer, unsigned int bytes_to_print)
{
	unsigned int cont;
	unsigned int i;
	const unsigned short bytes = 16;

	/* Print the lines */
	for (cont = 0; cont < bytes_to_print; cont = cont + bytes)
	{
		printf("%p | ", (void *)address);
		address = address + bytes;

		for (i = 0; i < bytes; i++)
		{
			if (i < (bytes_to_print - cont))
			{
				printf("%.2x ", (unsigned char)buffer[i + cont]);
			}
			else
			{
				printf("   ");
			}
		}

		//Space between two columns
		printf("| ");

		//Print the characters
		for (i = 0; i < bytes; i++)
		{
			if (i < (bytes_to_print - cont))
			{
				printf("%c", (isgraph(buffer[i + cont])) ? buffer[i + cont] : '.');
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void error(char *msg) {
	fprintf(stderr, "Error: %s\n", msg);
	exit(-1);
}

