/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:06:35 by macampos          #+#    #+#             */
/*   Updated: 2023/10/20 15:37:29 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	buffer_fix(char *nl_pointer, char *buffer)
{
	if (nl_pointer[1] == '\0')
		ft_clearbuf(buffer);
	else
		ft_strcpy(buffer, nl_pointer + 1);
}

char	*get_next_line(int fd)
{
	char		*nlpointer;
	static char	buffer[NUMBER_BUFFERS][BUFFER_SIZE + 1];
	char		*line;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || fd >= NUMBER_BUFFERS)
	{
		if (fd > 0 && fd < NUMBER_BUFFERS && read(fd, 0, 0) >= 0)
			ft_clearbuf(buffer[fd]);
		return (NULL);
	}
	line = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE))
	{
		nlpointer = ft_strchr(buffer[fd], '\n');
		line = ft_strjoin(line, buffer[fd]);
		if (nlpointer)
		{
			buffer_fix(nlpointer, buffer[fd]);
			break ;
		}
		else
			ft_clearbuf(buffer[fd]);
	}
	return (line);
}

// int	main(void)
// {
// 	int	text;
// 	int	text1;
// 	int	text2;
// 	int	text3;

// 	text1 = open("text1.txt", O_RDONLY);
// 	text = open("text.txt", O_RDONLY);
// 	text3 = open("text3.txt", O_RDONLY);
// 	text2 = open("text2.txt", O_RDONLY);
// 	printf("%s", get_next_line(text));
// 	printf("%s", get_next_line(text));
// 	printf("%s", get_next_line(text));
// 	printf("%s", get_next_line(text));
// 	printf("%s", get_next_line(text1));
// 	printf("%s", get_next_line(text1));
// 	printf("%s", get_next_line(text1));
// 	printf("%s", get_next_line(text1));
// 	printf("%s", get_next_line(text2));
// 	printf("%s", get_next_line(text2));
// 	printf("%s", get_next_line(text2));
// 	printf("%s", get_next_line(text2));
// 	printf("%s", get_next_line(text3));
// 	printf("%s", get_next_line(text3));
// 	printf("%s", get_next_line(text3));
// 	printf("%s", get_next_line(text3));
// }