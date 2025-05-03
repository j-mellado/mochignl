/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmellado <jmellado@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:08:27 by jmellado          #+#    #+#             */
/*   Updated: 2025/05/03 19:45:20 by jmellado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n') // mientras exista un dato en buffer y no sea un salto de linea iteramos
		i++;
	if (!buffer[i])    // si no existe dato (caso eof)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char)); // reservamos espacio para la longuitud de buffer - la linea contando null
	i++;
	j = 0;
	while (buffer[i]) // mientras exista algo en buffer
		line[j++] = buffer[i++]; // copiamos los caracteres restantes de buffer en line
	free(buffer);
	return (line); // devolvemos todos los datos restantes
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n') //mientras exista un dato en buffer y no sea un salto de pagina
		i++;
	line = ft_calloc(i + 2, sizeof(char)); // reservamos el espacio para la linea completa
	i = 0;								   // reiniciamos el iterador
	while (buffer[i] && buffer[i] != '\n') // mientras esxista un dato en buffer y no sea salto de linea
	{
		line[i] = buffer[i];               // almacenamos la linea en line
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')    // si hemos llegado al salto de linea
		line[i++] = '\n';                  //ponemos el salto de linea en line y salimos del bucle despues
	return (line);                         // devolvemos una linea completa
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1); // Inicio el espacio de memoria para el resto
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // inicio el espacio de memoria para el contenido del txt
	byte_read = 1; //flag para que empiece la primera ejecucion
	while (byte_read > 0) //Mientras que tengamos algo leido
	{
		byte_read = read(fd, buffer, BUFFER_SIZE); // lee el fd guardalo en buffer la cantidad de buffer_size (tiene un puntero que se va moviendo cada vez que se llama)
		if (byte_read == -1) // si el read fallaa
		{
			free(res);
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0; // en buffer cantidad total de datos leidos pon un null
		res = ft_free(res, buffer); // en res guardamos buffer
		if (ft_strchr(buffer, '\n')) // si en buffer hay un salto de linea paramos el while
			break ;
		if (byte_read < BUFFER_SIZE) // si lop que hemos leido es menor que el maximo que leemos de golpe (significa que es EOF)
			return (free(buffer), res); //libera buffer y devuelve ress
	}
	free(buffer); // Si nos salimos del while liberamos buffer
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer); //buffer es los datos leidos
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);  // Line contiene una unica liena completa
	buffer = ft_next(buffer); // buffer tiene todo lo que no es line guardado de forma estatica, ya line no existe dentro de buffer
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*next_line;
	int		count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, next_line);
		next_line = NULL;
		free(next_line);
	}
	close(fd);
	return (0);
}
*/
