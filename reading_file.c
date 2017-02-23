#include <stdio.h>
#include <stdlib.h>
#include "reading_file.h"

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


int ReadingFile()
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

	char * sizeVideo[nbVideo];
	indexVideo = 0;
	char nb[50];

	while((current = fgetc(file)) != '\n')
	{
		nb[indexChar] = current;
		if(current == ' ')
		{
			sizeVideo[indexVideo] = nb;
			indexVideo = indexVideo + 1;
			indexChar = 0;
			nb = "";
		}
	}

	

	int endpoint[1000][1000];


	int cache[1000][1000];

	printf("PARAM %s \n", param.nbVideo);
	
	return current;
}


int main (int argc, char *argv[])
{
	ReadingFile();
	return 0;
}
