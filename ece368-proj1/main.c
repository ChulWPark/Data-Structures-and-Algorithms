#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sorting.h"

int main(int argc, char ** argv){
	int N = 1000000;
	
	Save_Seq1(argv[1], N);
	Save_Seq2(argv[2], N);
	return 0;
}
