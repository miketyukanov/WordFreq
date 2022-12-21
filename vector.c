#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtbl.h"
#include "vector.h"


#define INIT_VECTOR_SIZE 5000

entries_vector_t vector={INIT_VECTOR_SIZE,0,NULL};

//since this vector is a singleton, its functions don't need
//a pointer to it.

void init_vector(void) 
{
	vector.data=calloc(sizeof(node_t*), INIT_VECTOR_SIZE);
}


void add_nodeptr_to_array(node_t *node)
{
	vector.data[vector.size++] = node; 
	if(vector.size>=vector.capacity)
	{
		size_t new_capacity = vector.capacity*2;
		printf("\nabout to realloc array to capacity %zd\n", new_capacity); 
		vector.data=reallocarray(vector.data, sizeof(node_t*), new_capacity);
		if(!vector.data)//here it can actually fail
		{
			fprintf(stderr, "reallocarray failed to resize:\n %m \n");
			exit(11);
		}
		vector.capacity = new_capacity;
	}
}

int compare_nodeptrs(const void *a, const void *b)
{
	const node_t *a_ptr=*((const node_t **)a); 
	const node_t *b_ptr=*((const node_t **)b); 
	
	if(a_ptr->freq_counter<b_ptr->freq_counter)
		return -1;
	if(a_ptr->freq_counter>b_ptr->freq_counter)
		return 1;
	return strcmp(a_ptr->word, b_ptr->word);
}


void print_sorted_array(void)
{
	size_t i=0;
	printf("\n\nFrequency\tWord\n\n");
	for(i = 0; i<vector.size; ++i)
	{
		printf("%ld\t\t%s\n", vector.data[i]->freq_counter, vector.data[i]->word);
	}
}


void cleanup_data(void)
{
	size_t i=0;
	for(i=0; i<vector.size; ++i)
	{
		free(vector.data[i]->word);
		free(vector.data[i]);
	}
	free(vector.data);
}

