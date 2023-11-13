#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @s: Source string to duplicate.
 * Return: Pointer to the newly allocated duplicate string.
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	// Get the length of the string
	len = _strlen(s);

	// Allocate memory for the duplicate string
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);

	// Copy the string to the new memory
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Calculates the length of a string.
 * @s: Input string.
 * Return: Length of the string.
 */
int _strlen(const char *s)
{
	int len;

	// Count characters until null terminator
	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - Compares characters in a string with a set of delimiters.
 * @str: Input string.
 * @delim: Set of delimiters.
 * Return: 1 if all characters in str are delimiters, 0 otherwise.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	// Iterate through str to check if all characters are delimiters
	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - Breaks a string into a sequence of tokens.
 * @str: Input string.
 * @delim: Set of delimiters.
 * Return: Pointer to the next token, or NULL if there are no more tokens.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	// Initialize if str is not NULL
	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = splitted;

	// Check if there are more tokens
	if (str_start == str_end)
		return (NULL);

	// Tokenize the string
	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}

	// Check if there are more tokens
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - Checks if a string consists of only digits.
 * @s: Input string.
 * Return: 1 if all characters in s are digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	// Iterate through s to check if all characters are digits
	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
