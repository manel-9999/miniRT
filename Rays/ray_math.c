/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:16:48 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 14:48:56 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_v	*get_ray_eq(int i, t_vars *prog)
{
	t_v	*ray_vec;
	t_p	*point_temp;
	t_p	*point_pxl;
	t_v	*x_screen;
	t_v	*y_screen;

	x_screen = num_times_vector(
			((i % prog->img_w) - (prog->img_w / 2)) * prog->map->c->pxl_size,
			*prog->map->c->screen_right);
	y_screen = num_times_vector(
			((prog->img_w / 2) - (i / prog->img_w)) * prog->map->c->pxl_size,
			*prog->map->c->screen_up);
	point_temp = point_plus_vector(*prog->map->c->screen_center, *x_screen, 1);
	point_pxl = point_plus_vector(*point_temp, *y_screen, 1);
	ray_vec = p_min_p(*point_pxl, *prog->map->c->origin);
	free(x_screen);
	free(y_screen);
	free(point_temp);
	free(point_pxl);
	return (ray_vec);
}

int	sp_hit(t_v ray_vec, t_obj_sp sp, t_obj_C cam, float *t)
{
	float	a;
	float	b;
	float	c;

	a = ray_vec.dx * ray_vec.dx
		+ ray_vec.dy * ray_vec.dy
		+ ray_vec.dz * ray_vec.dz;
	b = 2 * (
			ray_vec.dx * (cam.origin->x - sp.center->x)
			+ ray_vec.dy * (cam.origin->y - sp.center->y)
			+ ray_vec.dz * (cam.origin->z - sp.center->z));
	c = (cam.origin->x - sp.center->x) * (cam.origin->x - sp.center->x)
		+ (cam.origin->y - sp.center->y) * (cam.origin->y - sp.center->y)
		+ (cam.origin->z - sp.center->z) * (cam.origin->z - sp.center->z)
		- (sp.diameter / 2) * (sp.diameter / 2);
	return (get_lowest_t(a, b, c, t));
}

/*
	TODO: Try to limit the size of the plane
	if ((a / b) * pl.n_vec->dx + cam.origin->x - pl.center->x > 100 ||
			(a / b) * pl.n_vec->dy + cam.origin->y - pl.center->y > 100 ||
			(a / b) * pl.n_vec->dz + cam.origin->z - pl.center->z > 100)
		return(1);
*/

int	pl_hit(t_v ray_vec, t_obj_pl pl, t_obj_C cam, float *t)
{
	float	a;
	float	b;

	a = pl.n_vec->dx * (pl.center->x - cam.origin->x)
		+ pl.n_vec->dy * (pl.center->y - cam.origin->y)
		+ pl.n_vec->dz * (pl.center->z - cam.origin->z);
	b = ray_vec.dx * pl.n_vec->dx
		+ ray_vec.dy * pl.n_vec->dy
		+ ray_vec.dz * pl.n_vec->dz;
	if (fabsf(b) < 1e-6f)
		return (1);
	if (a / b < 0)
		return (1);
	else
	{
		*t = a / b;
		return (0);
	}
}

int	get_lowest_t(float a, float b, float c, float *t)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (1);
	else
	{
		t1 = (b * (-1) + sqrt(delta)) / (2 * a);
		t2 = (b * (-1) - sqrt(delta)) / (2 * a);
		if (t1 < 0 && t2 > 0)
			*t = t2;
		else if (t2 < 0 && t1 > 0)
			*t = t1;
		else if (t1 < t2 && t1 > 0)
			*t = t1;
		else if (t2 < t1 && t2 > 0)
			*t = t2;
		else
			return (1);
	}
	return (0);
}
