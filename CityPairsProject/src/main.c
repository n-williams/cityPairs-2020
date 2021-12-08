#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citypairs.h"

int main(){

	//reads both important files, plus prints an error if problems occur
	FILE *fenergy = fopen("src/energy.txt","r");
	FILE *fcitypairs = fopen("src/citypairs.txt","r");
	if(fenergy == NULL || fcitypairs == NULL){
		printf("Error reading data file\n");
		return -1;
	}
	
	//variables for processing fenergy file
	int CityCount = 0;
	int LineCount = 0;
	char line[1024];
    char City1[20];
	char City2[20];
	int Pair1;
	int Pair2;
	int energy;

	//reads each line and counts whenever a newline occurs
	while(fgets(line,1024,fenergy) != NULL){
		LineCount++;
	}
	//reset read position in document to start
    fseek(fenergy,0,SEEK_SET); 

	//double LineCount as we need to have edges go both ways
    struct Graph* graph = createGraph(LineCount*2);

	knownCitiesList = malloc(128 * LineCount * sizeof(int));

	for(int i=0; i<LineCount; i++){
		//separating each word in each line
		fscanf(fenergy, "%s\t%s\t%d", City1,City2,&energy);
		
		//loops through the list to see if the city has already occurred
		int DuplicateCity1 = 0;
		int DuplicateCity2 = 0;
		for(int j=0; j<CityCount; j++){
			if(strcmp(City1,getName(j)) == 0){
				DuplicateCity1 = 1;
			}
			if(strcmp(City2,getName(j)) == 0){
				DuplicateCity2 = 1;
			}
		}
		
		//if it hasn't, add it to the known cities list
		if(!DuplicateCity1){
			sprintf(getName(CityCount), "%s", City1);
			CityCount++;
		}
		//assign the city index to half of the pair
		for(int j=0; j<CityCount; j++){
			if(strcmp(City1,getName(j)) == 0){
				Pair1 = j;
				break;
			}
		}
		if(!DuplicateCity2){
			sprintf(getName(CityCount), "%s", City2);
			CityCount++;
		}
		for(int j=0; j<CityCount; j++){
			if(strcmp(City2,getName(j)) == 0){
				Pair2 = j;
				break;
			}
		}
		//add two edges with the pair just assigned
		//makes this bidirectional, with the same 
		//energy gain/loss either way
        addEdge(graph, Pair1, Pair2, energy, i);
		addEdge(graph, Pair2, Pair1, energy, i);
	}

    ////////////////////////////
	
	//variables for processing fcitypairs file
	int cityPairLineCount = 0;
    char CityPair1[20];
    char CityPair2[20];
	
	//reads each line and counts whenever a newline occurs
	while(fgets(line,1024,fcitypairs) != NULL){
        cityPairLineCount++;
    }
	//reset read position in document to start
    fseek(fcitypairs,0,SEEK_SET);

	int* startCities = malloc(sizeof(int) * cityPairLineCount);
    int* endCities   = malloc(sizeof(int) * cityPairLineCount);

    for(int i=0; i<cityPairLineCount; i++){
		//separating each word in each line
        fscanf(fcitypairs, "%s\t%s", CityPair1,CityPair2);
		
		//assigns the startCities variable the index of the source city
        for(int j=0; j<CityCount; j++){
            if(strcmp(CityPair1, getName(j)) == 0){
                startCities[i] = j;
                break;
            }
        }
		
		//assigns the endCities variable the index of the destination city
        for(int j=0; j<CityCount; j++){
            if(strcmp(CityPair2, getName(j)) == 0){
                endCities[i] = j;
                break;
            }
        }
		//run the main logic for each pair needed to be assessed
        BellmanFord(graph, startCities[i], endCities[i]);
    }

    return 0;
}
