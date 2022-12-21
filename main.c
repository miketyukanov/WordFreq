#include "stdio.h"
#include "extract.h"

void print_usage(void)
{
	fprintf(stderr, "usage:\n WordFreq w/o parameters for stdin or redirected input;\
				\n WordFreq filename to count words in a txt file\n\n");
}

int main(int argc, char**argv)
{
	FILE *src_file=NULL;
	if(argc>2)
	{
		fprintf(stderr,"Too many arguments\n\n");
		print_usage();
		return 1;
	}
	if(argc==2)
	{
		if(!(src_file = fopen(argv[1],"r")))
		{
			fprintf(stderr, "Couldn't open file %s:\n %m\n", argv[1]);
			return 2;
		}
		 

	}
	else //argc=1, i.e., no arguments
	{
	src_file = stdin;
	}	 
	extract(src_file);
	if(argc==2) 
		fclose(src_file);
	return 0;
}
