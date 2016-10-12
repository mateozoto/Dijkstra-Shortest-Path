/**
* Assignment 3
* CPSC 441
* Mateo Zoto / 10082263
* Dijkstra's, minDistance based of http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_ROWS 26
#define MAX_COLUMNS 26
#define MAX_HOBBITS 14
#define LENGTH_NAME 20

// struct array that contains the accumulated hops,dist,time,gold,trolls, and path for every dwarf 
// that is traveling to bilbos house
struct homes{
	char hobbitName[LENGTH_NAME];
	int home;
	int totaldistance;
	int totaltime;
	int totalgold;
	int totaltrolls;
	int totalhops;
	char path[MAX_ROWS];
} homesList[MAX_HOBBITS];
//initialize number of hobbits to 0 and initialize adjancency matrices for dist, time, gold, trolls and edge
//to pass into dijkstra's 
int numberofhobbits = 0;
char pathStored [MAX_ROWS][MAX_COLUMNS];
int edge [MAX_ROWS][MAX_COLUMNS];
int distance[MAX_ROWS][MAX_COLUMNS];
int time [MAX_ROWS][MAX_COLUMNS];
int gold [MAX_ROWS][MAX_COLUMNS];
int trolls [MAX_ROWS][MAX_COLUMNS];
// calculates the lowest index
// code from http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
int minDistance(int graph[], bool seen[]){
   int vertice;
   int min = INT_MAX, min_index;
   for (vertice = 0; vertice < MAX_ROWS; vertice++)
     if (graph[vertice] < min && seen[vertice] == false){
         min = graph[vertice];
		 min_index = vertice;
	}
   return min_index;
}
// code based from http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
// input is bilbos position, and output is the shortest distance to every vertice on the graph aka the dwarves
// handles averages and the displaying of everything, accumulation of gold trolls and the like with the calculation
// of the shortest path based on input
void dijkstra(int graph[MAX_ROWS][MAX_COLUMNS], int bilbo, int algorithm){
     int dist[MAX_ROWS]; 
	 int i, j;
	 int count;
	 int v;
     bool seen[MAX_ROWS];
	 // initialize dist to INF and seen to false for everything as we have not seen everything yet
     for (i = 0; i < MAX_ROWS; i++){
        dist[i] = INT_MAX;
		seen[i] = false;
	}
	//initialize the path stored double matrix
	for (i = 0; i < MAX_ROWS; i++){
		for (j = 0; j < MAX_ROWS; j++){
			pathStored[i][j] = '+';
		}
	}
	//initialize all the paths stored in the structs of the dwarves to the empty string
	for (i = 0; i < numberofhobbits; i++){
		for (j = 0; j < MAX_COLUMNS; j++){
			homesList[i].path[j] = ' ';
		}
	}
	//bilbo gets set to 0
     dist[bilbo] = 0;
     for (count = 0; count < MAX_COLUMNS; count++){
			//store the minimum distance which will act as X in u
		   int u = minDistance(dist, seen);
		   seen[u] = true;
		   for (v = 0; v < MAX_ROWS; v++)
			 if (!seen[v] && graph[u][v]  && dist[u]+graph[u][v] < dist[v]&& dist[u] != INT_MAX ){
				//anything that satisfies the properties of dijkstra's gets added into the distance array
				dist[v] = dist[u] + graph[u][v];
				for (i = 0; i < MAX_COLUMNS; i++){
					if (pathStored[u][i] != '+'){/* do nothing */}
					else
						//exit the loop cause we don't want to deal with +'s
						break;
						//update the path
						pathStored[v][i] = pathStored[u][i];
				}
			}
			//traverse through the pathStored array
			//if we see the symbol +, we replace it with the vertice we have just seen
			//on the condition that the vertice is not equal to the previous as there are
			//no loops within vertices in this graph.
			for (i = 0; i < MAX_COLUMNS; i++){
				for (j = 0; j< MAX_ROWS; j++){
					if (pathStored[i][j] != '+'){}
					else
						//exit the loop if it's all good, eitherwise keep traversing until we find an empty space aka a +
						break;
					}
					//ensure that the previous isn't being inserted twice.
					if (pathStored[i][j-1] != (char) i + 'A'){
						pathStored[i][j] = (char) i + 'A';
					}
			}
	}
	int k, n, x, y;
	int daddy;
	int found = 0;
	int hob;
	for (i = 0; i < MAX_ROWS; i++){
		for (k = 0; k < numberofhobbits; k++){
			//traverse from 0 to N dwarves and see if the current i matches a dwarf in the struct. if it does
			//we will store that i in a var, and say we found and proceed, eitherwise, the loop ends,
			//and the outer loop increments by 1 repeating the same process. this guarantees that
			//every dwarf in the array has been found.
			if (homesList[k].home == i){
				hob = k;
				found = 1;
			}
			// if the dwarf matched with the current i, we will store their specific path to their own individual struct
			// for easier access when printing.
			if (found == 1){
				found = 0;
				daddy = 0;
				//traverse the path array backwards. if we see a +, don't do anything, eitherwise if we don't, add that vertice
				//to the dwarfs specific path array.
				for (j = (MAX_COLUMNS - 1); j > -1; j--){
					if (pathStored[i][j] != '+'){
						homesList[hob].path[daddy] = pathStored[i][j];
						daddy++;
					}
				}
				//printf("Hobbit %d at vertice %c\n", hob, ((char) i + 'A'));
				//set the destination as the final part of the path
				homesList[hob].path[daddy] = (char) homesList[0].home + 'A';
				//string terminator for fun
				homesList[hob].path[MAX_ROWS] = '\0';
				n = 0;
				// accumulate gold time distance trolls and hops according to the algorithm being used. 
				// ensure that we stop ahead of 1 node if we see a ' ' meaning that the path is done.
				while(homesList[hob].path[n +1] != ' '){
						// x and y are the vertices listed in the path array i.e. if i had VBC, VB would be look at first, then BC. 
						// when the algorithm sees the empty string, it will halt and stop accumulating. 
						// we pull the information from the graphs we got user input from
						x = (int)homesList[hob].path[n]-'A';
						y = (int)homesList[hob].path[n+1]-'A';
						// depending on the algorithm, accumulate the nesserary values into the struct of the dwarf.
						if(algorithm == 1){
							homesList[hob].totaldistance += distance[x][y];
							homesList[hob].totaltime += time[x][y];
							homesList[hob].totalgold += gold[x][y];
							homesList[hob].totaltrolls += trolls[x][y];
						}
						else if (algorithm == 2){
							homesList[hob].totalhops += edge[x][y];
							homesList[hob].totaltime += time[x][y];
							homesList[hob].totalgold += gold[x][y];
							homesList[hob].totaltrolls += trolls[x][y];
						}
						else if (algorithm == 3){
							homesList[hob].totalhops += edge[x][y];
							homesList[hob].totaldistance += distance[x][y];
							homesList[hob].totalgold += gold[x][y];
							homesList[hob].totaltrolls += trolls[x][y];
						}
						else if (algorithm == 4){
							homesList[hob].totalhops += edge[x][y];
							homesList[hob].totaldistance += distance[x][y];
							homesList[hob].totaltime += time[x][y];
							homesList[hob].totalgold += gold[x][y];
						}
						n++;
					}
			}
		}
	}
	//PRINTING YAY!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf("Destination is always Bilbo's home at node %c \n", (char) homesList[0].home + 'A');
	printf("\n");
	printf("Hobbit\tHome\tHops\tDist\tTime\tGold\tTrolls\tPath\n");
	printf("-----------------------------------------------------------------\n");
	int bb;
	int ret;
	// initialize all the averages/totals to 0.
	float averagehops = 0;
	float averagedist = 0;
	float averagetime = 0;
	float averagegold = 0;
	float averagetrolls = 0;
	printf("\n");
		// traverse the dist[i] array to put everything into place.
      for (i = 0; i < MAX_ROWS; i++){
		if (dist[i] != INT_MAX && i != homesList[0].home){
			for ( bb = 0; bb < numberofhobbits; bb++){
				//match up with the dwarfs vertice on the list
				if (homesList[bb].home == i)
					ret = bb;
			}
			// if the dwarf doesn't match, do nothing
			if (homesList[ret].home != i){}
			else{
				// depending on whatever algorithm we are using, 
				// assign dist[i] to the corresponding vairable in the hobbits struct.
				if (algorithm ==1)
					homesList[ret].totalhops = dist[i];
				else if (algorithm == 2)
					homesList[ret].totaldistance = dist[i];
				else if (algorithm == 3)
					homesList[ret].totaltime = dist[i];
				else if (algorithm == 4)
					homesList[ret].totaltrolls = dist[i];
				// add up the the total hops distance time gold and trolls as we traverse through every dwarf
				averagehops +=  homesList[ret].totalhops;
				averagedist += homesList[ret].totaldistance;
				averagetime += homesList[ret].totaltime;
				averagegold += homesList[ret].totalgold;
				averagetrolls += homesList[ret].totaltrolls;
				printf("%s\t%c\t%d\t%d\t%d\t%d\t%d\t%s\n",homesList[ret].hobbitName , (i + 'A'), homesList[ret].totalhops, homesList[ret].totaldistance, homesList[ret].totaltime, homesList[ret].totalgold, homesList[ret].totaltrolls, homesList[ret].path);
			}
		}
	 }
	  // divide by the total number of dwarves - the one hobbit that is bilbo
	  averagehops /= (numberofhobbits - 1);
	  averagedist /= (numberofhobbits - 1);
	  averagetime /= (numberofhobbits - 1);
	  averagegold /= (numberofhobbits - 1);
	  averagetrolls /= (numberofhobbits -1);
	 printf("-----------------------------------------------------------------\n");
	 printf("AVERAGE\t%.2f\t%.1f\t%.1f\t%.1f\t%.1f \n", averagehops, averagedist, averagetime, averagegold, averagetrolls);
}

