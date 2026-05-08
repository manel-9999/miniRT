/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checker_vectors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:47:16 by edugonza          #+#    #+#             */
/*   Updated: 2025/10/06 19:55:53 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_vector_force_mag(char **temp)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (arg_count(temp) != 3)
		return (1);
	while (i != 3)
	{
		if (check_float(temp[i]))
			res = 1;
		i++;
	}
	return (res);
}

int	check_vector_check_mag(char **temp)
{
	int		i;
	float	mag;
	float	comp[3];
	int		res;

	res = 0;
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
		comp[i] = ft_atof(temp[i]);
		i++;
	}
	mag = comp[0] * comp[0] + comp[1] * comp[1] + comp[2] * comp[2];
	if (mag > 1.001 || mag < 0.999)
		res = 1;
	printf("check_vector result: %.8f -- %d\n", mag, res);
	return (res);
}

int	check_vector(char *line)
{
	int		res;
	char	**temp;

	res = 0;
	if (line[0] == 't')
	{
		temp = ft_split(line + 1, ',');
		res = check_vector_force_mag(temp);
	}
	else
	{
		temp = ft_split(line, ',');
		res = check_vector_check_mag(temp);
	}
	ft_split_free(temp);
	return (res);
}
