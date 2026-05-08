/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:22:19 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 17:27:17 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_v	*n_point_to_light(t_p p_obj, t_obj_L *light)
{
	t_v	*to_light;
	t_v	*dir_to_light;

	to_light = p_min_p(*light->origin, p_obj);
	dir_to_light = vector_normalized(*to_light);
	free(to_light);
	return (dir_to_light);
}

void	l_on_pxl(unsigned int *pxl_c, unsigned int light_c,
	float ratio, unsigned int ori_c )
{
	int	pxl_c_unpack[3];
	int	light_c_unpack[3];
	int	ori_c_unpack[3];

	unpack_colors(pxl_c_unpack, *pxl_c);
	unpack_colors(light_c_unpack, light_c);
	unpack_colors(ori_c_unpack, ori_c);
	pxl_c_unpack[0] = (ori_c_unpack[0] * light_c_unpack[0] * ratio) / (255);
	pxl_c_unpack[1] = (ori_c_unpack[1] * light_c_unpack[1] * ratio) / (255);
	pxl_c_unpack[2] = (ori_c_unpack[2] * light_c_unpack[2] * ratio) / (255);
	*pxl_c = (pxl_c_unpack[0] << 16) | (pxl_c_unpack[1] << 8) | pxl_c_unpack[2];
}

static void	handle_light_shadow(t_light_p *params,
	unsigned int *final_color, t_obj_L *light)
{
	unsigned int	new_color;
	float			dot;
	t_v				*n_from_p_to_l;

	n_from_p_to_l = n_point_to_light(params->p_obj, light);
	if (!n_from_p_to_l)
		return ;
	dot = vector_dot_vector(*n_from_p_to_l, *params->n_n_on_p);
	if (dot <= 0.0f)
		return (free(n_from_p_to_l));
	new_color = 0;
	l_on_pxl(&new_color, light->color, light->ratio * dot, params->color);
	if (!is_in_shadow(params->prog, params->p_obj, *params->n_n_on_p, light))
	{
		add_colors(new_color, *final_color, final_color);
		specular(params, final_color, light);
	}
	else
	{
		new_color = 0;
		l_on_pxl(&new_color, light->color, light->ratio * dot * SCALE,
			params->color);
		add_colors(new_color, *final_color, final_color);
	}
	free(n_from_p_to_l);
}

void	apply_lights(t_vars *prog, t_v n_on_p, t_p p_obj, unsigned int *color)
{
	unsigned int	final_color;
	t_light_p		params;
	t_v				*n_n_on_p;
	int				i;

	final_color = 0;
	l_on_pxl(&final_color, prog->map->a->color, prog->map->a->ratio, *color);
	n_n_on_p = vector_normalized(n_on_p);
	if (!n_n_on_p)
		return ;
	params = (t_light_p){prog, p_obj, n_n_on_p, *color};
	i = -1;
	while (++i < count_l(prog->map->l_arr))
		handle_light_shadow(&params, &final_color, prog->map->l_arr[i]);
	free(n_n_on_p);
	*color = final_color;
}
