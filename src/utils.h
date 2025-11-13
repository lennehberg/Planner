#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

#define DATE_VAR_LEN 8
#define TIME_VAR_LEN 6
#define TITLE_LEN 256
#define DESC_LEN 300

#include <time.h>
#include <stdbool.h>
#include <string.h>

/**
 * boolean for partability
 */
typedef char bool_t; 

/**
 * Event Date type - DDMMYYYY format
 */
typedef time_t pdate_t; 

/**
 * Event Time type - HHMMSS format
 */ 
typedef time_t ptime_t;

/**
 * Event Title type - limited to 256 characters
 */ 
typedef char ptitle_t[TITLE_LEN];

/**
 * Event Description type - limited to 65536 characters
 */ 
typedef char pdesc_t[DESC_LEN];


/**
 * Priorety enum - starting from no priorety (0) to high priorety (3)
 */
typedef enum {
	NO_PRIORETY,
	PRIORETY_LOW,
	PRIORETY_MED,
	PRIORETY_HIGH
} Priorety;


void *find_lower_bound(const void *key, const void *base, size_t num, size_t size, 
			int (*compare)(const void *, const void *));

#endif // UTILS_H	

