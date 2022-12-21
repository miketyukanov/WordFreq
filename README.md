# WordFreq -- an exercise and a test.

This program accepts text (plain ASCII) text from console or file and counts
total words, unique words and the quantity of each word's usage. Since  many 
similar programs with similar limitations exist on the net, I've added some 
hash function stats and designed the program in a way that could be useful
to someone testing and comparing hash functions. 

Initially it's an exercise from VT's programming course. The design is simple 
and suboptimal, made for programming speed and ease. 

Input is read character-by-character, every contiguous sequence of characters 
within A-Z and a-z ranges is a word, everything else is skipped. Words are 
stored in a simple hash table. To display the results in a nice sorted way the
pointers to them are copied to a growable array, where they can be sorted by 
qsort. The freeing of data is also made through this array. 

The actual hash function is called via a macro `HASH_FUNC`.
If you want to test your hash function, feel free to add it into hashtabl.c
(preferrably after other hash functions and before the macro) and change the
current definition such as 
`#define HASH_FUNC(word, word_len) naive_hash_func(word, word_len)`
to something like  
`#define HASH_FUNC(word, word_len) my_experimental_hash_func(word, word_len)`

To get a bucket-by-bucket usage stats, uncomment 
`printf("Bucket %X\t\tcollisions = %ld\n", i, local_collisions);` in 
*print_hash_table_stat* found in hashtbl.c

TODO:
1. Clean up superfluous struct variables such as "entries" (it is misnamed, 
too), make consistent spacing between operands and operators, comment the text
more, making comments student-friendly. 

2. Comb the web for better hash functions, think up a func of my own,
comparable enough to the established ones while memorizeable enough to 
reproduce it in an interview-like haste.

3. Test it more thouroughly. It seems to work, but it's better to prove it. 
