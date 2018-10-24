#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// DATA STRUCTURE FOR THE MAP //
typedef struct MapNode {
	int xpos;
	int ypos;
	int distance;
	bool visited;
	struct AdjNode * head;
} MapNode;
////////////////////////////////
// DATA STRUCTURE FOR THE ADJACENCY LINKED LIST //
typedef struct AdjNode {
	int node;
	int weight;
	struct AdjNode * next;
} AdjNode;
//////////////////////////////////////////////////
// DATA STRUCTURE FOR THE PATH LINKED LIST //
typedef struct PathNode {
	int node;
	struct PathNode * next;
} PathNode;
/////////////////////////////////////////////

void dijkstra(MapNode * map, int cur, int final, int numvert);

MapNode * mapgen(FILE * inFile, int * numvert);
