#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include "nummanager.h"

/* argp constants, metadata for --help switch */
static char doc[]                     = "A program to increase/decrease a singular number in a file";
static char args_doc[]                = "FILE";
const  char *argp_program_version     = "increment v1.0";
const  char *argp_program_bug_address = "noemail@email.com";

/* Arguments for the options */
struct arguments {
	char     *file;
	long int increment_number;

};

/* Options for the tool, defines what is to be parsed and other metadata
 * for --help
 *
 * argp_option format : {NAME, KEY, OPTIONS_ARGUMENT_NAME, FLAGS, DOCS} */
static struct argp_option options[] = {
	{"increment", 'i', "N", OPTION_ARG_OPTIONAL, "Increase number in FILE by N"},
	{"decrement", 'd', "N", OPTION_ARG_OPTIONAL, "Increase number in FILE by N"},
	{0}
};


/* Parser function argp is going to use.
 * Will be provided as a parameter to the structure argp
 *
 * Parameters
 * key: 	It is a number representing the given option.
 * 		If it is can be an ascii character, it will use the number
 * 		for the ascii value for the KEYs in argp_option
 * arg: 	Value of the argument for every option (so key).
 * 		If it is an argument to the tool (the FILE), then it 
 * 		will be associated with the key ARGP_KEY_ARG 
 * argp_state:  the state while the function is run in argp for every
 * 		argument in char **argv
 *
 * Return value:
 * error_t is int typedef. The function MUST return 0 to be rerun
 * or else the program will fail to parse any other char **argv than
 * the first. */
static error_t 
parse_opt(int key, char *arg, struct argp_state *state) {
	struct arguments *arguments = state->input;

	switch (key) {
		case 'i': /* Fall through */
		case 'd':
			if (arg == NULL) {
				arg = "1";
			};

			// Find wheather we should increment or decrement
			int isPositive = (key == 'i' ? 1 : -1);

			arguments->increment_number += isPositive*strtol(arg, NULL, 10);
			break;

		case ARGP_KEY_ARG:
			if (state->arg_num >= 1) {
				printf("Too many args\n");
				argp_usage(state);
			};

			arguments->file = arg;
			break;

		case ARGP_KEY_END:
			if (state->arg_num < 1) { 
				argp_usage(state);
			};
			break;

		default:
			return ARGP_ERR_UNKNOWN;

	};
	return 0;


}

/* This is the argp handler, it will contain all 
 * the necessary information to parse our 
 * char **argv */
static struct argp argp = { options, parse_opt, args_doc, doc };



int main(int argc, char **argv) {

	// Assign default values
	struct arguments arguments;
	arguments.increment_number = 0;
	

	if (argp_parse(&argp, argc, argv, 0, 0, &arguments) != 0) {
		perror("Error parsing, argp_parse");
	};

	printf("File: %s\n", arguments.file);
	printf("Increment Number: %ld\n", arguments.increment_number);
	printf("Current num in file %lld\n", parseNum(arguments.file));
	updateNum(arguments.file, arguments.increment_number);
	printf("New num in file %lld\n", parseNum(arguments.file));


	return 0;
}
