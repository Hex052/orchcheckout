structure	type, num, lname, fname
clearline	reads and discards characters until a newline or EOF is reached
updatefile	writes buffer to file, overwriting characters for specified length. To erase without inserting, overwrite should be amount to delete, and size should be 0. Upon exiting, will return the pointer to the same relative location in the file (moved forward if any inserts fell on or before the position) and returns location of pointer.

Considering screwing this on Windows and only writing for Linux

Frequent look-ups
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
int ftruncate(int fildes, off_t length);

List of errors that could result from reading a line:
	SUCCESS	Read was successful
	COMMENT	Line is a comment
	BLANK	Line is blank
	BADTYPE	Unknown type

    -	Number can't ever be 0, since that is the same thing as non-zero characters being in that column


TODO: truncate is only in POSIX, a similar thing in Windows would be _chsize
	_chsize( fileno(f), size);
		or SetEndOfFile
	int ftruncate(int fildes, off_t length);
TODO: Need to update the file after changes are made
TODO: Loop and questions for checkout need finishing
TODO: Fix readentry and integrate into rest of program
TODO: Create enum list for readentry so different read errors can be tracked

TODO: Needed Columns	Type	Num	last	first	PayType	Make/Model	Signed
