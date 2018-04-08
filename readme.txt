structure	type, num, lname, fname
clearline	reads and discards characters until a newline or EOF is reached
updatefile	writes buffer to file, overwriting characters for specified length. To erase without inserting, overwrite should be amount to delete, and size should be 0. Upon exiting, will return the pointer to the same relative location in the file (moved forward if any inserts fell on or before the position) and returns location of pointer.

Considering screwing this on Windows and only writing for Linux

Frequent look-ups
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int ftruncate(int fildes, off_t length);
strtok splits strings.

My functions:
unsigned filelines(FILE *stream, char ***lines) //Returns total number of lines read from file
void *listadvance(void *member, int dist, enum listadvance_type type)
//Pass in starting element, amount to go foreward or back, and type of structure.
//Returns element dist places away, unless end was closer, in which case returns end.

List of errors that could result from reading a line:
	SUCCESS	Read was successful
	COMMENT	Line is a comment
	BLANK	Line is blank
	BADTYPE	Unknown type

    -	Number can't ever be 0, since that is the same thing as non-zero characters being in that column


TODO: Needed Columns	Type	Num	Last	First	PayType	Make/Model	Signed
