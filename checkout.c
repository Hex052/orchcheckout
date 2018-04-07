#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linux-functions.h"
#define line_size 80
#define max_instruments 30

struct inventory {
	unsigned short linenum;
	char *num;
	char *type;
	int count;
	struct inventory *numnext;
	struct inventory *numprev;
};
struct chkout {
	unsigned short linenum;
	char *num;
	char *type;
	char *name;
	struct chkout *linenext;
	struct chkout *lineprev;
	struct chkout *numnext;
	struct chkout *numprev;
};

void clearline(FILE *stream)
{
	int c;
	do
		c = fgetc(stream);
	while (c != '\n' && c != -1);
	return;
}

unsigned filelines(FILE *stream, char ***lines)
//Returns total number of lines read from file
//TODO Error checking?
{
	unsigned read = 0;
	unsigned allocated = 40;
	void *newlines;
	newlines = realloc(*lines, allocated);
	if (newlines == 0)
	{
		fputs("Error allocating memory", stderr);
		exit(2);
	}
	*lines = newlines;
	unsigned i = 0; //Which line to read from
	do
	{
		(*lines)[i] = malloc(sizeof(char) * 80);
		size_t n = 80; //needed for getline, discarded later.
		if (i == 40) //Too few lines allocated. Make larger
		{
			allocated += 40;
			newlines = realloc(*lines, allocated);
			if (newlines == 0)
			{
				fputs("Error allocating memory\n", stderr);
				exit(2);
			}
			*lines = newlines;
		}
		if (getline(&(*lines)[i], &n, stream) == -1)
			free((*lines)[i]);
		else
			read += 1;
		i++;
	}
	while(ferror(stream) != 0);
	return(read);
}

int main(int argc, char *argv[])
{
	FILE *inventorystream = 0, *chkoutstream = 0;
	unsigned short inventorylen = 0, chkoutlen = 0, inventorycount = 0, chkoutcount = 0;
	char **inventorylines = 0, **chkoutlines = 0;
	struct inventory *inventorystart = 0;
	if (inventorylines == 0 || chkoutlines == 0)
	{
		fputs("Error allocating memory.\n", stderr);
		exit (2);
	}
	/* Arguments */
	if (argc > 1)
	{
		//TODO Look for arguments here.
	}
	else
	{
		inventorystream = fopen("inventory", "r+"); //TODO Create relevant file
		if (inventorystream == 0)
		{
			fputs("The file \"inventory\" is not avaliable in the same directory.\n", stderr); //TODO Implement arguments.
			exit(1);
		}
		chkoutstream = fopen("out", "r+"); //TODO Create relevant file
		if (chkoutstream == 0)
		{
			fputs("The file \"chkout\" is not avaliable in the same directory.\n", stderr); //TODO Implement arguments.
			exit(1);
		}
	}
	/* Read files */
	inventorylen = filelines(inventorystream, &inventorylines);
	chkoutlen = filelines(chkoutstream, &chkoutlines);

	/* Intake inventory */
	for (unsigned i = 1; i + 1 <= inventorylen; i++) //Starts at 1, since line 0 holds file info, not inventory info. inventorylen starts counting from 0 for no lines, but i has 0 as the first line
	{
		struct inventory *item = malloc(sizeof(struct inventory));
		char *tempstring, *linestr = malloc(strlen(inventorylines[i]) + 3); //Extra two bytes to be sure
		strcpy(linestr, inventorylines[i]);
		item->linenum = i + 1;
		if (item == 0)
		{
			fputs("Error allocating memory.\n", stderr);
			exit(2);
		}
		if (linestr[0] == '#') //If the line is a comment, skip it.
			continue;
		/*  Type  */
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0)
		{
			free(item);
			continue;
		}
		item->type = malloc(strlen(tempstring));
		strcpy(item->type, tempstring);
		/*  Number  */
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0)
		{
			free(item->type); free(item);
			continue;
		}
		item->num = malloc(strlen(tempstring));
		strcpy(item->num, tempstring);
		/*  Avaliable  */
		strtok(linestr, "\t\n"); //Make column
		strtok(linestr, "\t\n"); //Serial number column
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0)
		{
			free(item->type); free(item->num); free(item);
			continue;
		}
		item->count = atoi(tempstring);
		if (item->count < 0)
		{
			printf("In %s %s, a negative amout are avaliable for checkout. (%i)\n", item->type, item->num, item->count);
			do
			{
				char *line = 0; size_t n = 0;
				puts("Please type the correct number.>");
				getline(&line, &n, stdin);
				item->count = atoi(line);
				free(line);
			} while (item->count < 0);
		}
		if (item->count > 5)
		{
			printf("Item of type \"%s\", numbered \"%s\", can be checked out %i times. If this is intended, ignore this message.\n", item->type, item->num, item->count);
		}
		if (inventorystart == 0)
		{
			inventorystart = item;
			item->numnext = 0;
			item->numprev = 0;
		}
		else
		{
			item->numprev = 0;
			item->numnext = inventorystart;
			inventorystart->numprev = item;
		}
		free(linestr);
		inventorycount++;
	}

	/* Sort inventory */

}
