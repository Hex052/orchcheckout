#include <stdio.h>
#define line_size 80
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
typedef signed int ssize_t;
//The getline and getdelim functions are from the GNU standard libraries; I haven't written them.
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream)
{
	size_t indx = 0;
	int c;

	/* Sanity checks.  */
	if (lineptr == NULL || n == NULL || stream == NULL)
		return -1;

	/* Allocate the line the first time.  */
	if (*lineptr == NULL)
	{
		*lineptr = malloc(line_size);
		if (*lineptr == NULL)
			return -1;
		*n = line_size;
	}

	while ((c = getc(stream)) != EOF)
	{
		/* Check if more memory is needed.  */
		if (indx >= *n)
		{
			*lineptr = realloc(*lineptr, *n + line_size);
			if (*lineptr == NULL)
				return -1;
			*n += line_size;
		}

		/* Push the result in the line.  */
		(*lineptr)[indx++] = c;

		/* Bail out.  */
		if (c == delim)
			break;
	}

	/* Make room for the null character.  */
	if (indx >= *n)
	{
		*lineptr = realloc(*lineptr, *n + line_size);
		if (*lineptr == NULL)
			return -1;
		*n += line_size;
	}

	/* Null terminate the buffer.  */
	(*lineptr)[indx++] = 0;

	/* The last line may not have the delimiter, we have to
	* return what we got and the error will be seen on the
	* next iteration.  */
	return (c == EOF && (indx - 1) == 0) ? -1 : indx - 1;
}
ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
	return getdelim(lineptr, n, '\n', stream);
}
#endif
