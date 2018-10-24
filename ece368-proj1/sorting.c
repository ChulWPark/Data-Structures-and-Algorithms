#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorting.h"

long *Load_File(char *Filename, int *Size){
	
	//OPEN THE FILE
	FILE * datastream = fopen(Filename, "r");
	
	//IF FILE WAS NOT OPENED PROPERLY, return NULL;
	if(datastream == NULL){
		return NULL;
	}
	
	//READING THE FIRST LINE OF THE FILE, WHICH IS THE SIZE OF AN ARRAY
	char sizetemp[1000]; //temporary string
	fgets(sizetemp, 1000, datastream);
	*Size = (int) atof(sizetemp); //atof RETURNS THE STRING INTO A DOUBLE
	
	//MALLOC THE ARRAY IN HEAP MEMORY
	long *Array = malloc(sizeof(long) * (*Size));
	char elemtemp[100]; //temporary string
	
	//READING REST OF THE FILE, WHICH IS THE ARRAY ELEMENTS
	int i;
	for(i = 0; i < (*Size); i++){
		fgets(elemtemp, 100, datastream);
		Array[i] = (long) atof(elemtemp);
	}
	
	//CLOSE THE FILE
	fclose(datastream);
	
	//RETURN THE LOADED ARRAY
	return Array;
}

int Save_File(char *Filename, long *Array, int Size){
	
	//VAR IN ORDER TO KEEP TRACK OF NUMBER OF ELEMENTS SAVED	
	int savecount = 0;
	
	//OPEN THE FILE
	FILE * datastream = fopen(Filename, "w");
	
	//IF FILE WAS NOT OPENED PROPERLY, return NULL;
	if(datastream == NULL){
		return 0;
	}

	//WRITING THE FIRST LINE OF THE FILE, WHICH IS THE SIZE OF AN ARRAY
	fprintf(datastream, "%d\n", Size);
	
	//WRITING REST OF THE FILE, WHICH IS THE ARRAY
	int i;
	for(i = 0; i < Size; i++){
		fprintf(datastream, "%ld\n", Array[i]);
		savecount++;
	}

	//CLOSE THE FILE
	fclose(datastream);

	//RETURN NUMBER OF ELEMENTS SAVED//SUPPOSED TO BE THE NUMBER OF ELEMENTS IN THE ARRAY, WHICH MEANS SUCCESS
	return savecount;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move){

	//GET GAP SEQUENCE FROM Generate_Seq1 FUNCTION
	int * seqarray = Generate_Seq1(Size);
	
	int i; //SUBARRAY SELECTION INDEX
	int j; //SUBARRAY ELEMENT SELECTION INDEX
	int gap; //seqarray[k]
	int k; //INDEX OF seqarray
	int m; //SEARCH INDEX
	int g = 0; //SEARCH END OF THE seqarray INDEX: START FROM THE LARGEST NUMBER IN THE SEQUENCE
	long temp; //TEMPORARY IN ORDER TO STORE THE ELEMENT THAT IS TO BE INSERTED TO THE SORTED PART
	
	//FINDING THE INDEX OF LARGEST NUMBER IN THE SEQ1
	while(seqarray[g] != '\0'){
		g++;
	}
	g = g - 1; //INDEX OF LARGEST NUMBER IN SEQ1
	//GAP SELECTION FOR LOOP
	for(k = g; k >= 0; k--){
		gap = seqarray[k]; //GAP IS SELECTED FROM THE gapArray
		//SUBARRAY SELECTION FOR LOOP
		for(i = 0; i < gap; i++){ //START FROM THE FIRST SUBARRAY~
			//SUBARRAY ELEMENT SELECTION FOR LOOP
			for(j = i + gap; j < Size; j = j + gap){ //START FROM THE SECOND ELEMENT IN SUBARRAY
				temp = Array[j]; //STORE IT FIRST : ELEMENT THAT IS TO BE SORTED
				(*N_Move)++;
				for(m = j; m > 0; m = m - gap){ //SEARCH WHERE TO INSERT (LEFT PART OF THE ARRAY)
					(*N_Comp)++;
					if(Array[m - gap] > temp){  
						Array[m] = Array[m - gap];
						(*N_Move)++;
						(*N_Comp)++;
						if(m == (gap + i)){ //IF IT REACHES THE SECOND ELEMENT IN SUBARRAY
							Array[m - gap] = temp;
							(*N_Move)++;
							break;
						}
					}
					else{ //if(temp > Array[m - gap]): MOVE ON 
						Array[m] = temp;
						(*N_Move)++;
						break;
					}
				}
			}
		}
	}
		
	//FREE GAP ARRAY
	free(seqarray);
	
	return;
}

