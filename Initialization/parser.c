/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:18:44 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 17:26:10 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	normalize_line(char **line)
{
	int		i;
	char	*temp;

	temp = ft_strtrim(*line, "\n\t ");
	i = 0;
	while (temp[i] != '\0')
	{
		if (!ft_isprint(temp[i]) || temp[i] == ' ')
			temp[i] = ' ';
		i++;
	}
	free(*line);
	*line = temp;
	return ;
}

void	end_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
}

int	valid_line(char *line, t_vars *prog)
{
	char	**temp;
	int		val;

	temp = ft_split(line, ' ');
	val = 0;
	if (ft_strncmp(temp[0], "A", 1) == 0)
		val = parse_ambient(temp, prog);
	else if (ft_strncmp(temp[0], "C", 1) == 0)
		val = parse_camera(temp, prog);
	else if (ft_strncmp(temp[0], "L", 1) == 0)
		val = parse_light(temp, prog);
	else if (ft_strncmp(temp[0], "sp", 2) == 0)
		val = parse_sphere(temp, prog);
	else if (ft_strncmp(temp[0], "pl", 2) == 0)
		val = parse_plane(temp, prog);
	else if (ft_strncmp(temp[0], "cy", 2) == 0)
		val = parse_cylinder(temp, prog);
	else if (ft_strncmp(temp[0], "#", 1) == 0)
		val = 0;
	else
		val = return_error(prog, "Invalid line in map file, accepted lines"
				"should begin with 'A', 'C', 'L', 'sp', 'pl', 'cy' or '#'");
	ft_split_free(temp);
	return (val);
}

void	parsing(int fd, t_vars *prog)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		while (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
		}
		normalize_line(&line);
		if (valid_line(line, prog))
		{
			ft_printf("\n\n### --- INVALID MAP --- ###\n\n");
			free(line);
			end_gnl(fd);
			exit (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
