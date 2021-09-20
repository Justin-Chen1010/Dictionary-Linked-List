/* func.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 28th August 2020.
* This has the basic list operations that are needed to create a linked list and free it.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "func.h"


/***************************************************************************************/
/* This function is provided by Alistar Moffat from taken from listops.c
   it makes an empty list. It is modified with calloc for the purpose of this assignment.
   Link to listops.c: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */
list_t
*make_empty_list(void) {
    list_t *list;
    list = (list_t*)calloc(1, sizeof(list_t));
    assert(list!=NULL);
	list->head = list->foot = NULL;
    return list;
}


/***************************************************************************************/

void free_data(data_t *curr){
		free(curr->year);		
		free(curr->block_id);		
		free(curr->property_id);		
		free(curr->base_property_id);		
		free(curr->clue_small_area);		
		free(curr->trading_name);		
		free(curr->industry_code);
		free(curr->industry_description);
		free(curr->x_coord);
		free(curr->y_coord);
		free(curr->location);
		free(curr);
}


/***************************************************************************************/
/* This function is provided by the Alistair Moffat taken from listops.c it 
   loops through and frees the calloc'd list, it is modified to free the nodes 
   specific categories for the purpose of this assignment 
   link to listops.c: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */

void
free_list(list_t *list) {
    node_t *curr, *prev;
    assert(list!=NULL);
    curr = list->head;
    while (curr) {
        prev = curr;
        curr = curr->next;
		free_data(prev->data);
        free(prev);
    }
    free(list);
}


/***************************************************************************************/
/* This function is provided by Alistair Moffat taken from listops.c
   This is the only function we need to insert data_t values into a node 
   into the list. It is modifed to meet the needs of the assignment
   Link: https://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/listops.c */
list_t
*insert_at_foot(list_t *list, data_t *value) {
    node_t *new;
    new = (node_t*)calloc(1, sizeof(node_t));
    assert(new!=NULL);
    new->data = value;
    if (list->foot==NULL) {
        /* this is the first insertion into the list */
        list->head = list->foot = new;
    } else {
        list->foot->next = new;
        list->foot = new;
    }
    return list;
}
/***************************************************************************************/


