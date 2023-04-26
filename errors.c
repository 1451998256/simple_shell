#include "shell.h"

/**
 * _eputs - prints a string to standard error
 * @str: the string to be printed
 *
 * Return: void
 */
void _eputs(char *str)
{
	if (!str)
		return;
	while (*str)
	{
		_eputchar(*str);
		str++;
	}
}

/**
 * _eputchar - writes a character to standard error
 * @c: the character to be written
 *
 * Return: On success, 1 is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes a character to a file descriptor
 * @c: the character to be written
 * @fd: the file descriptor to write to
 *
 * Return: On success, 1 is returned.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints a string to a file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters printed
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (count);
	while (*str)
	{
		count += _putfd(*str, fd);
		str++;
	}
	return (count);
}
