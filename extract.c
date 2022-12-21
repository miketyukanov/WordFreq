#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "extract.h"
#include "hashtbl.h"

void extract(FILE *src_file)
{
	int unique_words=0;
	int total_words=0;
	
	int word_len=0;
	char buf[MAX_WORD_LEN];
	int in_word=0;
	int c=0;
	while((c = fgetc(src_file))!=EOF)
	{
		if(isalpha(c))
		{
			if(!in_word)//starting a new word 
			{
				in_word = 1;
				word_len=0;
			}
			buf[word_len++] = tolower(c);
			if(word_len>=MAX_WORD_LEN)
			{
				fprintf(stderr, "The word %s is too long, probably the input is not an ASCII text\n", buf);
				exit(10);
			}

		} else
		{
			if(in_word) //there was a word, and it is finished 
			{
				in_word=0;
				total_words++;
				buf[word_len]=0;
				unique_words+= add_to_hash_table(buf, word_len);
			}//otherwise  we just continue reading
		}
		
		
	}	
	printf("Total words: %d\nUnique words: %d\n\n", total_words, unique_words);

	print_hash_table_stat();


}
