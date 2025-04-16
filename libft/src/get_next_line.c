/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:35:25 by rcochran          #+#    #+#             */
/*   Updated: 2025/03/10 18:16:42 by rcochran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*extract_line(char *buf)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
	{
		return (free(buf), free(line), NULL);
	}
	j = 0;
	while (j < i)
	{
		line[j] = buf[j];
		j++;
	}
	return (line);
}

/* return new str : *buffer at the end of *buf and free buf */
char	*append_and_free(char *buffer, char *add)
{
	char	*new_buffer;

	if (!buffer && !add)
		return (NULL);
	if (!buffer)
		return (add);
	new_buffer = ft_strjoin(buffer, add);
	if (new_buffer == NULL)
		return (NULL);
	free(buffer);
	return (new_buffer);
}

char	*get_buffer(int fd, char *buf)
{
	char	*buffer;
	int		nb_read;

	if (!buf)
		buf = ft_calloc(1, 1);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
			return (free(buf), free(buffer), NULL);
		buffer[nb_read] = '\0';
		buf = append_and_free(buf, buffer);
		if (ft_strchr(buf, '\n') != NULL)
			break ;
	}
	free(buffer);
	return (buf);
}

char	*update_buf(char *buf)
{
	size_t	i;
	size_t	j;
	char	*new_buf;

	i = 0;
	while (buf[i] != '\0' && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	if (!buf[i])
		return (free(buf), NULL);
	new_buf = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	if (!new_buf)
		return (free (buf), NULL);
	j = 0;
	while (buf[i + j] != '\0')
	{
		new_buf[j] = buf[i + j];
		j++;
	}
	new_buf[j] = '\0';
	return (free(buf), new_buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf = 0;

	if (!buf)
		buf = ft_calloc(1, 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(buf, '\n') == NULL)
	{
		buf = get_buffer(fd, buf);
	}
	if (!buf)
		return (NULL);
	line = extract_line(buf);
	buf = update_buf(buf);
	return (line);
}

/* int	main(int ac, char *av[])
{
	int		fd;
	char	*temp;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	temp = get_next_line(fd);
	printf("line : [%s]\n", temp);
	while (temp)
	{
		free(temp);
		temp = get_next_line(fd);
		printf("line : [%s]\n", temp);
	}
	close(fd);
	return (0);
} */

/* int	main(int ac, char *av[])
{

	while (1)
		printf("%s\n", get_next_line(0));

} */
/* int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	printf("l.129 - 1st line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.132 - 2nd line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.135 - 3rd line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.138 - 4th line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.138 - 5th line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.138 - 6th line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.138 - 7th line : |%s|\n", line);
	free(line);
	line = get_next_line(fd);
	printf("l.138 - 8th line : |%s|\n", line);
	free(line);
	if (fd >= 0)
		close(fd);
	return (0);
} */