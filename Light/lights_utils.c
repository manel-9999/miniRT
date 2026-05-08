/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:07:48 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/11/10 17:03:26 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	unpack_colors(int rgb[3], unsigned int color)
{
	rgb[0] = (color >> 16) & 0xff;
	rgb[1] = (color >> 8) & 0xff;
	rgb[2] = color & 0xff;
}

void	add_colors(unsigned int c1, unsigned int c2, unsigned int *result)
{
	int	rgb1[3];
	int	rgb2[3];
	int	final[3];

	unpack_colors(rgb1, c1);
	unpack_colors(rgb2, c2);
	final[0] = fmin(255, rgb1[0] + rgb2[0]);
	final[1] = fmin(255, rgb1[1] + rgb2[1]);
	final[2] = fmin(255, rgb1[2] + rgb2[2]);
	*result = (final[0] << 16) | (final[1] << 8) | final[2];
}

void	light_calcs(unsigned int *final_color, unsigned int L_color,
	float inten, unsigned int ori_color)
{
	unsigned int	new_color;

	if (inten < 0)
		inten = 0;
	new_color = 0;
	l_on_pxl(&new_color, L_color, inten, ori_color);
	add_colors(new_color, *final_color, final_color);
}

t_v	*get_half_vector(t_p p_obj, t_vars *prog, t_v light_dir)
{
	t_v	*to_cam;
	t_v	*n_to_cam;
	t_v	*half;
	t_v	*n_half;

	to_cam = p_min_p(*prog->map->c->origin, p_obj);
	if (!to_cam)
		return (NULL);
	n_to_cam = vector_normalized(*to_cam);
	if (!n_to_cam)
		return (NULL);
	half = vector_plus_vector(light_dir, *n_to_cam);
	n_half = vector_normalized(*half);
	free(to_cam);
	free(n_to_cam);
	free(half);
	return (n_half);
}

void	specular(t_light_p *params, unsigned int *final_color, t_obj_L *light)
{
	unsigned int	spec_color;
	float			dot_n_h;
	float			spec_intense;
	t_v				*half;
	t_v				*light_dir;

	light_dir = n_point_to_light(params->p_obj, light);
	half = get_half_vector(params->p_obj, params->prog, *light_dir);
	dot_n_h = vector_dot_vector(*params->n_n_on_p, *half);
	if (dot_n_h > 0.0f)
	{
		spec_intense = STRENGHT * light->ratio * powf(dot_n_h, SHINY);
		spec_color = 0;
		l_on_pxl(&spec_color, light->color, spec_intense, 0xFFFFFF);
		add_colors(spec_color, *final_color, final_color);
	}
	free(light_dir);
	free(half);
}
