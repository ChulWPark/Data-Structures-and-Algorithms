#include<stdio.h>
#include<stdlib.h>
#include "huff.h"
#include "stdint.h"
#include <string.h>

ListNode * buildNode(int aphb, long ct)
{
	ListNode * built = malloc(sizeof(ListNode));
	built->next = NULL;
	built->ptr = malloc(sizeof(TreeNode));
	built->ptr->label = aphb;
	built->ptr->count = ct;
	built->ptr->left = NULL;
	built->ptr->right = NULL;
	return built;
}
ListNode * addNode(ListNode * head, int aphb, long ct)
{
	if(head == NULL)
	{
		head = buildNode(aphb, ct);
		return head;
	}
	else
	{
		ListNode * storedHead = head;
		ListNode * newnode = buildNode(aphb, ct);
		ListNode * curnode = head;
		ListNode * prevnode = head;
		while(curnode != NULL)
		{
			if(newnode->ptr->count > curnode->ptr->count)
			{
				prevnode = curnode;
				curnode = curnode->next;
			}
			else if(newnode->ptr->count < curnode->ptr->count)
			{
				if(curnode == head)
				{
					newnode->next = curnode;
					return newnode;
				}
				else
				{
					prevnode->next = newnode;
					newnode->next = curnode;
					return storedHead;
				}
			}
			else
			{
				if(newnode->ptr->label > curnode->ptr->label)
				{
					prevnode = curnode;
					curnode = curnode->next;
				}
				else if(newnode->ptr->label < curnode->ptr->label)
				{
					prevnode->next = newnode;
					newnode->next = curnode;
					return storedHead;
				}
			}
		}
		curnode = newnode;
		prevnode->next = curnode;
		return storedHead;
	}
}

ListNode * buildTree(ListNode * head)
{
	if(head->next == NULL)
	{
		return head;
	}
	else if(head->next->next == NULL)
	{
		TreeNode * first = head -> ptr;
		TreeNode * second = head -> next -> ptr;
		free(head->next);
		free(head);
		ListNode * center = malloc(sizeof(ListNode));
		center -> next = NULL;
		center -> ptr = malloc(sizeof(TreeNode));
		center -> ptr -> count = (first -> count) + (second -> count);
		center -> ptr -> label = 1000;
		center -> ptr -> left = first;
		center -> ptr -> right = second;
		return center;
	}
	TreeNode * first = head -> ptr;
	TreeNode * second = head -> next -> ptr;
	ListNode * save = head -> next -> next;
	free(head->next);
	free(head);
	ListNode * center = malloc(sizeof(ListNode));
	center -> next = NULL;
	center -> ptr = malloc(sizeof(TreeNode));
	center -> ptr -> count = (first -> count) + (second -> count);
	center -> ptr -> label = 1000;
	center -> ptr -> left = first;
	center -> ptr -> right = second;
	head = addTree(save, center);
	head = buildTree(head);
	return head;
}

ListNode * addTree(ListNode * head, ListNode * target)
{	
	ListNode * storedHead = head;
	ListNode * curnode = head;
	ListNode * prevnode = head;
	while(curnode != NULL)
	{
		if(target->ptr->count > curnode->ptr->count)
		{
			prevnode = curnode;
			curnode = curnode->next;
		}
		else if(target->ptr->count < curnode->ptr->count)
		{
			if(curnode == head)
			{
				target->next = curnode;
				return target;
			}
			else
			{
				prevnode->next = target;
				target->next = curnode;
				return storedHead;
			}
		}
		else
		{
			prevnode = curnode;
			curnode = curnode->next;
		}
	}
	curnode = target;
	prevnode->next = curnode;
	return storedHead;
}

void printTree(TreeNode * head, char * huff, int * index, int ** table)
{
	if(head == NULL)
	{
		return;
	}
	if(head->label == 1000)
	{
	}
	if(head->label != 1000)
	{
		huff[index[0]] = '\0';
		int i = 0;
		while(huff[i] != '\0')
		{
			if(huff[i] == '1')
			{
				table[head->label][i] = 1;
			}
			else if(huff[i] == '0')
			{
				table[head->label][i] = 0;
			}
			i++;
		}
		table[head->label][i] = 7; // indicating null
		index[0]--;
		return;
	}
	huff[index[0]] = '0';
	index[0]++;
	printTree(head->left, huff, index, table);
	huff[index[0]] = '1';
	index[0]++;
	printTree(head->right, huff, index, table);
	index[0]--;
}

void printContents(FILE * inFile, FILE * headerFile, int ** table, unsigned char * whichbit, unsigned char * curbyte)
{
	int target;
	int i;
	unsigned char temp;
	char ch;
	while( (ch = fgetc(inFile)) != EOF)
	{
		target = (int) ch;
		i = 0;
		while(table[target][i] != 7)
		{
			temp = (unsigned char) table[target][i];
			writeBit(headerFile, temp, whichbit, curbyte);
			i++;
		}
	}
	//ADDING EOF AT THE END OF THE FILE
	i = 0;
	while(table[0][i] != 7)
	{
		temp = (unsigned char) table[0][i];
		writeBit(headerFile, temp, whichbit, curbyte);
		i++;
	}
	padZero(headerFile, whichbit, curbyte);	
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

void printHeader(TreeNode * head, FILE * headerFile, unsigned char * whichbit, unsigned char * curbyte, int last)
{
	unsigned char nonleaf = 0;
	unsigned char leaf = 1;
	unsigned char temp;
	if(head == NULL)
	{
		return;
	}
	else if(head->label != 1000)
	{
		unsigned char fixed = (unsigned char) head->label; 
		writeBit(headerFile, leaf, whichbit, curbyte);
		for(int i = 0; i < 8; i++)
		{
			temp = fixed >> (7 - i);
			writeBit(headerFile, temp, whichbit, curbyte);
		}
		if(head->label == last)
		{
			padZero(headerFile, whichbit, curbyte);
		}
		//DEBUGGING PURPOSE
		//printf("%d", 1);
		//printf("%c", head->label);
	}
	else
	{
		writeBit(headerFile, nonleaf, whichbit, curbyte);
		//DEBUGGING PURPOSE
		//printf("%d",0);
	}
	printHeader(head->left, headerFile, whichbit, curbyte, last);
	printHeader(head->right, headerFile, whichbit, curbyte, last);
}

int writeBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte)
{
	if ((* whichbit) == 0)
	{
		// reset
		* curbyte = 0;
    }
	// shift the bit to the correct location
	unsigned char temp = bit << (7 - (* whichbit));
	* curbyte |= temp; // store the data
	int value = 0;
	if ((* whichbit) == 7)
	{
    	int ret;
    	ret = fwrite(curbyte, sizeof(unsigned char), 1, fptr);
    	// printByte(* curbyte); // for debugging
    	if (ret == 1)
		{
			value = 1;
		}
    	else
		{
	  		value = -1;
		}
    }
	* whichbit = ((* whichbit) + 1) % 8;
	return value;
}

int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte)
{
	int rtv;
	while ((* whichbit) != 0)
    {
    	rtv = writeBit(fptr, 0, whichbit, curbyte);
    	if (rtv == -1)
		{
	  		return -1;
		}
    }
  	return rtv;
}
