/*****************************************************************************/
/* Mikko Majamaa */
/*****************/
/* this file contains the code related to results of analyzations */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "result_list.h"
#include "name_list.h"


void Print_result_list(Result *pA, int n) {
	Result *ptr;
	FILE *file;
	if (pA == NULL) { //empty resultlist
		printf("Tuloslista on tyhjä.\n");
		return;
	}

	//print the headline
	if (n == 1) { //print to terminal
		printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	} else if (n == 2) { //print to file
		char file_name[30];
		printf("Anna tallennettavan tulostiedoston nimi: ");
		scanf("%s", file_name);
		if ((file = fopen(file_name, "w")) == NULL) {
			printf("Tiedostoa ei saatu avattua.\n");
			return;
		}
		fprintf(file, "Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	} 
	//

	ptr = pA;
	while (ptr != NULL) {
		if (n == 1) { //print to terminal
			printf("%9s %5ld %6d %6d %2d %dkB / %d%%\n", ptr->ds_name, ptr->qty_names, ptr->shortest_length, ptr->longest_length, ptr->avg_length, ptr->memory_tot, ptr->memory_used);		
		} else if (n == 2) { //print to file
			fprintf(file, "%9s %5ld %6d %6d %2d %dkB / %d%%\n", ptr->ds_name, ptr->qty_names, ptr->shortest_length, ptr->longest_length, ptr->avg_length, ptr->memory_tot, ptr->memory_used);		
		
		}
		ptr = ptr->pN;
	}

	
	if (n == 2) { //print to file
		printf("Tiedosto tallennettu.\n");
		fclose(file);
	}		


	return;
}

Result *Analyze(Name *pA_n, Result *pA_r) {
	if (pA_n == NULL) { //namelist is empty
		printf("Nimilista on tyhjä.\n");
		return NULL;
	}

	int qty, min_length, max_length, char_qty, length; //qty is the total quantity of names and qtyChars is the total quantity of characters in all of the names
	double memory_tot, memory_used;
	qty = max_length = char_qty = memory_tot = memory_used = 0;
	min_length = 30;
	Name *ptr;
	Result *new, *ptr_result;

	if ((new = (Result*)malloc(sizeof(Result))) == NULL) { //allocate memory for the result
		perror("Muistia ei saatu varattua. Lopetetaan. \n");
		exit(0);
	}
	
	printf("Anna analysoitavalle datasetille nimi: ");
	scanf("%s", new->ds_name);
	printf("Analysoidaan listassa olevat tiedot.\n");

	ptr = pA_n;
	while (ptr != NULL) { //go through the namelist
		qty += 1;
		memory_tot += sizeof(Name);
		length = strlen(ptr->name);
		memory_used += sizeof(Name) - (29 * sizeof(char) - (length *sizeof(char))); //how much memory of allocated is not in useful purpose
		char_qty += length;
		if (length < min_length) {
			min_length = length;
		}
		if (length > max_length) {
			max_length = length;
		}
		ptr = ptr->pN;
	}

	new->qty_names = qty;
	new->shortest_length = min_length;
	new->longest_length = max_length;
	new->avg_length = char_qty / qty;
	new->pN = NULL;
	new->memory_tot = memory_tot/1000;
	

	new->memory_used = round((memory_used / memory_tot) * 100);

	Print_result_list(new, 1);

	if (pA_r == NULL) { //tuloslista oli tyhjä
		return (pA_r = new);
	} else {
		ptr_result = pA_r; //etsitään listan loppu
		while (ptr_result->pN != NULL) {
			ptr_result = ptr_result->pN;
		}
		ptr_result->pN = new;
		return pA_r;
	}
}

Result *Empty_result_list(Result *pA, int n) {
	Result *ptr;
	if ((pA == NULL) && (n != 0)) { //tuloslista on jo tyhjä
		printf("Tuloslista on jo tyhjä.\n");
		return pA;
	} else {
		ptr = pA;
		while (pA != NULL) { //käydään läpi koko lista
			pA = pA->pN;
			free(ptr); //vapautetaan muisti
			ptr = pA;
		}
		if (n != 0) {
			printf("Tuloslista tyhjennetty.\n");
		}		
		return NULL;
	}
}

/*****************************************************************************/
/* eof */