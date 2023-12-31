#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nummanager.h"

/* Description:
 * removes the trailing new line character at the end 
 * of the buffer. If the buffer has a new line,
 * it adjusts the lenght and buffer such that the new line
 * is ignored.
 *
 * Parameters:
 * int *  lenght : lenght of the the buffer, will be adjusted 
 * 		   if a new line is detected at the end of the buffer
 * 		   by reducing it by 1.
 * char * buf    : the contents of the buffer, will be adjusted if
 * 		   new line is detected at the end by replacing it with 
 * 		   a null character \0.
 *
 * Return:
 * Nothing
 */

static void
removeTrailingLF(int *lenght, char *buf) {
	if (*lenght <= 0) {
		return;
	};

	int lastIdx = (*lenght) - 1;

	if (buf[lastIdx] == '\n') {
		buf[lastIdx] = '\0';
		*lenght -= 1;
	};
	

}


/* Description:
 * Check if a file only contains a number and if it 
 * respects the byte lenght limit of a long long int 
 *
 * Parameters:
 * char *file : file name of the file with the number
 *
 * Return:
 * Returns 1 for valid file and 0 for invalid file */

static int
isValidFile(char *file) {

	FILE *fp = fopen(file, "r");

	if (fp == NULL) {
		perror("Error opening file");
		return 0;
	};


	int bufSize = 17;
	char bufFile[bufSize];

	fgets(bufFile, bufSize, fp);

	int bufFileLenght = strlen(bufFile);

	fclose(fp);


	removeTrailingLF(&bufFileLenght, bufFile);


	// Max character limit of 4,294,967,296 or if file only has or "" so 10 or 0 characters respectively
	if (bufFileLenght > 10 || bufFileLenght == 0) {
		return 0;
	};


	// Check if every character is a number and if the beginning has a negative or not
	for (int idx = 0; idx < bufFileLenght; idx++) {

		char c = bufFile[idx];

		// Check if its a negative number, then it is valid
		if (idx == 0 && c == '-') {
			continue;
		};

		if (c < 48 || c > 57) {
			return 0;
		};
	};

	return 1;

}


/* Description:
 * Gets the number at the beginning of a file and stops at the first non-parsable character.
 * Non-parsable characters: Whitespace (space, new line, tab) or everything except a digit 
 * Return the parsed number in the file 
 *
 * Parameters:
 * char *file : file name of the file with the number
 *
 * Return:
 * Returns the number inside the file */

long long int
parseNum(char *file) {
	if (!isValidFile(file)) {
		fprintf(stderr, "File is of invalid format, make sure it only contains a number\n");
		exit(1);
	};

	FILE *fp = fopen(file, "r");

	if (fp == NULL) {
		perror("[ERROR] opening file for reading");
		exit(1);
	};

	long long int numFile = 0;

	if (fscanf(fp, "%lld", &numFile) < 1) {
		fprintf(stderr, "[PARSER FAILED] EOF encountered or No values converted\n");
		fclose(fp);
		exit(1);
	};

	fclose(fp);

	return numFile;
}


/* Description:
 * Update the number in the file
 *
 * Parameters:
 * char *        file         : file name of the 
 * long long int num          : the value of the number by which the number in the file will be incremented by
 * short         activeLimits : intger value of a bitfield representing if upperLimit or lowerLimit is turned ON or NOT
 * 				using the constants UPPERLIMIT or LOWERLIMIT which are defined in nummanager.h
 * long long int lowerLimits  : the lower limit that the newNum cannot go under
 * long long int upperLimits  : the upper limit that the newNum cannot go above
 *
 * Return Value:
 * Returns 1 if success on writing the new number or 0 if failiure to writing the new number */

int
updateNum(char *file, long long int num, short int activeLimits, long long int lowerLimit, long long int upperLimit) {
	long long int baseNumFile, newNum;

	baseNumFile = parseNum(file);
	newNum      = baseNumFile + num;

	if ((activeLimits & LOWERLIMIT && lowerLimit > newNum) || (activeLimits & UPPERLIMIT && upperLimit < newNum)) {
		fprintf(stderr, "[WARNING] Cannot go past the limit\n");
		return 0;
	}


	FILE *fp = fopen(file, "w");

	if (fp == NULL) {
		perror("[ERROR] opening file for writing");
		return 0;
	};
	

	if (fprintf(fp, "%lld", newNum) < 0) {
		perror("[ERROR] writing to file");
		fclose(fp);
		return 0;
	};
		
	fclose(fp);

	return 1;
}

