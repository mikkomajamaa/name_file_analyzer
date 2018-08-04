/*****************************************************************************/
/* Mikko Majamaa */
/*****************/
/* read and analyze name files provided by Finland's Population Register Centre */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name_list.h"
#include "result_list.h"

int Menu(void);

int main(void) {
	Name *p_beginning_names = NULL;
	Result *p_beginning_results = NULL;
	printf("Tämä ohjelma tutkii nimitietoja sisältäviä tiedostoja.\n");
	do {
		switch (Menu()) {
			case 1:
				p_beginning_names = Read_name_file(p_beginning_names);
				break;
			case 2:
				Print_name_list(p_beginning_names);
				break;
			case 3:
				p_beginning_results = Analyze(p_beginning_names, p_beginning_results);
				break;
			case 4:
				Print_result_list(p_beginning_results, 1);
				break;
			case 5:
				Print_result_list(p_beginning_results, 2);
				break;
			case 6:
				p_beginning_results = Empty_result_list(p_beginning_results, 1);
				break;
			case 0:
				Empty_name_list(p_beginning_names);
				Empty_result_list(p_beginning_results, 0);
				printf("Kiitos ohjelman käytöstä.\n");
				exit(0);
				break;
			default:
				printf("Virheellinen valinta.\n");
				break;
		}
	} while (1 == 1);

	return 0;
}

int Menu(void) {
	int i;
	printf("1) Lue nimitiedosto\n");
	printf("2) Tulosta listassa olevat tiedot\n");
	printf("3) Analysoi tiedot\n");
	printf("4) Tulosta kaikki tulostiedot\n");
	printf("5) Tallenna kaikki tulostiedot tiedostoon\n");
	printf("6) Tyhjennä tuloslista\n");
	printf("0) Lopeta\n");
	printf("Anna valintasi: ");
	scanf("%d", &i);
	return i;
}

/*****************************************************************************/
/* eof */