#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include "nummanager.h"


/* argp constants, metadata for --help switch */

static char doc[]                     = "A program to increase/decrease a singular number in a file";
static char args_doc[]                = "FILE";
const  char *argp_program_version     = "Increment v1.0";
const  char *argp_program_bug_address = "noemail@email.com";


/* Arguments for the options */

struct arguments {
	short int     verbose;
	char *        file;
	long long int incrementNumber;
	short int     activeLimits;
	long long int lowerLimit; 
	long long int upperLimit;

};


/* Options for the tool, defines what is to be parsed and other metadata
 * for --help
 *
 * argp_option format : {NAME, KEY, OPTIONS_ARGUMENT_NAME, FLAGS, DOCS} */

static struct argp_option options[] = {
	{ "increment", 'i',   "N", OPTION_ARG_OPTIONAL,       "Increase number in FILE by N" },
	{ "decrement", 'd',   "N", OPTION_ARG_OPTIONAL,       "Increase number in FILE by N" },
	{  "upperlim", 'u', "MAX",                   0, "Set upper limit for number in FILE" },
	{  "lowerlim", 'l', "MIN",                   0, "Set lower limit for number in FILE" },
	{   "verbose", 'v',     0,                   0,                "verbose information" },
	{ 0 }
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

			arguments->incrementNumber += isPositive*strtoll(arg, NULL, 10);
			break;

		case 'l':
			// adding 0000 0001 to (0000 0000 or 0000 0010) using OR
			arguments->activeLimits |= LOWERLIMIT;
			arguments->lowerLimit = strtoll(arg, NULL, 10);
			break;

		case 'u':
			// adding 0000 0010 to (0000 0000 or 0000 00001) using OR
			arguments->activeLimits |= UPPERLIMIT;
			arguments->upperLimit = strtoll(arg, NULL, 10);
			break;

		case 'v':
			arguments->verbose = 1;
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


/* Description:
 * This is the main argp handler structure, it will contain all 
 * the necessary information to parse our char **argv 
 *
 * Format: 
 * { struct argp_option, void PARSE_FUNCTION, char *DOCUMENTATION_ON_COMMAND_ARGUMENTS, char *DESCRITION OF PROGRAM*/

static struct argp argp = { options, parse_opt, args_doc, doc };


/* Description:
 * Gives verbose information about the file update
 *
 * Parameters:
 * struct arguments *arguments : pointer to arguments structure that contains relavent information
 * 			         to update the file with the number, all of this will be displayed
 *
 * Return:
 * Nothing */

static void
verboseInfo(struct arguments *arguments) { 
	printf("FILE                   = %s\n",   arguments->file);
	printf("Current Number in FILE = %lld\n", parseNum(arguments->file));
	printf("Increment Number       = %lld\n", arguments->incrementNumber);
	printf("Active Limits          = %d\n",   arguments->activeLimits);
	printf("MIN                    = %lld\n", arguments->lowerLimit);
	printf("MAX                    = %lld\n", arguments->upperLimit);

	if (updateNum(arguments->file, arguments->incrementNumber, arguments->activeLimits, arguments->lowerLimit, arguments->upperLimit)) {
		printf("New Number in FILE     = %lld\n",  parseNum(arguments->file));

	} else {
		printf("[WARNING] Updating number in FILE failed\n");

	};
}



int main(int argc, char **argv) {

	struct arguments arguments;

	// Assign default values
	arguments.verbose          = 0;
	arguments.incrementNumber  = 0;
	arguments.activeLimits     = 0;
	arguments.lowerLimit       = 0;
	arguments.upperLimit       = 0;
	

	if (argp_parse(&argp, argc, argv, 0, 0, &arguments) != 0) {
		perror("[ERROR] parsing, argp_parse");
		return 1;
	};

	if (arguments.verbose) {
		verboseInfo(&arguments);
		return 0;
	};

	updateNum(arguments.file, arguments.incrementNumber, arguments.activeLimits, arguments.lowerLimit, arguments.upperLimit);

	return 0;
}
