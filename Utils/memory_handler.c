/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:19:45 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 17:38:19 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_p	*build_point(float x, float y, float z)
{
	t_p	*point;

	point = malloc (sizeof(t_p));
	point->x = x;
	point->y = y;
	point->z = z;
	return (point);
}

t_v	*build_vector(float dx, float dy, float dz)
{
	t_v	*vector;

	vector = malloc (sizeof(t_v));
	vector->dx = dx;
	vector->dy = dy;
	vector->dz = dz;
	return (vector);
}

int	free_mlx(t_vars *prog)
{
	if (prog->img.img_ptr)
		mlx_destroy_image(prog->ptr, prog->img.img_ptr);
	if (prog->win)
		mlx_destroy_window(prog->ptr, prog->win);
	if (prog->ptr)
	{
		mlx_destroy_display(prog->ptr);
		free(prog->ptr);
	}
	if (prog->map)
		free_map(prog->map);
	return (0);
}
