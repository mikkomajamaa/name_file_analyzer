/*****************************************************************************/
/* Mikko Majamaa */
/*****************/
/* this file contains the code related to reading and handling the data of the name files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name_list.h"
#define LEN 80

Name *Empty_name_list(Name *pA) { 
	Name *ptr;
	ptr = pA;
	while (pA != NULL) {
		pA = pA->pN;
		free(ptr);
		ptr = pA;
	}
	return NULL;
}

void Print_name_list(Name *pA) {
	Name *ptr;
	if (pA == NULL) { //empty namelist
		printf("Nimilista on tyhjä.\n");
		return;
	} else {
		ptr = pA;
		while (ptr != NULL) {
			printf("%s %ld\n", ptr->name, ptr->qty);	
			ptr = ptr->pN;
		}
		return;
	}
}

Name *Read_name_file(Name *pA) {
	Name *ptr_new, *ptr;
	FILE *file;
	char file_name[LEN];
	char line[LEN];
	char *p1 = NULL, *p2 = NULL; //pointers for first and second columns
	char qty_names_str[LEN];	
	int qty_lines = 0;
	printf("Anna luettavan tiedoston nimi: ");
	scanf("%s", file_name);
	
	if (pA != NULL) { //namelist is not empty
		printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
		pA = Empty_name_list(pA);
	}
	
	printf("Luetaan tiedosto %s.\n", file_name);
	fflush(stdin);

	if ((file = fopen(file_name, "r")) == NULL) { //open file
		perror("Tiedoston avaaminen epäonnistui");
		return NULL;
	}
	
	fgets(line, LEN, file); //remove the first line (header line)
	fflush(stdin);

	while (fgets(line, LEN, file) != NULL) {
		qty_lines += 1;				

		if ((ptr_new = (Name*)malloc(sizeof(Name))) == NULL) { //allocate memory
			perror("Muistin varaus epäonnistui.\n");
		}

		p1 = strtok(line, ";");
		p2 = strtok(NULL, "\n");
		
		strcpy(ptr_new->name, p1);
		strcpy(qty_names_str, p2);
		ptr_new->qty = atoi(qty_names_str);
		
		if (pA == NULL) { //empty list
			pA = ptr_new;
			ptr = ptr_new;
		} else {
			ptr->pN = ptr_new; //add node to the end of the list
			ptr = ptr_new;
		}

	}

	fclose(file);
	printf("Tiedosto %s luettu, %d nimiriviä.\n", file_name, qty_lines);
	return pA;
}

/*****************************************************************************/
/* eof */