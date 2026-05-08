/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:01:42 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 15:44:28 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static t_p	*get_shadow_origin(t_p p_obj, t_v n_on_p, t_v *dir_to_light)
{
	t_v	*offset;
	t_p	*shadow_origin;

	if (vector_dot_vector(n_on_p, *dir_to_light) >= 0.0f)
		offset = num_times_vector(SHADOW, n_on_p);
	else
		offset = num_times_vector(-SHADOW, n_on_p);
	shadow_origin = point_plus_vector(p_obj, *offset, 1);
	free(offset);
	return (shadow_origin);
}

static int	check_shadow_sp(t_v *to_light, t_obj_C tmp_cam, t_obj_sp **sp_arr)
{
	int		j;
	float	t;
	float	light_dist;
	t_v		*v_l;

	light_dist = vector_mag(*to_light);
	v_l = vector_normalized(*to_light);
	if (!v_l)
		return (0);
	j = 0;
	while (sp_arr[j])
	{
		t = -1.0f;
		if (!sp_hit(*v_l, *sp_arr[j], tmp_cam, &t) && t > SHADOW && \
				t < light_dist - SHADOW)
		{
			free(v_l);
			return (1);
		}
		j++;
	}
	free(v_l);
	return (0);
}

static int	check_shadow_pl(t_v *to_light, t_obj_C tmp_cam, t_obj_pl **pl_arr)
{
	int		j;
	float	t;
	float	light_dist;
	t_v		*v_l;

	light_dist = vector_mag(*to_light);
	v_l = vector_normalized(*to_light);
	if (!v_l)
		return (0);
	j = 0;
	while (pl_arr[j])
	{
		t = -1.0f;
		if (!pl_hit(*v_l, *pl_arr[j], tmp_cam, &t) && t > SHADOW && \
				t < light_dist - SHADOW)
		{
			free(v_l);
			return (1);
		}
		j++;
	}
	free(v_l);
	return (0);
}

static int	check_shadow_cy(t_v *to_light, t_obj_C tmp_cam, t_obj_cy **cy_arr)
{
	int		j;
	float	t;
	float	light_dist;
	t_v		*v_l;

	light_dist = vector_mag(*to_light);
	v_l = vector_normalized(*to_light);
	if (!v_l)
		return (0);
	j = 0;
	while (cy_arr[j])
	{
		t = -1.0f;
		if (!cy_hit(*v_l, *cy_arr[j], tmp_cam, &t) && t > SHADOW && \
				t < light_dist - SHADOW)
		{
			free(v_l);
			return (1);
		}
		j++;
	}
	free(v_l);
	return (0);
}

int	is_in_shadow(t_vars *prog, t_p p_obj, t_v n_on_p, t_obj_L *light)
{
	t_v		*to_light;
	t_v		*dir_to_light;
	t_p		*shadow_origin;
	t_obj_C	tmp_cam;
	int		in_shadow;

	to_light = p_min_p(*light->origin, p_obj);
	dir_to_light = n_point_to_light(p_obj, light);
	shadow_origin = get_shadow_origin(p_obj, n_on_p, dir_to_light);
	tmp_cam = *prog->map->c;
	tmp_cam.origin = shadow_origin;
	in_shadow = 0;
	if (prog->map->sp_arr)
		in_shadow |= check_shadow_sp(to_light, tmp_cam, prog->map->sp_arr);
	if (!in_shadow && prog->map->pl_arr)
		in_shadow |= check_shadow_pl(to_light, tmp_cam, prog->map->pl_arr);
	if (!in_shadow && prog->map->cy_arr)
		in_shadow |= check_shadow_cy(to_light, tmp_cam, prog->map->cy_arr);
	free(shadow_origin);
	free(to_light);
	free(dir_to_light);
	return (in_shadow);
}
