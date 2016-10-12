/**
* Assignment 3
* CPSC 441
* Mateo Zoto / 10082263
* Dijkstra's, minDistance and Path algorithms based of http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
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
	
int numberofhobbits = 0;
int distance[MAX_ROWS][MAX_COLUMNS];
int time [MAX_ROWS][MAX_COLUMNS];
int gold [MAX_ROWS][MAX_COLUMNS];
int trolls [MAX_ROWS][MAX_COLUMNS];
int edge [MAX_ROWS][MAX_COLUMNS];

int minDistance(int dist[], bool sptSet[]){
   int v;
   int min = INT_MAX, min_index;
   for (v = 0; v < MAX_ROWS; v++)
     if (sptSet[v] == false && dist[v] < min)
         min = dist[v], min_index = v;
   return min_index;
}

void findPath(int graph[MAX_ROWS][MAX_COLUMNS], int src, int dwarfhome, int hobbitindex, int algorithm){
	int y, x, i, ctr;
	char currentVertice[MAX_ROWS], pathNodes[MAX_ROWS];
	bool visited[MAX_ROWS];
	int desti[MAX_ROWS];
	bool finished = false;
	for(i = 0; i < MAX_ROWS; i++){
		desti[i] = INT_MAX;
		visited[i] = false;
		pathNodes[i] = ' ';
		homesList[hobbitindex].path[i] = ' ';
	}
	desti[src] = 0;
	for(ctr = 0; ctr < MAX_ROWS; ctr++){
		x = minDistance(desti, visited);
		visited[x] = true;
		if(desti[x] == INT_MAX)
			break;
		for(y = 0; y < MAX_ROWS; y++){
			if(!visited[y] && desti[x] != INT_MAX && graph[x][y] && desti[x] + graph[x][y] < desti[y] && graph[x][y] != '0'){
				desti[y] = desti[x] + graph[x][y];
				currentVertice[ctr] = (char)y+'A';
				if(currentVertice[ctr] == (char)dwarfhome+'A'){
					pathNodes[ctr] = (char)x+'A';
					pathNodes[ctr+1] = (char)dwarfhome+'A';
					finished = true;
					break;
				}
				else{
					pathNodes[ctr] = (char)x+'A';
				}
			}
			if(finished == true){
				break;
			}
		}
	}
	int n = 0;
	for( i = 0; i < MAX_ROWS; i++){
		if(pathNodes[i] == ' '){}
		else{
			homesList[hobbitindex].path[n] = pathNodes[i];
			n++;
		}
	}
	homesList[hobbitindex].path[MAX_ROWS] = '\0';
	n = 0;
	while(homesList[hobbitindex].path[n] != ' '){
			x = (int)homesList[hobbitindex].path[n]-'A';
			y = (int)homesList[hobbitindex].path[n+1]-'A';
			if(algorithm == 1){
				homesList[hobbitindex].totaldistance += distance[x][y];
				homesList[hobbitindex].totaltime += time[x][y];
				homesList[hobbitindex].totalgold += gold[x][y];
				homesList[hobbitindex].totaltrolls += trolls[x][y];
			}
			else if (algorithm == 2){
				homesList[hobbitindex].totalhops += edge[x][y];
				homesList[hobbitindex].totaltime += time[x][y];
				homesList[hobbitindex].totalgold += gold[x][y];
				homesList[hobbitindex].totaltrolls += trolls[x][y];
			}
			else if (algorithm == 3){
				homesList[hobbitindex].totaldistance += distance[x][y];
				homesList[hobbitindex].totalhops += edge[x][y];
				homesList[hobbitindex].totalgold += gold[x][y];
				homesList[hobbitindex].totaltrolls += trolls[x][y];
			}
			else if (algorithm == 4){
				homesList[hobbitindex].totaldistance += distance[x][y];
				homesList[hobbitindex].totaltime += time[x][y];
				homesList[hobbitindex].totalgold += gold[x][y];
				homesList[hobbitindex].totalhops += edge[x][y];
			}
			n++;
		}
		
}

void dijkstra(int graph[MAX_ROWS][MAX_COLUMNS], int src, int algorithm){
     int dist[MAX_ROWS];  
     bool sptSet[MAX_ROWS];
	 int i, count, v;
     for (i = 0; i < MAX_ROWS; i++){
        dist[i] = INT_MAX, sptSet[i] = false;
	}
     dist[src] = 0;
     for (count = 0; count < MAX_ROWS; count++){
		   int u = minDistance(dist, sptSet);
		   sptSet[u] = true;
		   for (v = 0; v < MAX_ROWS; v++)
			 if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
			}
	}
	printf("Hobbit\tHome\tHops\tDist\tTime\tGold\tTrolls\tPath\n");
	printf("-----------------------------------------------------------------\n");
	int bb;
	int ret;
	printf("\n");
      for (i = 0; i < MAX_ROWS; i++){
		if (dist[i] != INT_MAX && i != homesList[0].home){
			for ( bb = 0; bb < numberofhobbits; bb++){
				if (homesList[bb].home == i)
					ret = bb;
			}
			if (homesList[ret].home != i){}
			else{
				if (algorithm ==1)
					homesList[ret].totalhops = dist[i];
				else if (algorithm == 2)
					homesList[ret].totaldistance = dist[i];
				else if (algorithm == 3)
					homesList[ret].totaltime = dist[i];
				else if (algorithm == 4)
					homesList[ret].totaltrolls = dist[i];
				printf("%s\t%c\t%d\t%d\t%d\t%d\t%d\t%s\n",homesList[ret].hobbitName , (i + 'A'), homesList[ret].totalhops, homesList[ret].totaldistance, homesList[ret].totaltime, homesList[ret].totalgold, homesList[ret].totaltrolls, homesList[ret].path);
			}
			}
	  }
	 printf("-----------------------------------------------------------------\n");
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
		if (algorithm == 1){
			printf("Shortest Hop Path (SHP)\n");
			int ii = 0;
			for (i = 1; i < numberofhobbits; i++){
				findPath(edge, homesList[i].home, homesList[0].home, i, algorithm);
			}
			dijkstra(edge, homesList[0].home, algorithm);
		}
		else if (algorithm == 2){
			printf("Shortest Distance Path (SDP)\n");
			for (i = 1; i < numberofhobbits; i++){
				findPath(distance, homesList[i].home, homesList[0].home, i, algorithm);
			}
			dijkstra(distance, homesList[0].home, algorithm);
		}
		else if (algorithm == 3){
			printf("Shortest Time Path (STP)\n");
			for (i = 1; i < numberofhobbits; i++){
				findPath(time, homesList[i].home, homesList[0].home, i, algorithm);
			}
			dijkstra(time, homesList[0].home, algorithm);
		}
		else if (algorithm == 4){
			printf("Fewest Trolls Path (FTP)\n");
			for (i = 1; i < numberofhobbits; i++){
				findPath(trolls, homesList[i].home, homesList[0].home, i, algorithm);
			}
			dijkstra(trolls, homesList[0].home, algorithm);
		}
	}
	return 0;
}