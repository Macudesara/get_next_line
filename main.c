/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sara <mde-sara@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:32 by mde-sara          #+#    #+#             */
/*   Updated: 2023/10/20 11:48:24 by mde-sara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	//char arr[] = "HOLA";

	//char res = strlen(arr);
	//char res2 = ft_strlen(arr);
	//printf("%d\n%d\n", res, res2);
	// Abre el archivo que deseas leer
	fd = open("test3.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	// Llama a la función get_next_line para leer líneas del archivo
	int i = -1;
	while (++i < 8)
	{
		line = get_next_line(fd);
		//printf("Línea leída: %s\n", line);
		printf("%s", line);
		free(line);
	}

	// Cierra el archivo
	close(fd);
	return (0);
}
