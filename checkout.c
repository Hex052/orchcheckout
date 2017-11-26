#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct instrument {
	char *fname;
	char *lname;
	int num;
	char *type;
}
void blank(const int length, void **array)
{
	for (int i = 0; i < length; i++)
		array[i] = 0;
	return;
}
void println(const struct instrument *in, FILE *printdest)
{
	fprintf(printdest, "%s\t%d\t%s\t%s\n", in->type, in->num, in->lname, in->fname);
	return;
}
void printarr(const struct instrument **arr, FILE *printdest)
{
	for (int i = 0; i < 30; i++)
	{
		if (arr[i] == 0)
			return;
		println(arr[i], printdest);
	}
	return;
}
void addtoarray(struct instrument **array, struct instrument *add)
{
	int i = 0;
	while (array[i] != 0 && i < 30)
		i++
	if (i >= 30)
	{
		fprintf(stderr, "**** ERR: OUT OF MEMORY FOR MORE INSTRUMENTS OF TYPE %s ****", add->type);
		free(add->type);
		free(add->lname);
		free(add->fname);
		free(add);
	}
	else
	{
		array[i] = add;
	}
	return;
}
int main(void)
{

	printf("The outtab file must be located in the same directory as the program, as it stores data about who has checked out what.");
	FILE *outtab = fopen("outtab", "w");
	struct instrument *vln[30], *vla[30], *clo[30], *bas[30];
	blank(30, vla); blank(30, vln); blank(30, clo); blank(30, bas);
	if (outtab == 0)
	{
		printf("   The outtab file could not be opened for reading.");
		exit(1);
	}

	//Import list
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);

	while (feof(outtab) != 0)
	{
		struct instrument *temptostore = malloc(sizeof(struct instrument));
		char *fileline = malloc(80 * sizeof(char));
		ssize_t filelinechars;
		size_t filelinelength = 80;
		filelinechars = getline(&fileline, &filelinelength, outtab)
		if (filelinechars == -1 || fileline[0] == '#' || fileline[0] == '\n')
		{
			free(fileline);
			free(temptostore);
		}
		else
		{
			//Divides outtab by \t, loading into temptostore

			for (int loop = 0; loop < 4; loop ++)
			{
				char *filelinesplit = strtok(fileline, "\t\n");
				char *linecopy = malloc(filelinechars * sizeof(char));
				strcopy(linecopy,filelinesplit);
				//Switch based on order in outtab
				switch (loop)
				{
					case 1:
						temptostore->type = linecopy;
						break;
					case 2:
						temptostore->num = atoi(linecopy);
						free(linecopy);
						break;
					case 3:
						temptostore->lname = linecopy;
						break;
					case 4:
						temptostore->fname = linecopy;
						break;
					default:
						fprintf(stderr, "**** ERR: SPLITTING STRING FAILURE ****");
						break;
				}
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
				fprintf(stderr, "**** ERR: INSTRUMENT TYPE NOT FOUND: %s ****", temptostore->type);
				free(temptostore->type);
				free(temptostore->lname);
				free(temptostore->fname);
				free(temptostore);
			}
		}
	}

}

/*
	Import whole table into array 30 long
	Prompt for deletion or additon of persons. Print whole list.
		Deletion by vla 3
		Additon by fname, lname
	Update outtab upon new entries or deletions.
*/
