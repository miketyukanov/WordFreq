#ifndef HASHTBL_H
#define HASHTBL_H

#define MAX_WORD_LEN 200 //the longest English dictionary word is 45

//HASH_TABLE_SIZE: if you are testing sophisticated hash functions, 
//define HASH_TABLE_SIZE as a power of 2 and use masking such as
// hval=(HASH_TABLE_SIZE-1)&HASH_FUNC() to obtain a short index hash value -- 
// hashing speed-optimized
//#define HASH_TABLE_SIZE 0x10000
//
//if you are testing rather primitive hash functions, define HASH_TABLE_SIZE
//as a prime number and obtain the actual value as a modulo:
//hval=HASH_FUNC%HASH_TABLE_SIZE
//65537, while a prime, is too close to a 0x10000
//it's fun to compare them different
//#define HASH_TABLE_SIZE 65537
//#define HASH_TABLE_SIZE 71993
#define HASH_TABLE_SIZE 65521
//there is no difference for the primitive textbook addition-based func
//since it never reaches even 0x10000.
//for djb2 the results are slightly better with 71993


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
