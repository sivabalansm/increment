#ifndef NUMMANAGER_H
#define NUMMANAGER_H

/* Bit field boolean options. These are added
 * through the OR bit wise operator to the 
 * short int activeLimits vairable
 * 
 * Binary Values:
 * LOWERLIMIT : 0000 0001
 * UPPERLIMIT : 0000 0010 */
#define LOWERLIMIT 0x1
#define UPPERLIMIT 0x2

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

long long int parseNum(char *file);


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

int           updateNum(char *file, long long int num, short int activeLimits, long long int lowerLimit, long long int upperLimit);

#endif 




