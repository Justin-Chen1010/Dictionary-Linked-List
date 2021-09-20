/* Ass1.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 28th August 2020.
* This is the main function that includes the header file linking to my 2 other function files.
*
* To run the program type:
* ./dict results/temp_input results/temp_results < results/temp_stdin
* Made up of 4 files including this one
* -- Ass1.c The main file that refers to the headerfile that refers to the two function files
* -- func.c includes the operations that are required to create a list, insert in list and free the list.
* -- parse.c includes the operations that are required to read->format->insert into linked list-> take input -> search key in dict
* -- func.h includes all the function prototypes as well as struct prototypes
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main (int argc, char **argv){

	list_t *info_list;
	info_list = make_empty_list();
	FILE *out_file = fopen(argv[2], "a");
    FILE *fp = fopen (argv[1] , "r");
    if (fp == NULL){
        printf("File not found");
        return 0;
    }
	
	info_list = parse_string(info_list, fp, out_file);	
	fclose(fp);
	fclose(out_file);
	return 0;
}
