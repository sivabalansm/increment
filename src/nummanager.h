#ifndef NUMMANAGER_H
#define NUMMANAGER_H


/* Gets the number at the beginning of a file and stops at the first non-parsable character.
 * Non-parsable characters: Whitespace (space, new line, tab) or everything except a digit 
 * Return the parsed number in the file */

long long int parseNum(char *file);

/* Update the number in the file if it is a valid file,
 * check isValidFile(char *file) function
 * uses parseNum to get the original number before updating
 * Returns 1 if success or 0 if failiure */
int           updateNum(char *file, long int num);

#endif 




