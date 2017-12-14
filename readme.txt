structure	type, num, lname, fname
clearline	reads and discards characters until a newline or EOF is reached
updatefile	writes buffer to file, overwriting characters for specified length. To erase without inserting, overwrite should be amount to delete, and size should be 0. Upon exiting, will return the pointer to the same relative location in the file (moved forward if any inserts fell on or before the position) and returns location of pointer.

Considering screwing this on Windows and only writing for Linux

Frequent look-ups
ssize_t getline(char **lineptr, size_t *n, FILE *stream);


TODO: truncate is only in POSIX, a similar thing in Windows would be _chsize
	_chsize( fileno(f), size);
	int ftruncate(int fildes, off_t length);
TODO: Need to update the file after changes are made
TODO: Loop and questions for checkout need finishing
TODO: Fix readentry and integrate into rest of program
