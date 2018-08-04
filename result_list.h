/*****************************************************************************/
/* Mikko Majamaa */
/*****************/
/* struct result holds info of the result of analyze described in detail below*/

#ifndef result_list
#define result_list

#include "name_list.h"

typedef struct result {
	char ds_name[30]; //name of the data set
	long qty_names; //quantity of names in the data set
	int shortest_length; //length of the shortest name in the data set
	int longest_length; //length of the longest name in the data set
	int avg_length; //average length of name in the data set
	int memory_tot; //total memory allocated for the data set
	int memory_used; //total memory in useful purpose of the allocated memory in percents
		struct result *pN; //pointer to the next data set
} Result;

Result *Analyze(Name *pA_n, Result *pA_t);

/*In Empty_result_list -function parameter n == 0 if it's called from the menu by option the 0 (exit) and n == 1 when by the option 6 (empty resultlist).*/
Result *Empty_result_list(Result *pA, int n);

/*In Print_result_list -funtion n == 1 means printing to terminal and n == 2 printing to a file*/
void Print_result_list(Result *pA, int n);

#endif

/*****************************************************************************/
/* eof */
