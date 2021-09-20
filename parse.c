/* parse.c
*
* Create by Yan-Ting Justin Chen (yantingjc@student.unimelb.edu.au) on 28th August 2020.
* This has the operations that are required to read->format->insert into linked list-> take input -> search key in dict
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "func.h"


/*******************************************************************************************************/
/* This function takes the key and iterates through the entire list comparing whether
   the key matches with any entries in the dictionary, if a match occurs the function 
   will print out the relavent information in the format required.*/
void
search_key(list_t *list, char *key, FILE *out_file){

	node_t *curr_node; 
	int i = 0;
	int len;
	len = strlen(key);
	
	/* This replaces the new line that fgets picks up when I read in the key*/
	for(i=0; i<len; i++){
		if(key[i] == '\n'){
			key[i] = '\0';
			len--;
		}
	}
	curr_node = list->head;
	int found = 0;
	while(curr_node!=NULL){
	/* Print the name first and then put it in the same format as the example */
		if(strcmp(key, curr_node->data->trading_name) == 0){
			fprintf(out_file, "%s -->", curr_node->data->trading_name); 
			fprintf(out_file, " Census year: %s ||", curr_node->data->year);
			fprintf(out_file, " Block ID: %s ||", curr_node->data->block_id);
			fprintf(out_file, " Property ID: %s ||", curr_node->data->property_id);
			fprintf(out_file, " Base property ID: %s ||", curr_node->data->base_property_id);
			fprintf(out_file, " CLUE small area: %s ||", curr_node->data->clue_small_area);
			fprintf(out_file, " Industry (ANZSIC4) code: %s ||", curr_node->data->industry_code);
			fprintf(out_file, " Industry (ANZSIC4) description: %s ||", curr_node->data->industry_description);
			fprintf(out_file, " x coordinate: %s ||", curr_node->data->x_coord);
			fprintf(out_file, " y coordinate: %s ||", curr_node->data->y_coord);
			fprintf(out_file, " Location: %s || \n", curr_node->data->location);
			/* Print the node */
			found = 1;
		}
		curr_node = curr_node->next;
	}
	/* This checks keys one at a time, if the key isn't found in the file return NOTFOUND */
	if(found == 0){
			fprintf(out_file, "NOTFOUND\n");
		}
}

/*******************************************************************************************************/
/* This function extracts information from the file fp, then reformats the string so that it can be
   put into the correct nodes then inserted into a linked list. It also calls the search_key function
   in func.c that compares if the key is in the dictionary and if it does print out the corresponding 
   information and then free the variables necessary.*/
   
