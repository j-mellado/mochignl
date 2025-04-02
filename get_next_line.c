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

#include "get_next_line.h"

char* get_next_line(int fd)
{
	char buffer[BUFFER_SIZE + 1]; // creo un array de tamaño BUFERSIZE +1 para el /0
	char line[BUFFER_SIZE + 1]; // creo un array de tamaño BUFERSIZE +1 para el /0 que es el que voy a devolver
	size_t i;

	i = 0; //iterador para recorrer los arrays

	if (fd == -1)  // comprobamos que FD no sea -1 (caso de error)
		return (NULL);

	while (read(fd,buffer[i],1) > 0 ) // lo que devuelve read no sea ni 0 (final de documento) o -1 (error) mientras se guarda en buffer el contenido
	{
		if (buffer[i] == "\n")
		{
			buffer[i+1] == "\0";
			ft_strlcpy(line,buffer,i+1);
			
			return (line); 
		}
		i++;
	}
	return (NULL); // controla el 0 y el -1 de read
}
