#define MAX_FIELD 128+1
#define MAX_CHAR 512+1
#define TOTAL_FIELDS 11
#include <stdio.h>

/* Struct Prototypes */
/*****************************************************************************/
typedef struct {
    char *year;
	char *block_id;
	char *property_id;
	char *base_property_id;
	char *clue_small_area;
	char *trading_name;
	char *industry_code;
	char *industry_description;
	char *x_coord;
	char *y_coord;
	char *location;
} grid_cell_t;
typedef grid_cell_t data_t;

/*****************************************************************************/
typedef struct node node_t;
struct node {
    data_t *data;
    node_t *next;
};
/*****************************************************************************/
typedef struct {
    node_t *head;
    node_t *foot;
} list_t;

/*****************************************************************************/

/* Function Prototypes */
list_t *make_empty_list(void);
list_t *insert_at_foot(list_t *list, data_t *value);
list_t *parse_string(list_t *list, FILE *fp, FILE *out_file);
void free_list(list_t *list);
void search_key(list_t *list, char *key, FILE *out_file);







