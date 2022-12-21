CC=gcc
CCFLAGS=-Wall
CLEAN=rm -f
PROGRAM_NAME=wordfreq
OBJECT_FILES=*.o
SOURCE_FILES=main.c extract.c vector.c hashtbl.c

$(PROGRAM_NAME) : $(OBJECT_FILES)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJECT_FILES) : $(SOURCE_FILES)
	$(CC) $(CCFLAGS) -c $^

clean: 
	$(CLEAN) $(PROGRAM_NAME) *.o