void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move){

	//GET GAP SEQUENCE FROM Generate_Seq2 FUNCTION
	int * seqarray = Generate_Seq2(Size);
	
	int i; //Array INDEX
	int gap; //seqarray[h]
	long temp; //temporary VARIABLE FOR SWAP METHOD
	int g = 0; //SEARCH NUMBER OF GAP VALUES IN THE SEQUENCE
	int h; //INDEX OF seqarray
	int repeat = 1;	//CHECK VARIABLE WHICH DECIDES TO REPEAT THE BUBBLE SORT OR NOT
	int limit = Size; //VARIABLE THAT INDICATES THE UNSORTED PART OF THE Array

	//SEARCH HOW MANY GAP VALUES ARE IN THE seqarray
	while(seqarray[g] != '\0'){
		g++;
	}

	//GAP GENERATION FOR LOOP
	for(h = 0; h < g; h++){
		gap = seqarray[h]; //GAP IS SELECTED FROM THE seqarray
		for(i = 0; i < (Size - gap); i++){
			(*N_Comp)++;
			//IF Array[i] IS GREATER THAN Array[i + gap], THEN SWAP
			if(Array[i] > Array[i + gap]){
				temp = Array[i];
				Array[i] = Array[i + gap];
				Array[i + gap] = temp;
				(*N_Move) = (*N_Move) + 3; //3 MOVES OCCURRED
			}
		}
	}
	
	//GO THROUGH THE WHOLE ARRAY AGAIN WITH GAP = 1
	//THIS IS DOUBLE CHECK BECAUSE ITERATIONS ABOVE WON'T USUALLY SORT COMPLETELY
	while(repeat){ //THIS WHILE LOOP RUNS UNTIL NO MOVES OCCUR
		repeat = 0; //INITIALIZE CHECK VARIABLE TO 0
		for(i = 0; i < limit - 1; i++){
			(*N_Comp)++;
			//IF Array[i] IS GREATER THAN Array[i + gap], THEN SWAP
			if(Array[i] > Array[i + gap]){
				temp = Array[i];
				Array[i] = Array[i + gap];
				Array[i + gap] = temp;
				(*N_Move) = (*N_Move) + 3; //3 MOVES OCCURRED
				repeat = 1; //SINCE MOVES OCCURRED, ASSERT CHECK VARIABLE
			}
		}
		limit--; //SINCE THE LAST ELEMENT IS SORTED FOR SURE, THIS LETS THE ITERATION TO IGNORE THAT ONE IN NEXT ITERATION
	}
	
	//FREE seqarray
	free(seqarray);

	return;
}

