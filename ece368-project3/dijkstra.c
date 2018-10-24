#include "dijkstra.h"
#include "math.h"

void dijkstra(MapNode * map, int cur, int final, int numvert) {
	if(map[cur].distance > map[final].distance) {
		return;
	}
	if(cur == final) {
		return;
	}
	map[cur].visited = true;
	
	AdjNode * curnode = map[cur].head;
	while(curnode != NULL) {
		int weight = sqrt( pow((map[curnode->node].xpos - map[cur].xpos),2) + pow((map[curnode->node].ypos - map[cur].ypos),2) );
		if( ( map[cur].distance + weight ) < map[curnode->node].distance & map[curnode->node].visited == false) {
			map[curnode->node].distance = map[cur].distance + weight;
		}
		curnode = curnode->next;
	}
	
	int min_distance = (int) INFINITY;
	int min_node = -1;
	int i;
	for(i = 0; i < numvert; i++) {
		if(map[i].distance < min_distance && map[i].visited == false) {
				min_distance = map[i].distance;
				min_node = i;
		}
	}
	dijkstra(map, min_node, final, numvert);	
}

MapNode * mapgen(FILE * inFile, int * numvert){
    
	// LOCAL DECLARATION
	int i = 0;
    int ch;
    char * temp = malloc(sizeof(char) * 10);
    int numedge;
    ////////////////////
	while ( (ch = fgetc(inFile)) != '\n' ) {
        if( ch == ' ' ) {
            temp[i] = '\0';
            *numvert = atof(temp);
            i = 0;
        }
        else {
            temp[i] = ch;
            i++;
        }
    }
    temp[i] = '\0';
    numedge = atof(temp);
    //printf("Number of vertices: %d\n", *numvert);
    //printf("Number of edges: %d\n", numedge);

    // MALLOC map //
    MapNode * map = malloc(sizeof(MapNode) * (*numvert));
    for(i = 0; i < (*numvert); i++) {
		map[i].head = NULL;
		map[i].distance = (int) INFINITY;
		map[i].visited = false;
    }

    // READ ALL VERTICES AND PUT THEM IN map //
    int j = 0;
    int tempindex;
    int tempxpos;
    int tempypos;
    for(i = 0; i < (*numvert); i++) {
        if( (ch = fgetc(inFile)) == ' ' ) {
            while( (ch = fgetc(inFile)) == ' ' ) {
                //skip spaces
            }
            temp[j] = ch;
            j++;
        }
        else {
            temp[j] = ch;
            j++;
        }
        while( (ch = fgetc(inFile)) != ' ' ) {
            temp[j] = ch;
            j++;
        }
        temp[j] = '\0';
        tempindex = atof(temp);
        j = 0;
        while( (ch = fgetc(inFile)) == ' ' ) {
            // skip spaces
        }
        temp[j] = ch;
        j++;
        while( (ch = fgetc(inFile)) != ' ' ) {
            temp[j] = ch;
            j++;
        }
        temp[j] = '\0';
        tempxpos = atof(temp);
        j = 0;
        while( (ch = fgetc(inFile)) == ' ' ) {
            //skip spaces
        }
        temp[j] = ch;
        j++;
        while( (ch = fgetc(inFile)) != '\n' ) {
            temp[j] = ch;
            j++;
        }
        temp[j] = '\0';
        tempypos = atof(temp);
        j = 0;
        map[tempindex].xpos = tempxpos;
        map[tempindex].ypos = tempypos;
    }

    // READ ALL EDGES AND PUT AS AN ATTRIBUTE OF EACH NODE //
    int first;
    int second;
    for(i = 0; i < numedge; i++) {
        if( (ch = fgetc(inFile)) == ' ' ) {
            while( (ch = fgetc(inFile)) == ' ' ) {
                //skip spaces
            }
            temp[j] = ch;
            j++;
        }
        else {
            temp[j] = ch;
            j++;
        }
        while( (ch = fgetc(inFile)) != ' ' ) {
            temp[j] = ch;
            j++;
        }
        temp[j] = '\0';
        first = atof(temp);
        j = 0;
        while( (ch = fgetc(inFile)) != '\n' && (ch != EOF) ) {
            temp[j] = ch;
            j++;
        }
        temp[j] = '\0';
        second = atof(temp);
        j = 0;
		
		bool inserted = false;

		if(map[first].head == NULL) {
			map[first].head = malloc(sizeof(AdjNode));
			map[first].head->node = second;
			map[first].head->weight = sqrt( pow((map[second].xpos - map[first].xpos),2) + pow((map[second].ypos - map[first].ypos),2) );
			map[first].head->next = NULL;
		}
		else {
			AdjNode * newnode1 = malloc(sizeof(AdjNode));
			newnode1->node = second;
			newnode1->weight = sqrt( pow((map[second].xpos - map[first].xpos),2) + pow((map[second].ypos - map[first].ypos),2) );
			newnode1->next = NULL;
			AdjNode * curnode1 = map[first].head;
			AdjNode * prevnode1 = map[first].head;
			while(curnode1 != NULL){
				if(newnode1->weight > curnode1->weight) {
					prevnode1 = curnode1;
					curnode1 = curnode1->next;
				}
				else {
					if(curnode1 == map[first].head) {
						map[first].head = newnode1;
						newnode1->next = curnode1;
						inserted = true;
					}
					else {
						prevnode1->next = newnode1;
						newnode1->next = curnode1;
						inserted = true;
					}
				}
				if(inserted == true) {
					break;
				}
			}
			if(inserted == false && curnode1 == NULL) {
				prevnode1->next = newnode1;
			}
		}
		inserted = false;
		if(map[second].head == NULL) {
			map[second].head = malloc(sizeof(AdjNode));
			map[second].head->node = first;
			map[second].head->weight = sqrt( pow((map[first].xpos - map[second].xpos),2) + pow((map[first].ypos - map[second].ypos),2) );
			map[second].head->next = NULL;
		}
		else {
			AdjNode * newnode2 = malloc(sizeof(AdjNode));
			newnode2->node = first;
			newnode2->weight = sqrt( pow((map[first].xpos - map[second].xpos),2) + pow((map[first].ypos - map[second].ypos),2) );
			newnode2->next = NULL;
			AdjNode * curnode2 = map[second].head;
			AdjNode * prevnode2 = map[second].head;
			while(curnode2 != NULL){
				if(newnode2->weight > curnode2->weight) {
					prevnode2 = curnode2;
					curnode2 = curnode2->next;
				}
				else {
					if(curnode2 == map[second].head) {
						map[second].head = newnode2;
						newnode2->next = curnode2;
						inserted = true;
					}
					else {
						prevnode2->next = newnode2;
						newnode2->next = curnode2;
						inserted = true;
					}
				}
				if(inserted == true) {
					break;
				}
			}
			if(inserted == false && curnode2 == NULL) {
				prevnode2->next = newnode2;
			}
		}	
    }
	
	/*	
	// PRINT OUT //
	for(i = 0; i < (*numvert); i++) {
		AdjNode * curnode = map[i].head;
		if(curnode != NULL) {
			printf("%d:", i);
		}
		while(curnode != NULL){
			printf(" %d", curnode->node);
			curnode = curnode->next;
		}
		printf("\n");
	}
	*/

    // FREE TEMPORARY STRING //
    free(temp);

    // RETURN GENERATED map //
    return map;
}
