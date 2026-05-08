/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:25:07 by edugonza          #+#    #+#             */
/*   Updated: 2025/10/06 19:47:35 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_int(char *line)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i]) && line[i] != '-' && line[i] != '+')
			res = 1;
		i++;
	}
	return (res);
}

int	check_float(char *line)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isdigit(line[i])
			&& line[i] != '.' && line[i] != '-' && line[i] != '+')
			res = 1;
		i++;
	}
	return (res);
}

int	check_colors(char *line)
{
	int		i;
	int		res;
	char	**temp;

	res = 0;
	temp = ft_split(line, ',');
	i = 0;
	if (arg_count(temp) != 3)
	{
		ft_split_free(temp);
		return (1);
	}
	while (i != 3)
	{
		if (check_int(temp[i]))
			res = 1;
		if (ft_atoi(temp[i]) < 0 || ft_atoi(temp[i]) > 255)
			res = 1;
		i++;
	}
	ft_split_free(temp);
	return (res);
}

int	check_point(char *line)
{
	int		i;
	int		res;
	char	**temp;

	res = 0;
	temp = ft_split(line, ',');
	i = 0;
	if (arg_count(temp) != 3)
	{
		ft_split_free(temp);
		return (1);
	}
	while (i != 3)
	{
		if (check_float(temp[i]))
			res = 1;
		i++;
	}
	ft_split_free(temp);
	return (res);
}
