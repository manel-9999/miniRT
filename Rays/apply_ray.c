/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:03:11 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 17:38:59 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	ray_to_all_sps(t_vars *prog, t_v *r_vec, float *t, unsigned int *color)
{
	t_v		*n_on_p;
	t_p		*p_sphere;
	float	temp;
	int		j;

	temp = *t;
	j = 0;
	while (prog->map->sp_arr && prog->map->sp_arr[j])
	{
		if (!sp_hit(*r_vec, *prog->map->sp_arr[j], *prog->map->c, &temp))
		{
			if (*t > temp)
			{
				*t = temp;
				*color = prog->map->sp_arr[j]->color;
				p_sphere = point_plus_vector(*prog->map->c->origin, *r_vec, *t);
				n_on_p = p_min_p(*p_sphere, *prog->map->sp_arr[j]->center);
				apply_lights(prog, *n_on_p, *p_sphere, color);
				free(n_on_p);
				free(p_sphere);
			}
		}
		j++;
	}
	return ;
}

void	ray_to_all_pls(t_vars *prog, t_v *r_vec, float *t, unsigned int *color)
{
	t_p		*p_plane;
	float	temp;
	int		j;

	temp = *t;
	j = 0;
	while (prog->map->pl_arr && prog->map->pl_arr[j])
	{
		if (!pl_hit(*r_vec, *prog->map->pl_arr[j], *prog->map->c, &temp))
		{
			if (*t > temp)
			{
				*t = temp;
				*color = prog->map->pl_arr[j]->color;
				p_plane = point_plus_vector(*prog->map->c->origin, *r_vec, *t);
				apply_lights(prog, *prog->map->pl_arr[j]->n_vec,
					*p_plane, color);
				free(p_plane);
			}
		}
		j++;
	}
	return ;
}

void	ray_to_all_cys(t_vars *prog, t_v *r_vec, float *t, unsigned int *color)
{
	t_v		*normal_on_point;
	t_p		*p_cy;
	float	temp;
	int		j;

	temp = *t;
	j = 0;
	while (prog->map->cy_arr && prog->map->cy_arr[j])
	{
		if (!cy_hit(*r_vec, *prog->map->cy_arr[j], *prog->map->c, &temp))
		{
			if (*t > temp)
			{
				*t = temp;
				*color = prog->map->cy_arr[j]->color;
				p_cy = point_plus_vector(*prog->map->c->origin, *r_vec, *t);
				normal_on_point = n_from_cy(*prog->map->cy_arr[j], p_cy);
				apply_lights(prog, *normal_on_point, *p_cy, color);
				free(normal_on_point);
				free(p_cy);
			}
		}
		j++;
	}
	return ;
}
