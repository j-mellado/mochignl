/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:05 by jmellado          #+#    #+#             */
/*   Updated: 2025/04/07 16:56:40 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>  // para abrir un archivo txt
#include <stdio.h>  // para printf y End Of File
#include <stdlib.h> // para malloc
#include <unistd.h> // para read
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	int byte;         // numero de bytes leidos
	char c;           // caracter leido
	char *str_buffer; // linea
	int i;            // iterador
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	i = 0;
	str_buffer = (char *)malloc(10000);
	if (!str_buffer)
		return (NULL);
	byte = read(fd, &c, 1); // cada byte del txt
	while (byte > 0)
	{
		str_buffer[i] = c;
		i++;
		if (c == '\n' || c == EOF)
			break ;
		byte = read(fd, &c, 1);
	}
	if (i == 0 || byte < 0) // no mas char o ocurre un error
	{
		free(str_buffer);
		return (NULL);
	}
	str_buffer[i] = '\0';
	return (str_buffer);
}

int	main(void)
{
	int fd;     // el file descriptor
	char *str;  // aqui guardo lo que devuelve gnl, osea la linea devuelta
	char *path; // laruta hasta el file descriptor
	int i;      // un iterador para el bucle
	path = "test.txt";
	fd = open(path, O_RDONLY);
	i = 0;
	while (i < 10) // test de llamadas recurentes a gnl
	{
		str = get_next_line(fd);
		printf("%i", i);
		printf("%i, %s\n", fd, str);
		i++;
	}
	return (0);
}
