#include <stdio.h>
#include <stdlib.h>
#include "huff.h"
#include <string.h>
#include <time.h>

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
	long *asciiCount = (long *)malloc(sizeof(long)* ASCII_SIZE);
	if (asciiCount == NULL) {
		return NULL;
	}
	int ch;
	for (ch = 0; ch < ASCII_SIZE; ch++) {
		asciiCount[ch] = 0;
	}
	fseek(fp, 0, SEEK_SET);
	while ((ch = fgetc(fp)) != EOF) {
		asciiCount[ch] += 1;
	}
	//ADDING EOF
	asciiCount[0] = 1;
	
	return asciiCount;
}

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

	/* read and count the occurrences of characters */
	long *asciiCount = countLetters(inFile);
	fseek(inFile, 0, SEEK_SET);
	if (asciiCount == NULL) {
		fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");
		return EXIT_FAILURE;
	} 
	
	ListNode * head = NULL;
	
	///////////////////_sorted//////////////////////////////////
	/*FILE * sortedFile = fopen(argv[2], "w");
	if (sortedFile == NULL) {
		fprintf(stderr, "can't open the sorted file.  Quit.\n");
		return EXIT_FAILURE;
	}*/
	////////////////////sorted linked list//////////////////////
	int i = 0;
	for(i = 0; i < ASCII_SIZE; i++)
	{
		if(asciiCount[i] != 0)
		{
			head = addNode(head,i,asciiCount[i]);
		}
	}
	//ListNode * curnode = head;
	/*while(curnode != NULL)
	{
		//fprintf(sortedFile,"%c:%ld\n",curnode->ptr->label,curnode->ptr->count);
		curnode = curnode->next;
	}*/
	////////////////////////////////////////////////////////////
	
	//////////////////Create Huffman Tree///////////////////////
	ListNode * namu = buildTree(head);
	///////////////////_huffman/////////////////////////////////
	//FILE * huffmanFile = fopen(argv[3], "w");
	//if (huffmanFile == NULL) {
	//	fprintf(stderr, "can't open the huffman file.  Quit.\n");
	//	return EXIT_FAILURE;
	//}
	char * huff = malloc(sizeof(char) * 10000000);
	int * index = malloc(sizeof(int));
	index[0] = 0;
	//MAKE A TABLE
	int ** table;
	table = malloc(sizeof(int *) * ASCII_SIZE);
	for(i = 0; i < ASCII_SIZE; i++){
		table[i] = malloc(sizeof(int) * 10000);
	}	
	printTree(namu->ptr, huff, index, table);
	free(huff);
	free(index);
	////////////////////////////////////////////////////////////
	char * name = argv[1];
	char * ext = ".huff";
	strcat(name, ext);
	//////////////////_header///////////////////////////////////
	FILE * headerFile = fopen(name, "w");
	if (headerFile == NULL) {
		fprintf(stderr, "can't open the header file.  Quit.\n");
		return EXIT_FAILURE;
	}
	unsigned char temp1 = 0;
	unsigned char temp2 = 0;
	unsigned char * whichbit = &temp1;
	unsigned char * curbyte = &temp2;
	TreeNode * curpos = namu->ptr;
	while(curpos->right != NULL)
	{
		curpos = curpos -> right;
	}
	printHeader(namu->ptr, headerFile, whichbit, curbyte, curpos->label);
	////////////////////////////////////////////////////////////
	printContents(inFile, headerFile, table, whichbit, curbyte);
	fclose(inFile);
	fclose(headerFile);
	/////////////////////FREE///////////////////////////////////
	free(asciiCount);	
	freeTree(namu->ptr);
	free(namu);
	for(i = 0; i < ASCII_SIZE; i++){
		free(table[i]);
	}
	free(table);
	////////////////////////////////////////////////////////////
	
	clock_t end = clock();
	printf("It took %f seconds for the compression.\n", (float) (end - begin) / (CLOCKS_PER_SEC) );

	return EXIT_SUCCESS;
}
