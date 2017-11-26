#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct instrument {
	char *fname;
	char *lname;
	int num;
	char type[4];
}
int main(void)
{

	printf("The outtab file must be located in the same directory as the program, as it stores data about who has checked out what.");
	FILE *outtab = fopen("outtab", "w");
	struct instrument *vln[31], *vla[31], *clo[31], *bas[31];
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
		if (filelinechars = getline(&fileline, &filelinelength, outtab) == -1)
		{
			free(fileline);
			free(temptostore);
		}
		else
		{
			bool loop = true;
			while (loop)
			{
				char *filelinesplit = strtok(fileline, "\t\n");
				malloc()
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
