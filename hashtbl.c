#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtbl.h"
#include "vector.h"


table_entry_t hash_table[HASH_TABLE_SIZE];

// hash functions start here


/*a naive textbook hash function, can't remember where I read it, 
 * but it followed with 'and now real hash functions...'
 * can be used in haste w/o internet access */
unsigned long textb_hash_func(unsigned char *word, int word_len)
{
	unsigned long ret_val=0;
	
	for(int i=0; i<word_len; i++)
	{
		ret_val+= (word[i] * (i+1));
	}
	return ret_val;
}


// first hash function that can be easily grabbed on the net
// hash function from http://www.cse.yorku.ca/~oz/hash.html
//djb2, modified for dummy use of word_len
unsigned long djb2(unsigned char *str, int str_len)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}



//insert your hash functions before this line

//#define HASH_FUNC(word, word_len) textb_hash_func(word, word_len)
#define HASH_FUNC(word, word_len) djb2(word, word_len)

inline static node_t * create_new_node(char *word, int word_len)
{
	node_t *retval = calloc(1, sizeof(node_t));
	retval->word = calloc(1, word_len+1);
	strncpy(retval->word, word, word_len);
	retval->word_len = word_len;
	retval->freq_counter = 1;
	return retval;
}


int add_to_hash_table(char *word, int word_len)
{
//uncomment this if you are testing good hashfuncs for speed, and don't forget
//to change by comment-uncomment HASH_TABLE_SIZE to 0x10000
//	unsigned int hash_val = 0xFFFF & HASH_FUNC((unsigned char *)word, word_len);
//uncommet this if you are testing more primitive hashfuncs, this will significantly
//lessen collisions, don't forget to change HASH_TABLE_SIZE to a prime number
	unsigned int hash_val = (HASH_FUNC((unsigned char*)word, word_len)) % HASH_TABLE_SIZE;
	if(!hash_table[hash_val].entries)
	{
		assert(!hash_table[hash_val].list_head);
		hash_table[hash_val].entries++;
//		printf("adding a new word %s with a value %hX to the top\n", word, hash_val); 
		hash_table[hash_val].list_head = create_new_node(word, word_len);
		return 1;
	}
	//if at least one hash_table[hash_val] already exists, start searching for exact match
	node_t *cur_node = hash_table[hash_val].list_head;
	node_t *prev_node = cur_node;
	while(cur_node)
	{
		if(strcmp(word, cur_node->word))//just a collision 
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
		}
		else//found it!
		{
//			printf("found another use of word %s \n", word);
			cur_node->freq_counter++;
			return 0;
		}
	}
	//not found anything, cur_node is a NULL pointer, prev_node->next is NULL, it is the tail node
	hash_table[hash_val].entries++;
//	printf("adding a collision word %s with a value %hX\n", word, hash_val);
	cur_node = create_new_node(word, word_len);
	prev_node->next = cur_node;
	return 1;
}

void print_hash_table_stat(void) 
{

	int i=0;
	int used_entries=0;
	long int total_collisions=0;
	long int local_collisions=0;
	long int max_collisions=0;
	node_t *node_ptr=NULL;
	
	init_vector();
	
	printf("Hash table stats:\n\n");
	for(i=0; i<HASH_TABLE_SIZE; ++i)
	{//we can join the nodes into a single list to sort with list sort algos, or just sort an array of ptrs to them
		if(hash_table[i].entries)
		{
		 	local_collisions = hash_table[i].entries - 1;
			//uncomment to get a verbose bucket report
			//printf("Bucket %X\t\tcollisions = %ld\n", i, local_collisions);
			used_entries++;
			total_collisions += local_collisions;
			if(local_collisions > max_collisions)
				max_collisions = local_collisions;
			//here we transfer the ownership of all the allocated data to the array
			node_ptr = hash_table[i].list_head;
			do
			{
				add_nodeptr_to_array(node_ptr);
				node_ptr = node_ptr->next;
			} while(node_ptr);
		}
	}//!!! NOTE: is hash_table still valid after that? seems so, but another array implementation could change that!
	printf("\n\nTotal hash table usage: Total buckets =%d, used buckets = %d, total collisions = %ld, maximal collisions = %ld\n", 
			HASH_TABLE_SIZE, used_entries, total_collisions, max_collisions);
	
	comp_fun_ptr_t comp_fun=compare_nodeptrs;
	qsort(vector.data, vector.size, sizeof(node_t*), comp_fun);
	print_sorted_array();
	cleanup_data();
}
