#ifndef HASHTBL_H
#define HASHTBL_H

#define MAX_WORD_LEN 200 //the longest English dictionary word is 45
#define HASH_TABLE_SIZE 0x10000

typedef struct node_s node_t;
struct node_s
{
	node_t *next;
	char *word;
	unsigned long freq_counter;
	int word_len;
};


//now it's useless, since , which 
typedef struct table_entry_s table_entry_t;
struct table_entry_s
{
	unsigned long entries;
	node_t *list_head;
};


extern table_entry_t hash_table[HASH_TABLE_SIZE];

//returns number of new entries, 0 for found, 1 for a collision or a new word
int add_to_hash_table(char *word, int word_len);

void print_hash_table_stat(void);

#endif //HASHTBL_H
