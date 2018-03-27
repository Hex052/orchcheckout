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
	unsigned short inventorylen = 0, chkoutlen = 0;
	char **inventorylines = 0, **chkoutlines = 0;
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

	/* Sort inventory */

}
