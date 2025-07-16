#ifndef UTILS_H
#define UTILS_H

#define FALSE 0
#define TRUE 1

#define DATE_VAR_LEN 8
#define TIME_VAR_LEN 6
#define TITLE_LEN 256
#define DESC_LEN 65536

/**
 * boolean for partability
 */
typedef char bool_t; 

/**
 * Event Date type - DDMMYYYY format
 */
typedef const char pdate_t[DATE_VAR_LEN]; 

/**
 * Event Time type - HHMMSS format
 */ 
typedef const char ptime_t[TIME_VAR_LEN];

/**
 * Event Title type - limited to 256 characters
 */ 
typedef const char ptitle_t[TITLE_LEN];

/**
 * Event Description type = limited to 65536 characters
 */ 
typedef const char pdesc_t[DESC_LEN];


/**
 * Priorety enum - starting from no priorety (0) to high priorety (3)
 */
typedef enum {
	NO_PRIORETY,
	PRIORETY_LOW,
	PRIORETY_MED,
	PRIORETY_HIGH
} Priorety;

#endif // UTILS_H	