void Save_Seq1(char *Filename, int N){
	
	//OPEN THE FILE
	FILE * datastream = fopen(Filename, "w");

	//IF FILE WAS NOT OPENED PROPERLY, return;
	if(datastream == NULL){
		return;
	}

	//WRITING THE SEQUENCE IN ASCENDING ORDER
	int * seqarray = malloc(sizeof(int) * N);
	seqarray[0] = 1;
	int i = 0; //POWER OF 2
	int j = 0; //POWER OF 3
	int k = 1; //FOR LOOP INDEX
	int temp1 = 0; //TEMP VAR FOR TWICED
	int temp2 = 0; //TEMP VAR FOR TRIPLED
	fprintf(datastream, "%d\n", seqarray[0]);
	while(seqarray[k - 1] < N){
		if( (seqarray[i] * 2) == seqarray[k - 1] ){
			i++;
		}
		if( (seqarray[j] * 3) == seqarray[k - 1] ){
			j++;
		}
		temp1 = seqarray[i] * 2;
		temp2 = seqarray[j] * 3;
		if(temp1 < temp2){
			i++;
			seqarray[k] = temp1;
			if( (temp1 < N) && (temp1 > 0) ){
				fprintf(datastream, "%d\n", temp1);
			}
		}
		else{ //if(temp1 > temp2)
			j++;
			seqarray[k] = temp2;
			if( (temp2 < N) && (temp2 > 0) ){
				fprintf(datastream, "%d\n", temp2);
			}
		}
		k++;
	}
	
	//FREE ARRAY
	free(seqarray);
	
	//CLOSE THE FILE
	fclose(datastream);
		
	return;
}

void Save_Seq2(char *Filename, int N){
	
	//OPEN THE FILE
	FILE * datastream = fopen(Filename, "w");

	//IF FILE WAS NOT OPENED PROPERLY, return;
	if(datastream == NULL){
		return;
	}

	//PUT THE SEQUENCE IN DESCENDING ORDER INTO AN ARRAY
	int seqelem;
	int * seqarray = malloc(sizeof(int) * N);
	int i = 0;
	int start = N / 1.3;
	for(seqelem = start; seqelem > 0; seqelem = seqelem / 1.3){
		if( (seqelem == 9) || (seqelem == 10) ){ //IF IT IS 9 OR 10, CHANGE IT INTO 11
			seqelem = 11;
		}
		seqarray[i] = seqelem;
		i++;
	}
	
	//WRITING THE SEQUENCE IN ASCENDING ORDER (FROM END OF THE ARRAY)
	int seqindex;
	for(seqindex = i - 1; seqindex >= 0; seqindex = seqindex - 1){
		fprintf(datastream, "%d\n", seqarray[seqindex]);
	}

	//FREE TEMP ARRAY
	free(seqarray);

	//CLOSE THE FILE
	fclose(datastream);
	
	return;
}

int * Generate_Seq1(int Size){
		
	int * seqarray = malloc(sizeof(int) * Size);
	seqarray[0] = 1; //FIRST SEQUENCE ELEMENT IS 1, WHICH IS (2^0 * 3^0)
	int a = 0; //POWER OF 2
	int b = 0; //POWER OF 3
	int c = 1; //WHILE LOOP INDEX
	int temp1 = 0; //TEMP VAR FOR TWICED
	int temp2 = 0; //TEMP VAR FOR TRIPLED
	while(seqarray[c - 1] < Size){
		if( (seqarray[a] * 2) == seqarray[c - 1] ){
			a++;
		}
		if( (seqarray[b] * 3) == seqarray[c - 1] ){
			b++;
		}
		temp1 = seqarray[a] * 2;
		temp2 = seqarray[b] * 3;
		if(temp1 < temp2){
			a++;
			seqarray[c] = temp1;
		}
		else{ //if(temp1 > temp2)
			b++;
			seqarray[c] = temp2;
		}
		c++;
	}
	seqarray[c - 1] = '\0'; //PUT NULL AT THE END OF THE seqarray: INDICATE THE END
	
	return seqarray;	
}

int * Generate_Seq2(int Size){

	int seqelem;
	int * seqarray = malloc(sizeof(int) * Size);
	int i = 0;
	int start = Size / 1.3;
	for(seqelem = start; seqelem > 0; seqelem = seqelem / 1.3){
		if( (seqelem == 9) || (seqelem == 10) ){
			seqelem = 11;
		}
		seqarray[i] = seqelem;
		i++;
	}
	seqarray[i] = '\0'; //PUT NULL AT THE END OF THE seqarray: INDICATE THE END
	
	return seqarray;
}
