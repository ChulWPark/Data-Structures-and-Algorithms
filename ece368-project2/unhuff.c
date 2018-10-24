#include<stdio.h>
#include<stdlib.h>
#include "unhuff.h"
#include "stdint.h"

TreeNode * buildNode(int aphb)
{
	TreeNode * built = malloc(sizeof(TreeNode));
	built->label = aphb;
	built->left = NULL;
	built->right = NULL;
	return built;
}

int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	int ret = 1;
	if ((* whichbit) == 0)
	{
		// read a byte from the file
		ret = fread(curbyte, sizeof(unsigned char), 1, fptr);
	}
	if(ret != 1)
	{
		// read fail
		return -1;
	}
	// shift the bit to the correct location
	unsigned char temp = (* curbyte) >> (7 - (* whichbit));
	temp = temp & 0X01; //get only 1 bit, ignore the others
	// increase by 1
	* whichbit = ((*whichbit) + 1) % 8;
	* bit = temp;
	return 1;
}

TreeNode * readHeader(TreeNode * head, FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	readBit(fptr, bit, whichbit, curbyte);
	if((*bit) == 0) // isNonLeafNode
	{
		head = buildNode(1000);
		head->left = readHeader(head, fptr, bit, whichbit, curbyte);
		head->right = readHeader(head, fptr, bit, whichbit, curbyte);
		return head;
	}
	if((*bit) == 1) // isLeafNode
	{
		unsigned char temp = 0;
		for(int i = 0; i < 8; i++)
		{
			readBit(fptr, bit, whichbit, curbyte);
			unsigned char comp = (* bit) << (7 - i);
			temp |= comp;
		}
		TreeNode * leaf = buildNode( (int) temp );
		return leaf;
	}
	return NULL;
}

void readContents(FILE * fptr, FILE * unhuffFile, TreeNode * head, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte)
{
	TreeNode * curpos = head;
	while(1)
	{
		readBit(fptr, bit, whichbit, curbyte);
		if( (*bit) == 1)
		{
			curpos = curpos -> right;
		}
		if( (*bit) == 0)
		{
			curpos = curpos -> left;
		}
		if(curpos->label == 0)
		{
			break;
		}
		if(curpos->label != 1000)
		{
			fprintf(unhuffFile, "%c", curpos->label);
			curpos = head;
		}
	}
	return;
}


void freeTree(TreeNode * head)
{
	if(head == NULL)
	{
		return;
	}
	freeTree(head->left);
	freeTree(head->right);
	free(head);
}
