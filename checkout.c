#include <stdio.h>
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

}

/*
	Import whole table into array 30 long
	Prompt for deletion or additon of persons. Print whole list.
		Deletion by vla 3
		Additon by fname, lname
	Update outtab upon new entries or deletions.
*/
