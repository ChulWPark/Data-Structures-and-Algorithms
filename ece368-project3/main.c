#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"
#include "time.h"

int main(int argc, char ** argv) {
	
	clock_t begin = clock();

	// CHECK EXECUTE COMMAND //
	if(argc != 3) {
		printf("Wrong Command... It should be ./dijkstra map.txt query.txt");
		return EXIT_FAILURE;
	}

	// OPEN THE INPUT FILE //
	FILE * inFile = fopen(argv[1], "r");
	if(inFile == NULL) {
		fprintf(stderr, "can't open the input file.  Quit.\n");
		return EXIT_FAILURE;
	}

	// CALL mapgen FUNCTION //
	int numvert = 0;
	int * pointer = &numvert;
	MapNode * map = mapgen(inFile, pointer);
	
	// CLOSE THE INPUT FILE //
    fclose(inFile);
	
	// OPEN THE INPUT FILE //
	inFile = fopen(argv[2], "r");
	if(inFile == NULL) {
		fprintf(stderr, "can't open the input file.  Quit.\n");
		return EXIT_FAILURE;
	}
	
	// READ THE QUERY FILE //
	int numquery;
	int start;
	int end;
	fscanf(inFile, "%d", &numquery);
	for(int i = 0; i < numquery; i++) {
		for(int j = 0; j < numvert; j++) {
			map[j].distance = (int) INFINITY;
			map[j].visited = false;
		}
		fscanf(inFile, "%d %d", &start, &end);
		map[start].distance = 0;
		dijkstra(map, start, end, numvert);
		printf("%d\n", map[end].distance);
	}

	// CLOSE THE INPUT FILE //
	fclose(inFile);

	// FREE AdjNode LINKED LIST //
	for(int i = 0; i < numvert; i++) {
		if(map[i].head != NULL) {
			while(map[i].head != NULL) {
				AdjNode * curnode = map[i].head;
				map[i].head = curnode->next;
				free(curnode);
			}
		}
	}

	// FREE map
	free(map);

	clock_t finish = clock();
	printf("It took %f seconds for finding shortest path(s)\n", (float) (finish - begin) / (CLOCKS_PER_SEC) );

	return EXIT_SUCCESS;
}
