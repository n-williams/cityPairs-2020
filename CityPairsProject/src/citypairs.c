#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citypairs.h"

//integrates an index for the unique cities, which can then be called upon
//eg. in arrays
char *getName(int c){
    char* name = knownCitiesList + c*128;
    return name;
}

struct Edge{
    int source;
    int destination;
    int energy;
};

struct Graph{
    int vertices;
    int edgeNum;

    struct Edge* edge;
};

//function to create a graph
struct Graph* createGraph(int E){
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->edge = malloc(E * sizeof(struct Edge));


    graph->vertices = MAX_CITIES; //
    graph->edgeNum = E; //

    return graph;
}

//function to add an edge between two cities
void addEdge(struct Graph* graph, int src, int dest, int wgt, int i){

    graph->edge[i].source = src;
    graph->edge[i].destination = dest;
    graph->edge[i].energy = wgt;
};

//main logic to determine least energy consumed path
void BellmanFord(struct Graph* graph, int source, int destination){
    //variables
	int i;
	int j;
    int u;
    int v;
    int w;

	//total vertex number in the graph g
	int tV = graph->vertices;

	//total edge number in the graph g
	int tE = graph->edgeNum;

	//distance array
	//size equal to the number of vertices of the graph
	int d[tV];

	//fill the distance array with each being infinite
	for (i = 0; i < tV; i++) {
		d[i] = INF;
	}

	//mark the source vertex
	d[source] = 0;

	//main iterator, tV-1 times as this is the maximum possible
	for(i=1; i<=tV-1; i++) {
		for(j=0; j<tE; j++) {
			//get the edge data
			u = graph->edge[j].source;
			v = graph->edge[j].destination;
			w = graph->edge[j].energy;

			if(d[u] != INF && d[v] > d[u] + w) {
				d[v] = d[u] + w;
			}
		}
	}

	//detect negative cycle
	//if value changes then we have a negative cycle in the graph
	//and we cannot find the shortest distances
	for(i=0; i<tE; i++) {
		u = graph->edge[i].source;
		v = graph->edge[i].destination;
		w = graph->edge[i].energy;
		if(d[u] != INF && d[v] > d[u] + w) {
			printf("Negative weight cycle detected\n");
			return;
		}
	}

    printf("Vertex\t\tDistance from %s\n", getName(source));
	for(i = 0; i<tV; i++){
        printf("%s\t\t\t%d\n", getName(i), d[i]);
	}

    printf("\nLowest amount of energy consumed between %s and %s is %d\n\n\n", getName(source), getName(destination), d[destination]);

    return;
}