int main(int argc, char *argv[]){
	//check to see if the user has put in the proper input in the form of
	//the mapfile, homesfile and the algorithm of choice.
	if (argc != 4){
        printf("Syntax: %s mapfile homesfile algorithm\n", argv[0] );
		printf("mapfile is a txt file such as canadamap.txt.\n");
		printf("homesfile is a txt file such as canadahomes.txt.\n");
		printf("Algorithm is an integer ranging from 1 to 4.\n1 invokes SHP, 2 invokes SDP, 3 invokes STP, 4 invokes FTP.\n");
	}
	else{
		FILE *fp1, *fp2;
		int i, j, k;
		int x, y;
		char dwarf[LENGTH_NAME];
		char source, dest, ch, home;
		int distancev, timev, goldv, trollsv, hobbithome;
		char *mapfile = argv[1];
		char *homesfile = argv[2];
		int algorithm = atoi(argv[3]);
		// check to see if a valid algorithm input was put into the program
		if (algorithm < 1 || algorithm > 4){
			printf("Syntax: %s mapfile homesfile algorithm\n", argv[0] );
			printf("mapfile is a txt file such as canadamap.txt.\n");
			printf("homesfile is a txt file such as canadahomes.txt.\n");
			printf("Algorithm is an integer ranging from 1 to 4.\n1 invokes SHP, 2 invokes SDP, 3 invokes STP, 4 invokes FTP.\n");
			exit(0);
		}
		//Initialize all 4 adjacency arrays to infinity for Dijkstra's algorithm.
		for( i = 0; i < MAX_ROWS; i++ ){
			for( j = 0; j < MAX_COLUMNS; j++ ){
				distance[i][j] = 0;
				time[i][j] = 0;
				gold[i][j] = 0;
				trolls[i][j] = 0;
				edge [i][j] = 0;
			}
		}
		/**
		* Open the map file, and load it into memory.
		*/
		fp1 = fopen(mapfile, "r");
		if(fp1 == NULL){
			fprintf(stderr, "%s does not exist in the directory.\n", mapfile);
			exit(1);
		}
		// traverse through every line with 6 characters with spaces in between and put all the inputs in the line into variables
		while((k = fscanf(fp1, "%c %c %d %d %d %d\n", &source, &dest, &distancev, &timev, &goldv, &trollsv)) == 6){
			x = source - 'A';
			y = dest - 'A';
			if( x > MAX_ROWS || y > MAX_COLUMNS ){
				printf("More rows and columns to index that what can be handled by the program\n");
				exit(0);
			}
			// edges
			edge[x][y] = 1;
			edge[y][x] = 1;
			// distance
			distance [x][y] = distancev;
			distance [y][x] = distancev;
			// time
			time [x][y] = timev;
			time [y][x] = timev;
			// gold
			gold [x][y] = goldv;
			gold [y][x] = goldv;
			// trolls
			trolls [x][y] = trollsv;
			trolls [y][x] = trollsv;
		}
		//Done with the file, close it.
		fclose(fp1);
		//Debug display of the adjancancy matrix to see if the loading worked or not.
		/**
		* Open the homes file, and load it into memory.
		*/
		numberofhobbits = 0;
		k = 0;
		fp2 = fopen(homesfile, "r");
		if(fp2 == NULL){
			fprintf(stderr, "%s does not exist in the directory.\n", homesfile);
			exit(1);
		}
		int z = 0;
		// traverse through every line with a string and a character
		while((k = fscanf(fp2, "%s %c\n", dwarf, &home)) == 2){
			hobbithome = home - 'A';
			homesList [numberofhobbits].home = hobbithome;
			char terminate = '\0';
			while (strcmp(&dwarf[z], &terminate) != 0) {
				homesList[numberofhobbits].hobbitName[z] = dwarf[z];
				z++;
			}
			homesList[numberofhobbits].hobbitName[z]  = '\0';
			if(numberofhobbits == MAX_HOBBITS ){
				printf("There are more hobbits then what the program is meant to handle..\n");
				exit(0);
			}
			numberofhobbits ++;
			z = 0;
		}
		//Done with the file, close it.
		fclose(fp2);
		// depending on the algorithm chosen, we input a different array into the path and dijkstra algorithms respectively. 
		if (algorithm == 1){
			printf("Shortest Hop Path (SHP)\n");
			dijkstra(edge, homesList[0].home, algorithm);
		}
		else if (algorithm == 2){
			printf("Shortest Distance Path (SDP)\n");
			dijkstra(distance, homesList[0].home, algorithm);
		}
		else if (algorithm == 3){
			printf("Shortest Time Path (STP)\n");
			dijkstra(time, homesList[0].home, algorithm);
		}
		else if (algorithm == 4){
			printf("Fewest Trolls Path (FTP)\n");
			dijkstra(trolls, homesList[0].home, algorithm);
		}
	}
	return 0;
}