#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "linux-functions.h"
#define line_size 80
#define max_instruments 30

enum listadvance_type {INVENTORY, CHKOUTNUM, CHKOUTNAME};
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
	struct chkout *namenext;
	struct chkout *nameprev;
	struct chkout *numnext;
	struct chkout *numprev;
};
void *listadvance(void *member, int dist, enum listadvance_type type)
//Pass in starting element, amount to go foreward or back, and type of structure.
//Returns element dist places away, unless end was closer, in which case returns end.
{
	if (type == INVENTORY)
	{
		while (dist > 0)
		{
			if (((struct inventory *)member)->numprev == 0)
			{
				return member;
			}
			member = ((struct inventory *)member)->numprev;
			dist--;
		}
		while (dist < 0)
		{
			if (((struct inventory *)member)->numnext == 0)
			{
				return member;
			}
			member = ((struct inventory *)member)->numnext;
			dist++;
		}
		return member;
	}
	else if (type == CHKOUTNUM)
	{
		while (dist > 0)
		{
			if (((struct chkout *)member)->numprev == 0)
			{
				return member;
			}
			member = ((struct chkout *)member)->numprev;
			dist--;
		}
		while (dist < 0)
		{
			if (((struct chkout *)member)->numnext == 0)
			{
				return member;
			}
			member = ((struct chkout *)member)->numnext;
			dist++;
		}
		return member;
	}
	else if (type == CHKOUTNAME)
	{
		while (dist > 0)
		{
			if (((struct chkout *)member)->nameprev == 0)
			{
				return member;
			}
			member = ((struct chkout *)member)->nameprev;
			dist--;
		}
		while (dist < 0)
		{
			if (((struct chkout *)member)->namenext == 0)
			{
				return member;
			}
			member = ((struct chkout *)member)->namenext;
			dist++;
		}
		return member;
	}
	return 0;
}
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
//IDEA Error checking?
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
	FILE *inventory_stream = 0, *chkout_stream = 0;
	unsigned short inventory_totlines = 0, chkout_totlines = 0, inventory_count = 0, chkout_count = 0;
	char **inventorylines = 0, **chkoutlines = 0;
	struct inventory *inventory_list = 0;
	struct chkout *chkout_listbynum = 0, *chkout_listbyname = 0, **chkout_arrtype = 0;
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
		inventory_stream = fopen("inventory", "r+"); //TODO Create relevant file
		//QUESTION Is the "b" flag needed for Windows / Mac, where newlines are different?
		if (inventory_stream == 0)
		{
			fputs("The file \"inventory\" is not avaliable in the same directory.\n", stderr); //TODO Implement arguments.
			exit(1);
		}
		chkout_stream = fopen("chkout", "r+"); //TODO Create relevant file
		if (chkout_stream == 0)
		{
			fputs("The file \"chkout\" is not avaliable in the same directory.\n", stderr); //TODO Implement arguments.
			exit(1);
		}
	}
	/* Read files */
	inventory_totlines = filelines(inventory_stream, &inventorylines);
	chkout_totlines = filelines(chkout_stream, &chkoutlines);

	/* Intake inventory */
	for (unsigned i = 1; i + 1 <= inventory_totlines; i++) //Starts at 1, since line 0 holds file info, not inventory info. inventory_totlines starts counting from 0 for no lines, but i has 0 as the first line
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
		if (inventory_list == 0)
		{
			inventory_list = item;
			item->numnext = 0;
			item->numprev = 0;
		}
		else
		{
			item->numprev = 0;
			item->numnext = inventory_list;
			inventory_list->numprev = item;
			inventory_list = item;
		}
		free(linestr);
		inventory_count++;
	}

	/* Sort inventory */
	if (inventory_list == 0)
	{
		fputs("There is nothing in the inventory. Please add items before checking anything out.\n", stderr);
	}
	else	//IDEA Better sorting, not insert sort.
	{
		/* Beginning of new list */
		//TODO Is from here to the first strcmp broken?
		struct inventory *new_list = inventory_list;
		new_list->numprev = 0;
		new_list->numnext = 0;
		inventory_list = inventory_list->numnext;

		/* Foreach, insert into new */
		while (inventory_list != 0)
		{
			enum loc {NONE, BEFORE, AFTER};
			enum loc loc = NONE;
			struct inventory *search = new_list, *insert = inventory_list;
			inventory_list->numprev = 0;
			while ((strcmp(insert->type, search->type) > 0) && (search->numnext != 0))
				//Until there is no next or type is equal or less
				search = search->numnext;
			while (strcmp(insert->type, search->type) == 0 && strcmp(insert->num, search->num) > 0 && search->numnext != 0)
				//If same type, proceed foreward until num is less or equal or no next
				search = search->numnext;
			/* Determine if goes before or after search
			 *                       type
			 *               less    equal   greater
			 *      less     BEFORE  BEFORE  AFTER
			 * num	equal    BEFORE  BEFORE  AFTER
			 *      greater  BEFORE  AFTER   AFTER */
			if      (strcmp(insert->type, search->type) < 0) //Smaller type
				loc = BEFORE;
			else if (strcmp(insert->type, search->type) > 0) //Greater type
				loc = AFTER;
			else if (strcmp(insert->num, search->num) > 0) //Equal type, greater num
				loc = AFTER;
			else //Equal type, equal or less num
				loc = BEFORE;
			/* Move into position. Switch statement not used due to incompatability with enum */
			if (loc == BEFORE)
			{
				insert->numnext = search;
				insert->numprev = search->numprev;
				search->numprev = insert;
				if (insert->numprev != 0)
					insert->numprev->numnext = insert;
				if (new_list == insert->numnext) /* If should be first */
					new_list = insert;
			}
			else
			{
				insert->numnext = search->numnext;
				search->numnext = insert;
				insert->numprev = search;
				if (insert->numnext != 0)
					insert->numnext->numprev = insert;
			}
		}
		inventory_list = new_list;
	}

	/* Intake chkout */
	for (unsigned i = 1; i + 1 <= chkout_totlines; i++) //Starts at 1, since line 0 holds file info, not chkout info. chkout_totlines starts counting from 0 for no lines, but i has 0 as the first line
	//TODO This needs to decrement the entries in inventory
	{
		struct chkout *item = malloc(sizeof(struct chkout));
		char *tempstring, *linestr = malloc(strlen(inventorylines[i]) + 3); //Extra two bytes to be sure
		strcpy(linestr, chkoutlines[i]);
		item->linenum = i + 1;
		if (item == 0) //memory allocation error
		{
			fputs("Error allocating memory.\n", stderr);
			exit(2);
		}
		if (linestr[0] == '#') //If the line is a comment, skip it.
			continue;
		/*  Type  */
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0) //Blank line
		{
			free(item);
			continue;
		}
		item->type = malloc(strlen(tempstring));
		strcpy(item->type, tempstring);
		/*  Number  */
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0) //Incomplete line
		{
			free(item->type); free(item);
			continue;
		}
		item->num = malloc(strlen(tempstring));
		strcpy(item->num, tempstring);
		/*  Name  */
		tempstring = strtok(linestr, "\t\n");
		if (tempstring == 0) //Incomplete line
		{
			free(item->type); free(item->num); free(item);
			continue;
		}
		item->name = malloc(strlen(tempstring));
		strcpy(item->name, tempstring);
		/* Add to list */
		if (chkout_listbynum == 0)
		{
			chkout_listbynum = item;
			item->numnext = 0;
			item->numprev = 0;
		}
		else
		{
			item->numprev = 0;
			item->numnext = chkout_listbynum;
			chkout_listbynum->numprev = item;
		}
		free(linestr);
		chkout_count++;
	}

	if (chkout_listbynum == 0)
	{
		printf("There are no instruments checked out right now.");
	}
	else //NOTE stored in chkout_listbynum out of order
	{
		enum loc {NONE, BEFORE, AFTER};
		enum loc loc = NONE;
		struct chkout *tosort, *search, *index;
		chkout_listbyname = chkout_listbynum;
		chkout_listbynum = chkout_listbynum->numnext;
		chkout_listbyname->namenext = 0; chkout_listbyname->nameprev = 0;
		/* Sort chkout by name into chkout_listbyname */
		while (chkout_listbynum != 0)
		{
			tosort = chkout_listbynum;
			search = chkout_listbyname;
			chkout_listbynum = chkout_listbynum->numnext;
			tosort->numnext = 0; tosort->numprev = 0;
			while (strcmp(tosort->name, search->name) > 0 && search->namenext != 0)
				//Until there is no next or type is equal or less
				search = search->namenext;
			if (strcmp(tosort->name, search->name) > 0) //tosort goes after search
			{
				tosort->namenext = search->namenext;
				tosort->nameprev = search;
				search->namenext = tosort;
				if (tosort->namenext != 0)
					tosort->namenext->nameprev = tosort;
			}
			else //tosort is less than or equal, and goes before
			{
				tosort->namenext = search;
				tosort->nameprev = search->nameprev;
				search->nameprev = tosort;
				if (tosort->nameprev != 0)
					tosort->nameprev->namenext = tosort;
				if (tosort->namenext == chkout_listbyname) //If it would go before the first
					chkout_listbyname = tosort;
			}
		}
		/* Sort chkout by num into chkout_listbynum from listbynum */
		chkout_listbynum = chkout_listbyname;
		index = chkout_listbyname->namenext;
		chkout_listbynum->numnext = 0; chkout_listbynum->numprev = 0;
		while (index != 0)
		{
			tosort = index;
			search = chkout_listbynum;
			index = index->namenext;
			while (strcmp(tosort->type, search->type) > 0 && search->numnext != 0)
				//Until there is no next or type is equal or less
				search = search->numnext;
			while (strcmp(tosort->type, search->type) == 0 && strcmp(tosort->num, search->num) > 0 && search->numnext != 0)
				//If same type, proceed foreward until num is less or equal or no next
				search = search->numnext;
			/* Determine if goes before or after search
			 *                        type
			 *               less    equal   greater
			 *      less     BEFORE  BEFORE  AFTER
			 * num	equal    BEFORE  BEFORE  AFTER
			 *      greater  BEFORE  AFTER   AFTER */
			if (strcmp(tosort->type, search->type) < 0)
				//Smaller type
				loc = BEFORE;
			else if (strcmp(tosort->type, search->type) > 0)
				//Greater type
				loc = AFTER;
			else if (strcmp(tosort->num, search->num) > 0)
				//Equal type, greater num
				loc = AFTER;
			else //Equal type, equal or less num
				loc = BEFORE;
			/* Insert in position */
			if (loc == BEFORE)
			{
				tosort->numnext = search;
				tosort->numprev = search->numprev;
				search->numprev = tosort;
				if (tosort->numprev != 0)
					tosort->numprev->numnext = tosort;
				if (tosort->numnext == chkout_listbynum) /* If should be first */
					chkout_listbynum = tosort;
			}
			else
			{
				tosort->numnext = search->numnext;
				search->numnext = tosort;
				tosort->numprev = search;
				if (tosort->numnext != 0)
					tosort->numnext->numprev = tosort;
			}
		}
	}
}
