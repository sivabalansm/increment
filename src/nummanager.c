#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


/* Check if a file only contains a number and if it 
 * respects the bit limit of a long long int 
 * Returns 1 for valid file and 0 for invalid file*/

static int isValidFile(char *file) {
	FILE *fp = fopen(file, "r");
	if (fp == NULL) {
		perror("Error opening file\n");
		fclose(fp);
		return 0;
	};

	int bufSize = 17;
	char bufFile[bufSize];
	fgets(bufFile, bufSize, fp);

	fclose(fp);

	int bufFileLenght = strlen(bufFile);


	removeTrailingLF(&bufFileLenght, bufFile);


	// max character limit of 4,294,967,296 or if file only has or ""
	if (bufFileLenght > 10 || bufFileLenght == 0) {
		return 0;
	};

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

/* Gets the number at the beginning of a file and stops at the first non-parsable character.
 * Non-parsable characters: Whitespace (space, new line, tab) or everything except a digit 
 * Return the parsed number in the file */

long long int
parseNum(char *file) {
	if (!isValidFile(file)) {
		fprintf(stderr, "File is of invalid format, make sure it only contains a number\n");
		exit(1);
	};

	FILE *fp = fopen(file, "r");

	if (fp == NULL) {
		perror("Error opening file");
		fclose(fp);
		exit(1);
	};

	long long int numFile = 0;
	if (fscanf(fp, "%lld", &numFile) < 1) {
		fprintf(stderr, "PARSER FAILED: EOF encountered or No values converted\n");
		exit(1);
	};
	fclose(fp);
	//printf("%lld\n", numFile);

	return numFile;
}

/* Update the number in the file
 * Returns 1 if success or 0 if failiure */
int
updateNum(char *file, long int num) {
	long long int baseNumFile = parseNum(file);
	long long int newNum = baseNumFile + num;
	// printf("baseNum = %lld\nnewNum = %lld\n", baseNumFile, newNum);

	FILE *fp = fopen(file, "w");
	if (fp == NULL) {
		perror("Error opening file\n");
		fclose(fp);
		return 0;
	};
	
	if (fprintf(fp, "%lld", newNum) < 0) {
		perror("Could not write to file successfully");
		fclose(fp);
		return 0;
	};
		
	fclose(fp);
	return 1;
	

}


/*
int main(void) {

	printf("Num: %lld\n", parseNum("test.txt"));
	if (!updateNum("test.txt", -22)) {
		fprintf(stderr, "Failed to update number in file\n");
	};
	printf("New Num: %lld\n", parseNum("test.txt"));
	return 0;

}
*/