list_t *
parse_string(list_t *info_list, FILE *fp, FILE *out_file){
	
	int temp_len;
    char temp[MAX_CHAR];
	char processed[MAX_CHAR]; 
	data_t *curr;
	
	/*Consume the first line */
	fgets(temp, MAX_CHAR, fp);
	
	
    while(fgets(temp, MAX_CHAR, fp)){
		curr = (data_t *)calloc(1, sizeof(data_t));
		assert(curr!=NULL);
        int i, j;
        int is_quote=0;
        temp_len = strlen(temp);
        char x;
		
		/*Removes carriage returns and new lines at the end of the file*/
		if(temp[temp_len-2] == '\r'){
			temp[temp_len-2] = '\0';
		}
		else if(temp[temp_len-1] == '\n'){
			temp[temp_len-1] = '\0';
		}
		
		/*Reads the data into a temporary array and then formats it*/
        for(i=0; temp[i]!= '\0'; i++){
            int quote_changed = 0;
            x = temp[i]; 
            if(temp[i] == '"' && is_quote==1 && quote_changed == 0){
                is_quote = 0;
                quote_changed = 1;
            }
            if(temp[i] == '"' && is_quote==0 && quote_changed == 0){
                is_quote = 1;
                quote_changed = 1;
            }
            
            if(x == '"' && temp[i] =='"'){
                for(j=i; j<temp_len; j++){
                    temp[j] = temp[j+1];
                }
            }
            
            if(temp[i] == ',' && is_quote==0){
                temp[i] = '\n';
            }
        }

		
		/*Copies the formatted array into a temporary buffer*/
		for(i=0; i<temp_len; i++){
			processed[i] = temp[i];
		}
		
		/*Puts all of the data into the data_t type and then insert it into the list 
		  Doing all of this as it is being read line by line to ensure consistentcy*/
		
		/* Calloc all 11 */
		curr->year = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->year != NULL);
		
		curr->block_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->block_id != NULL);
		
		curr->property_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->property_id !=NULL);
		
		curr->base_property_id = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->base_property_id !=NULL);
		
		curr->clue_small_area = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->clue_small_area != NULL);
		
		curr->trading_name = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->trading_name != NULL);
		
		curr->industry_code = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->industry_code != NULL);
		
		curr->industry_description = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->industry_description != NULL);
		
		curr->x_coord = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->x_coord != NULL);
		
		curr->y_coord = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->y_coord != NULL);
		
		curr->location = (char *)calloc(MAX_FIELD, sizeof(char));
		assert(curr->location != NULL);
		
		int z = 0;
		i = 0;
		/*Read into the respective arrays then realloc with a +1 because we need the nullbyte at the end to do the comparison*/
		while(processed[i] != '\n'){
			curr->year[z] = processed[i];
			i++;
			z++;
		} 
		curr->year = (char *)realloc(curr->year, strlen(curr->year)+1);
		assert(curr->year != NULL);
		i++;
		z=0;	
		/*Need to iterate i to skip over the new line that let it exit the first loop, then reset z.
		  The reason why we are checking for new line is because I put a new line in the processed 
		  buffer every single time I had to remove a comma. This way we split the attributes up correctly.*/

		while(processed[i] != '\n'){
			curr->block_id[z] = processed[i];
			i++;
			z++;
		} 
		curr->block_id = (char *)realloc(curr->block_id, strlen(curr->block_id)+1);
		assert(curr->block_id != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->property_id[z] = processed[i];
			i++;
			z++;
		} 
		curr->property_id = (char *)realloc(curr->property_id, strlen(curr->property_id)+1);
		assert(curr->property_id !=NULL);
		i++;
		z=0;

		while(processed[i] != '\n'){
			curr->base_property_id[z] = processed[i];
			i++;
			z++;
		}
		curr->base_property_id = (char *)realloc(curr->base_property_id, strlen(curr->base_property_id)+1);
		assert(curr->base_property_id !=NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->clue_small_area[z] = processed[i];
			i++;
			z++;
		} 
		curr->clue_small_area = (char *)realloc(curr->clue_small_area, strlen(curr->clue_small_area)+1);
		assert(curr->clue_small_area != NULL);
		i++;
		z=0;
		while(processed[i] != '\n'){
			curr->trading_name[z] = processed[i];
			i++;
			z++;
		} 
		curr->trading_name = (char *)realloc(curr->trading_name, strlen(curr->trading_name)+1);
		assert(curr->trading_name != NULL);
		i++;
		z=0;
		while(processed[i] != '\n'){
			curr->industry_code[z] = processed[i];
			i++;
			z++;
		} 
		curr->industry_code = (char *)realloc(curr->industry_code, strlen(curr->industry_code)+1);
		assert(curr->industry_code != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->industry_description[z] = processed[i];
			i++;
			z++;
		} 
		curr->industry_description = (char *)realloc(curr->industry_description, strlen(curr->industry_description)+1);
		assert(curr->industry_description != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->x_coord[z] = processed[i];
			i++;
			z++;
		} 
		curr->x_coord = (char *)realloc(curr->x_coord, strlen(curr->x_coord)+1);
		assert(curr->x_coord != NULL);
		i++;
		z=0;
		
		while(processed[i] != '\n'){
			curr->y_coord[z] = processed[i];
			i++;
			z++;
		}
		curr->y_coord = (char *)realloc(curr->y_coord, strlen(curr->y_coord)+1);
		assert(curr->y_coord != NULL);
		i++;
		z=0;
		while(processed[i] != '\0'){
			curr->location[z] = processed[i];
			i++;
			z++;
		} 
		curr->location = (char *)realloc(curr->location, strlen(curr->location)+1);
		assert(curr->location != NULL);
		
		/* After the insertion of the data into the respective arrays inside the data_t structure,
		   plug it into the insert at foot function which will create a new node and insert the data in.*/
		insert_at_foot(info_list, curr);
	}
	/* This calls the search_key function which utilizes strcmp between the key and the current nodes trading_name array*/
	char key[MAX_CHAR];
	while(fgets(key, MAX_CHAR, stdin)){
		search_key(info_list, key, out_file);
	}
	free_list(info_list);
	
	return info_list;
}

