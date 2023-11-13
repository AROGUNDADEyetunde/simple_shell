#include "shell.h"

/**
 * rev_string - Reverses a string in-place.
 * @s: String to be reversed.
 * Return: void
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	// Count the number of characters in the string
	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	// Swap characters to reverse the string
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}