#ifndef VECTOR_H
#define VECTOR_H

//vector used for sorting the results by frequency and alphabet
//resizeable


typedef struct entries_vector_s
{
	size_t capacity;
	size_t size;
	node_t ** data;
} entries_vector_t;

#define INIT_VECTOR_SIZE 5000

//since this vector is a singleton, its functions don't need
//a pointer to it.

//the actual vector
extern entries_vector_t vector;

//kinda constructor
void init_vector(void); 

//adding with doubling resize if needed
void add_nodeptr_to_array(node_t *node);

//qsort-compatible comparison
int compare_nodeptrs(const void *a, const void *b);

//I can't trust myself to use function pointers correctly w/o typedef
typedef int (*comp_fun_ptr_t)(const void *a, const void *b);

//just that, printing the results. If performance were an issue, we could 
//cleanup here, but a separate destructor is safer
void print_sorted_array(void);

//here we cleanup the contents, too, since vector took ownership from 
//hashtable
void cleanup_data(void);

#endif //VECTOR_H
