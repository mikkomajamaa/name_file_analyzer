/*****************************************************************************/
/* Mikko Majamaa */
/*****************/
/* struct name holds info on each unique name and quantity of them */

#ifndef name_list
#define name_list

typedef struct name {
	char name[30];
	long qty; //quantity of unique names
	struct name *pN; //pointer to next name
} Name;

Name *Empty_name_list(Name *pA);
Name *Read_name_file(Name *pA);
void Print_name_list(Name *pA);

#endif

/*****************************************************************************/
/* eof */
