#include <stdio.h>
#include <stdlib.h>
#include "reading_file.h"
#include <string.h>

struct general
{
   char nbVideo[50];
   char nbEndpoint[50];
   char nbRequest[50];
   char nbCache[50];
   char capacityCache[50];
};
typedef struct general general;



typedef enum { False, True } Boolean;


ret *ReadingFile()
{
	general param;
	int check = 0;
	int indexStore = 0;
	int current = 0;
	// check si le fichier s'ouvre correctement
	FILE *file = fopen("kittens.in", "r");
	if(file == NULL)
	{
		printf("ERREUR - le fichier ne s'ouvre pas correctement\n\n");
	}

	while((current = fgetc(file)) != '\n') // première ligne
	{
		if(current == ' ')
		{
			check = check + 1;
			indexStore = 0;
			continue;
		}
		if(check == 0)
		{
			param.nbVideo[indexStore] = current; 
			indexStore = indexStore + 1;
		}
		if(check == 1)
		{
			param.nbEndpoint[indexStore] = current; 
			indexStore = indexStore + 1;
		}
		if(check == 2)
		{
			param.nbRequest[indexStore] = current; 
			indexStore = indexStore + 1;
		}
		if(check == 3)
		{
			param.nbCache[indexStore] = current; 
			indexStore = indexStore + 1;
		}
		if(check == 4)
		{
			param.capacityCache[indexStore] = current; 
			indexStore = indexStore + 1;
		}
	}

	char *sizeVideo[atoi(param.nbVideo)]; // contient la deuxième ligne
	int indexVideo = 0;
	int indexChar = 0;
	char nb[5];


	while((current = fgetc(file)) != '\n')
	{
		if(current == ' ')
		{
			sizeVideo[indexVideo] = nb;
			indexVideo = indexVideo + 1;

			printf("%s\n", nb);
			indexChar = 0;
			for (int x = 0; x < 5; x++)
			{
				nb[x] = ' ';
			}
			continue;
		}
		if(indexChar == 3)
		{
			continue;
		}
		nb[indexChar] = current;
		indexChar = indexChar  + 1;
	}

	char Ld[4];
	char K[strlen(param.nbCache)];
	int indexLd = 0;
	int indexK = 0;


	while((current = fgetc(file)) != ' ')
	{
		Ld[indexLd] = current;
		indexLd = indexLd + 1;
	}

	while((current = fgetc(file)) != '\n')
	{
		K[indexK] = current;
		indexK = indexK + 1;
	}

	printf("LD : %s\nK : %s\n", Ld, K);

	ret r;
	r.nbVideo = atoi(param.nbVideo);
	r.nbEndpoint = atoi(param.nbEndpoint);
	r.nbRequest = atoi(param.nbRequest);
	r.nbCache = atoi(param.nbCache);
	r.capacityCache = atoi(param.capacityCache);

	double latencyCache[r.nbEndpoint][r.nbCache]; 
	double latencyData[r.nbEndpoint];

	for(int i = 0; i < r.nbEndpoint; i++)
	{
		latencyData[i] = 0;
		for(int j = 0; j < r.nbCache; j++)
		{
			latencyCache[i][j] = 0;
		}
	}

	int nbConnections;
	int idCache;
	for (int i = 0; i < r.nbEndpoint; i++)
	{
		nbConnections = 0;
		fscanf(file, "%lf %d\n", &latencyData[i], &nbConnections);
		for (int j = 0; j < nbConnections; j++)
		{
			idCache = 0;
			fscanf(file, "%d", &idCache);
			fscanf(file, "%lf", &latencyCache[i][idCache]);
		}
	}

	double request[r.nbVideo][r.nbRequest];
	for(int i = 0; i < r.nbVideo; i++)
	{
		for(int j = 0; j < r.nbRequest; j++)
		{
			request[i][j] = 0;
		}
	}
	int n;
	int idVideo;
	int idEndpoint;

	for (int i = 0; i < r.nbRequest; i++)
	{
		n = 0;
		idVideo = 0;
		idEndpoint = 0;
		fscanf(file, "%d %d %d\n", &n, &idVideo, &idEndpoint);
		request[idEndpoint][idVideo] = n;
	}



	r.latencyCache = latencyCache;
	r.latencyData = latencyData;
	r.request = request;


	printf("PARAM %s \n", param.nbVideo);
	printf("PARAM %s \n", param.nbEndpoint);
	printf("PARAM %s \n", param.nbRequest);
	printf("PARAM %s \n", param.nbCache);
	printf("PARAM %s \n", param.capacityCache);
	
	return r;
}


int main (int argc, char *argv[])
{
	ReadingFile();
	return 0;
}
