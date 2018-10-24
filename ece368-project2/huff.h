#ifndef PA15_H
#define PA15_H		 

#define ASCII_SIZE 256

typedef struct TreeNode {
   int label;
   long count;
   struct TreeNode *left;
   struct TreeNode *right;
} TreeNode;

typedef struct ListNode {
   TreeNode *ptr;
   struct ListNode *next;
} ListNode;

ListNode * buildNode(int aphb, long ct);

ListNode * addNode(ListNode * head, int aphb, long ct);

ListNode * buildTree(ListNode * head);

ListNode * addTree(ListNode * head, ListNode * target);

void printTree(TreeNode * head, char * huff, int * index, int ** table);

void printContents(FILE * inFile, FILE * headerFile, int ** table, unsigned char * whichbit, unsigned char * curbyte);

void freeTree(TreeNode * head);

void printHeader(TreeNode * head, FILE * headerFile, unsigned char * whichbit, unsigned char * curbyte, int last);

int writeBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte);

int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte);

#endif
