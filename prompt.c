#include "shell.h"

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the resulting string.
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	// Find the end of the destination string
	for (i = 0; dest[i] != '\0'; i++)
		;

	// Append the source string to the destination
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	// Add null terminator
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - Copies a string.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the resulting string.
 */
char *_strcpy(char *dest, char *src)
{
	size_t a;

	// Copy each character from source to destination
	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 * Return: 0 if equal, positive if s1 > s2, negative if s1 < s2.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	// Compare corresponding characters of both strings
	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	// Return comparison result
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - Locates character in a string.
 * @s: String to search.
 * @c: Character to find.
 * Return: Pointer to the first occurrence of the character or '\0' if not found.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	// Iterate through the string to find the character
	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: String to check.
 * @accept: Set of characters to accept.
 * Return: Number of bytes in the initial segment of s which consist only of bytes from accept.
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	// Iterate through s to find the length of the prefix substring
	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		// Check if the character is in accept
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		// Break if character not in accept
		if (bool == 1)
			break;
	}
	return (i);
}
