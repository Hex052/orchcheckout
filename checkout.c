#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linux-functions.h"
#define line_size 80
#define max_instruments 30

struct content {
	unsigned short linenum;
	char *num;
	struct content *next;
	struct content *prev;
};
struct checkout {
	unsigned short linenum;
	char *num;
	char *name;
	struct content *linenext;
	struct content *lineprev;
	struct content *numnext;
	struct content *numprev;
};

void clearline(FILE *stream)
{
	int c;
	do
		c = fgetc(stream);
	while (c != '\n' && c != -1);
	return;
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		//TODO: Look for arguments here.
	}


	/*
	size_t linenum = 0;
	while (true)
	{
		struct instrument *temptostore = malloc(sizeof(struct instrument));
		temptostore->out = true; temptostore->lname = 0; temptostore->fname = 0; temptostore->type = 0; temptostore->num = 0;
		char *fileline = malloc(80 * sizeof(char));
		size_t filelinechars, filelinelength = 80;
		filelinechars = getline(&fileline, &filelinelength, outtab);
		linenum++;
		if (filelinechars == EOF || fileline[0] == '#' || fileline[0] == '\n')
		{
			//free(fileline);
			free(temptostore);
		}
		else
		{
			//Divides outtab by \t, loading into temptostore
			char *filelinebegin = fileline, *filelinesplit = strtok(fileline, "\t\n");
			for (int column = 1; column < 5; column++) //Loop counts column of outtab
			{
				char *linecopy = malloc(filelinechars * sizeof(char));
				strcopy(linecopy,filelinesplit);
				//If splitting results in nothing, mark entry as checked out or discard line
				if (filelinesplit[0] == '\0')
				{
					if (column > 1)
					{
						temptostore->out = false;
					}
					else if (column = 1)
					{
						free(temptostore->type);
					}
					free(linecopy);
					column = 7;
					break;
				}
				//Switch based on order in outtab
				switch (column)
				{
					case 1:
						temptostore->type = linecopy;
						break;
					case 2:
						temptostore->num = atoi(linecopy);
						//Ensure sane instrument numbers (ie > 0)
						if (temptostore->num < 1)
						{
							fprintf(stderr,"**** ERR: ABNORMAL INSTRUMENT NUMBER - LINE %d ****", linenum);
							free(temptostore->type);
							free(temptostore);
						}
						free(linecopy);
						break;
					case 3:
						temptostore->lname = linecopy;
						break;
					case 4:
						temptostore->fname = linecopy;
						break;
					case 7:
						break;
					default:
						fprintf(stderr, "**** ERR: SPLITTING STRING - LINE %d ****", linenum);
						break;
				}
				filelinesplit = strtok(NULL, "\t\n");
			}
			if (strcmp("vln", temptostore->type) == 0)
				addtoarray(vln, temptostore);
			else if (strcmp("vla", temptostore->type) == 0)
				addtoarray(vla, temptostore);
			else if (strcmp("clo", temptostore->type) == 0)
				addtoarray(clo, temptostore);
			else if (strcmp("bas", temptostore->type) == 0)
				addtoarray(bas, temptostore);
			else
			{
				fprintf(stderr, "**** ERR: INSTRUMENT TYPE NOT FOUND: %s - LINE %d ****", temptostore->type, linenum);
				free(temptostore->type);
				free(temptostore->lname);
				free(temptostore->fname);
				free(temptostore);
			}
			free(filelinebegin);
		}
	}
	//fclose(outtab);

	//Make changes to check in/out lists
	fprintf(stdout, "The current checkouts are as follows:\n");
	printarr(vln, stdout, true); printarr(vla, stdout, true); printarr(clo, stdout, true); printarr(bas, stdout, true);
	fprintf(stdout, "The current checkins are as follows:\n");
	printarr(vln, stdout, false); printarr(vla, stdout, false); printarr(clo, stdout, false); printarr(bas, stdout, false);

	bool contloop = true, save = true;
	while (contloop)
	{

		printf("Checkout (o), Checkin (i), Reprint (r), Quit (q), Advanced (~)");
		switch(getchar())
		{
			case 'o':
			case 'O':
			{
				struct instrument *temptoinsert = malloc(sizeof(struct instrument));
				clearline(stdin); //Ensure stdin has no trailing newline
				printf("Instrument type and num to check out");
				char *fileline = malloc(80 * sizeof(char));
				ssize_t filelinechars;
				size_t filelinelength = 80;
				filelinechars = getline(&fileline, &filelinelength, stdin);
				if (filelinechars == -1) //If something wrong happened, notify user and break switch
				{
					printf("Something has gone wrong reading the line, please try again.");
					break;
				}
				char *filelinesplit = strtok(fileline, "\t\n");
				struct instrument **array = 0;
				//Find correct array - Braces to be able to collapse section
				{
					//Determine array the instrument needs to go into
					if (strcmp(filelinesplit, "vln") == 0)
						array = vln;
					else if (strcmp(filelinesplit, "vla") == 0)
						array = vla;
					else if (strcmp(filelinesplit, "clo") == 0)
						array = clo;
					else if (strcmp(filelinesplit, "bas") == 0)
						array = bas;
					else
					{
						printf("Instrument type not found: %s\n", filelinesplit);
						break;
					}
				}
				filelinechars = strtok(NULL, "\t\n");
				int instrumentnum = atoi(filelinechars);

				char *linecopy = malloc(filelinechars * sizeof(char));
			}
			case '~':
			{
				printf("Add instrument (a), Delete instrument (d), Change make/model (m)");
				switch (getchar());
				case 'a':
				case 'A':
				{
					char *line = malloc(line_size * sizeof(char));
					fseek(outtab, 0, SEEK_END);
					printf("What is the instrument type and number? (type, num) > ");

				}
			}
		}
	}*/
}
/*
	Import whole table into array 30 long
	Prompt for deletion or additon of persons. Print whole list.
		Deletion by vla 3
		Additon by fname, lname
	Update outtab upon new entries or deletions.
*/
