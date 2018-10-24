#ifndef PA15_H
#define PA15_H		 

#define ASCII_SIZE 256


typedef struct TreeNode {
   int label;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

TreeNode * buildNode(int aphb);

int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte);

TreeNode * readHeader(TreeNode * head, FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte);

void readContents(FILE * fptr, FILE * unhuffFile, TreeNode * head, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte);

void freeTree(TreeNode * head);

#endif
