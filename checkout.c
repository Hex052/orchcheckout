#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct instrument {
	char *fname;
	char *lname;
	int num;
	char *type;
	bool out;
}
void blank(const int length, void **array)
{
	for (int i = 0; i < length; i++)
		array[i] = 0;
	return;
}
void clearline(FILE *input)
{
	char c;
	do
		c = fgetc(input);
	while (c != '\n');
}
void println(const struct instrument *in, FILE *printdest)
{
	fprintf(printdest, "%s\t%d\t%s\t%s\n", in->type, in->num, in->lname, in->fname);
	return;
}
void printarr(const struct instrument **arr, FILE *printdest, const bool which)
{
	for (int i = 0; i < 30; i++)
	{
		if (arr[i] == 0)
			return;
		if (arr[i]->out = which)
			println(arr[i], printdest);
	}
	return;
}
void addtoarray(struct instrument **array, struct instrument *add)
{
	int i = 0;
	while (array[i] != 0 && i < 30)
	{
		//Check to see if the same instrument is already checked out
		if (array[i]->num == add->num)
		{
			int errcorrectint = 0; struct instrument *errcorrectstruct;
			while (errcorrectint > 2 || errcorrectint < 1)
			{
				printf("Two instruments exist with the same number %d.\n1)\t", add->num);
				println(add, stdout); printf("2)\t"); println(array[i], stdout);
				printf("Which is correct? ");
				errcorrectint = atoi(getchar());
				clearline(stdin);
			}
			if (errcorrectint == 1)
				errcorrectstruct = add;
			else
				errcorrectstruct = array[i];
			printf("What number should \n   "); println(errcorrectstruct, stdout); printf("   be corrected to be? (!!Caution: any number will be accepted, doesn't check for non-numbers!!)");
			char *errcorrectstring = malloc(80 * sizeof(char));
			size_t n = 80;
			getline(&errcorrectstring, &n, stdin);
			errcorrectstruct->num = atoi(errcorrectstring);
			free(errcorrectstring);
		}
		i++
	}
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
struct instrument *locateinarray(int num, struct instrument **array)
{
	//Locate an instrument of a given number in an array
	for (int i = 0; i < 30 && array[i] != 0; i++)
	{
		if (array[i]->num == num)
			return array[i];
	}
	//If reaches here, none match in array.
	return 0;
}
int main(void)
{

	printf("The outtab file must be located in the same directory as the program, as it stores data about who has checked out what.");
	FILE *outtab = fopen("outtab", "w");
	struct instrument *vln[30], *vla[30], *clo[30], *bas[30];
	blank(30, vla); blank(30, vln); blank(30, clo); blank(30, bas);
	if (outtab == 0)
	{
		printf("**** ERR: UNABLE TO OPEN \"outtab\" for reading ****");
		exit(1);
	}

	//Import list
	//ssize_t getline(char **lineptr, size_t *n, FILE *stream);
	int linenum = 0;
	while (feof(outtab) != 0)
	{
		struct instrument *temptostore = malloc(sizeof(struct instrument));
		temptostore->out = true; temptostore->lname = 0; temptostore->fname = 0; temptostore->type = 0; temptostore->num = 0;
		char *fileline = malloc(80 * sizeof(char));
		ssize_t filelinechars;
		size_t filelinelength = 80;
		filelinechars = getline(&fileline, &filelinelength, outtab);
		linenum++;
		if (filelinechars == -1 || fileline[0] == '#' || fileline[0] == '\n')
		{
			//free(fileline);
			free(temptostore);
		}
		else
		{
			//Divides outtab by \t, loading into temptostore
			char *filelinesplit = strtok(fileline, "\t\n");
			for (int loop = 0; loop < 4; loop ++)
			{
				char *linecopy = malloc(filelinechars * sizeof(char));
				strcopy(linecopy,filelinesplit);
				//If splitting results in nothing, mark entry as checked out or discard line
				if (filelinesplit[0] == '\0')
				{
					if (loop > 1)
					{
						temptostore->out = false;
					}
					else if (loop = 1)
					{
						free(temptostore->type);
					}
					free(linecopy);
					loop = 7;
					break;
				}
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
					case 7:
						break;
					default:
						fprintf(stderr, "**** ERR: SPLITTING STRING ****");
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
				fprintf(stderr, "**** ERR: INSTRUMENT TYPE NOT FOUND: %s ****", temptostore->type);
				free(temptostore->type);
				free(temptostore->lname);
				free(temptostore->fname);
				free(temptostore);
			}
			free(fileline);
		}
	}
	fclose(outtab);

	//Make changes to check in/out lists
	fprintf(stdout, "The current checkouts are as follows:\n");
	printarr(vln, stdout, true); printarr(vla, stdout, true); printarr(clo, stdout, true); printarr(bas, stdout, true);
	fprintf(stdout, "The current checkins are as follows:\n");
	printarr(vln, stdout, false); printarr(vla, stdout, false); printarr(clo, stdout, false); printarr(bas, stdout, false);

}

/*
	Import whole table into array 30 long
	Prompt for deletion or additon of persons. Print whole list.
		Deletion by vla 3
		Additon by fname, lname
	Update outtab upon new entries or deletions.
*/
