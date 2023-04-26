#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise,
 *         -1 on error.
 */
int _erratoi(char *s)
{
   int i = 0;
   unsigned long int result = 0;

   if (*s == '+')
           s++;

   for (i = 0; s[i] != '\0'; i++)
   {
       if (s[i] >= '0' && s[i] <= '9')
           {
           result *= 10;
           result += (s[i] - '0');
           if (result > INT_MAX)
               return (-1);
	  }
       else
           return (-1);
   }
   return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: void
 */
void print_error(info_t *info, char *estr)
{
   _eputs(info->fname);
   _eputs(": ");
   print_d(info->line_count, STDERR_FILENO);
   _eputs(": ");
   _eputs(info->argv[0]);
   _eputs(": ");
   _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - function converts a number to a string in the specified base
 * @num: the number to convert
 * @base: the base to convert to
 * @flags: flags to apply to conversion (CONVERT_UNSIGNED, CONVERT_LOWERCASE)
 *
 * Return: pointer to converted string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char *ptr;
	unsigned long n = num;
	char array[16];

	if (flags & CONVERT_LOWERCASE)
	{
		array[0] = '0'; array[1] = '1'; array[2] = '2'; array[3] = '3';
		array[4] = '4'; array[5] = '5'; array[6] = '6'; array[7] = '7';
		array[8] = '8'; array[9] = '9'; array[10] = 'a'; array[11] = 'b';
		array[12] = 'c'; array[13] = 'd'; array[14] = 'e'; array[15] = 'f';
	}
	else
	{
		array[0] = '0'; array[1] = '1'; array[2] = '2'; array[3] = '3';
		array[4] = '4'; array[5] = '5'; array[6] = '6'; array[7] = '7';
		array[8] = '8'; array[9] = '9'; array[10] = 'A'; array[11] = 'B';
		array[12] = 'C'; array[13] = 'D'; array[14] = 'E'; array[15] = 'F';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		*--ptr = '-';
	}
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: void
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
