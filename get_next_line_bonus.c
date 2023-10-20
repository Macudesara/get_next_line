/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sara <mde-sara@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:14:45 by mde-sara          #+#    #+#             */
/*   Updated: 2023/10/20 11:19:31 by mde-sara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_storage(char **storage)
{
	if (storage != NULL && *storage != NULL)
	{
		free(*storage);
		*storage = NULL;
	}
	return (NULL);
}

char	*ft_cleanstorage(char *storage)
{
	int		i;
	int		j;
	char	*new_storage;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free_storage(&storage));
	new_storage = (char *)malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!new_storage)
		return (free_storage(&storage));
	i++;
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free_storage(&storage);
	return (new_storage);
}

char	*ft_getlines(char *storage, int i)
{
	char	*newmemory;

	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	newmemory = (char *)malloc((i + 1) * sizeof(char));
	if (!newmemory)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		newmemory[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		newmemory[i] = storage[i];
		i++;
	}
	newmemory[i] = '\0';
	return (newmemory);
}

char	*ft_readlines(int fd, char *storage)
{
	char	*storagememory;
	int		nbytes;

	storagememory = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!storagememory)
		return (free_storage(&storage));
	nbytes = 1;
	while (!ft_strchr(storage, '\n') && nbytes != 0)
	{
		nbytes = read(fd, storagememory, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free_storage(&storage);
			free_storage(&storagememory);
			return (NULL);
		}
		storagememory[nbytes] = '\0';
		storage = ft_strjoin(&storage, storagememory);
	}
	free_storage(&storagememory);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (storage[fd] == NULL || !ft_strchr(storage[fd], '\n'))
		storage[fd] = ft_readlines(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = ft_getlines(storage[fd], 0);
	if (!line)
		return (free_storage(&storage[fd]));
	storage[fd] = ft_cleanstorage(storage[fd]);
	return (line);
}
