#include <stdio.h>
#include <stdlib.h>
#include "unhuff.h"
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
	clock_t begin = clock();

	if(argc != 2) {
	printf("Not enough arguments");
	return EXIT_FAILURE;
	}
	FILE * inFile = fopen(argv[1], "r");
	if (inFile == NULL) {
		fprintf(stderr, "can't open the input file.  Quit.\n");
		return EXIT_FAILURE;
	}
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	unsigned char temp3 = 0;
	unsigned char * whichbit = &temp1;
	unsigned char * curbyte = &temp2;
	unsigned char * bit = &temp3;
	TreeNode * namu = NULL;
	namu = readHeader(namu, inFile, bit, whichbit, curbyte);
	//IGNORE SPARE BITS
	while( (*whichbit) != 0)
	{
		readBit(inFile, bit, whichbit, curbyte);
	}
	//READ CONTENTS
	char * name = argv[1];
	char * ext = ".unhuff";
	strcat(name, ext);
	FILE * unhuffFile = fopen(name, "w");
	if (unhuffFile == NULL) {
		fprintf(stderr, "can't open the unhuff File.  Quit.\n");
		return EXIT_FAILURE;
	}	
	readContents(inFile, unhuffFile, namu, bit, whichbit, curbyte);

	freeTree(namu);
	fclose(inFile);
	fclose(unhuffFile);
	
	clock_t end = clock();
	printf("It took %f seconds for the decompression\n", (float) (end - begin) / (CLOCKS_PER_SEC) );

	return EXIT_SUCCESS;
}
