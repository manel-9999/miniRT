/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:11:17 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/10/06 19:56:21 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	arg_count(char **str)
{
	int	m;

	m = 0;
	while (str[m] != NULL)
		m++;
	return (m);
}

static int	rgb_to_hex(int *rgb)
{
	int	r;
	int	g;
	int	b;
	int	hex_nbr;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_printf("Error\nWrong RGB values, must be in range [0,255]\n");
		exit(1);
	}
	hex_nbr = (r << 16) | (g << 8) | b;
	printf("RGB to hex: 0x%x\n", hex_nbr);
	return (hex_nbr);
}

int	parse_rgb_arr(char *str)
{
	char	**temp;
	int		*arr;
	int		m;
	int		hex_nbr;

	temp = ft_split(str, ',');
	if (arg_count(temp) != 3)
	{
		ft_printf("Error\nArray must have 3 values\n");
		free(temp);
		exit(1);
	}
	arr = malloc (3 * sizeof(int));
	m = 0;
	while (m < 3)
	{
		arr[m] = ft_atoi(temp[m]);
		m++;
	}
	ft_split_free(temp);
	hex_nbr = rgb_to_hex(arr);
	free(arr);
	return (hex_nbr);
}

t_p	*handle_origin_arr(char *str)
{
	char		**temp;
	float		arr[3];
	int			m;
	t_p			*point;

	temp = ft_split(str, ',');
	m = 0;
	while (m < 3)
	{
		arr[m] = ft_atof(temp[m]);
		m++;
	}
	ft_split_free(temp);
	point = build_point(arr[0], arr[1], arr[2]);
	printf("Point built: x:%.4f, y:%.4f, z:%.4f\n",
		point->x, point->y, point->z);
	return (point);
}

t_v	*handle_vector_arr(char *str)
{
	char	**temp;
	float	*arr;
	int		m;
	t_v		*vector;
	t_v		*v_temp;

	if (str[0] == 't')
		str++;
	temp = ft_split(str, ',');
	arr = malloc(3 * sizeof(float));
	m = 0;
	while (m < 3)
	{
		arr[m] = ft_atof(temp[m]);
		printf("Vector arr[%d]: %.4f\n", m, arr[m]);
		m++;
	}
	ft_split_free(temp);
	v_temp = build_vector(arr[0], arr[1], arr[2]);
	vector = vector_normalized(*v_temp);
	free(v_temp);
	free(arr);
	return (vector);
}
