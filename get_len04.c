#include "shell.h"

/**
 * get_len - Calculates the length of an integer.
 * @n: Input integer.
 * Return: Length of the integer.
 */
int get_len(int n)
{
	unsigned int n1;
	int length = 1;

	// Adjust length for negative numbers
	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	// Calculate the length of the integer
	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}

/**
 * aux_itoa - Converts an integer to a string.
 * @n: Input integer.
 * Return: Pointer to the resulting string.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int length = get_len(n);
	char *buffer;

	// Allocate memory for the string representation of the integer
	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	// Adjust for negative numbers
	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	length--;

	// Convert the integer to string
	do {
		*(buffer + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	} while (n1 > 0);

	return (buffer);
}

/**
 * _atoi - Converts a string to an integer.
 * @s: Input string.
 * Return: Resulting integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	// Process each character in the string
	while (*(s + count) != '\0')
	{
		// Break if non-digit character is encountered after processing digits
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		// Handle sign
		if (*(s + count) == '-')
			sign *= -1;

		// Process digits
		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			// Adjust multiplier for each digit
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	// Calculate the integer value
	for (i = count - size; i < count; i++)
	{
		result = result + ((*(s + i) - '0') * multiplier);
		multiplier /= 10;
	}
	
	// Apply sign
	return (result * sign);
}
