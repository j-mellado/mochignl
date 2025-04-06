/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:33:05 by jmellado          #+#    #+#             */
/*   Updated: 2025/04/02 12:58:01 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // para malloc
#include <stdio.h> // para printf y End Of File
#include <fcntl.h> // para abrir un archivo txt

char *get_next_line(int fd)
{
	int 	byte;
	char 	c;
	char 	*str_buffer;
	int 	i;

	i = 0;
	str_buffer = (char*)malloc(1000000);
	byte = read(fd, &c, 1);
	while (byte > 0)
	{
		str_buffer[i] = c;
		i++;
		if (c == '\n' || c == EOF)
			break;
	}
	

	return("hello 42");
}


int main(void)
{	
	int     fd;
	char	*str;
	char	*path;
	int 	i;

	path = "test.txt";
	fd = open(path, O_RDONLY);
	i = 0;
	while(i < 6) // test de llamadas recurentes a gnl
	{
		str = get_next_line(fd);
		printf("%i", i);
		printf("%i, %s\n",fd,str);
		i++;
	}
	return (0);
}