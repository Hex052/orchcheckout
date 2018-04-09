Considering screwing this on Windows and only writing for Linux

Frequent look-ups  
```
ssize_t getline(char **lineptr, size_t *n, FILE *stream);  
int ftruncate(int fildes, off_t length);  
strtok splits strings.  
```

My functions:  
```
clearline (FILE *stream) //reads and discards characters until a newline or EOF is reached
unsigned filelines(FILE *stream, char ***lines) //Returns total number of lines read from file  
void *listadvance(void *member, int dist, enum listadvance_type type)  
//Pass in starting element, amount to go foreward or back, and type of structure.  
//Returns element dist places away, unless end was closer, in which case returns end.  
```

Exit codes:  
* 1 : Files not found TODO remove this  
* 2 : Memory allocation error  
* 3 : Couldn't sort a list  

TODO: Needed Columns	Type	Num	Last	First	PayType	Make/Model	Signed
