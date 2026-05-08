/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_math_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:23:53 by edugonza          #+#    #+#             */
/*   Updated: 2025/09/29 18:43:55 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

float	vector_dot_vector(t_v v1, t_v v2)
{
	return (v1.dx * v2.dx + v1.dy * v2.dy + v1.dz * v2.dz);
}

float	vector_mag(t_v v)
{
	return (sqrt(v.dx * v.dx + v.dy * v.dy + v.dz * v.dz));
}

void	reverse_vector(t_v *v)
{
	v->dx = v->dx * (-1);
	v->dy = v->dy * (-1);
	v->dz = v->dz * (-1);
	return ;
}

t_p	*point_plus_vector(t_p p, t_v v, float times)
{
	t_p	*new_point;

	new_point = build_point(p.x + times * v.dx,
			p.y + times * v.dy, p.z + times * v.dz);
	return (new_point);
}

t_v	*vector_normalized(t_v v)
{
	t_v		*new_vector;
	float	mag;

	mag = vector_mag(v);
	if (mag == 0)
		return (NULL);
	new_vector = build_vector(v.dx / mag, v.dy / mag, v.dz / mag);
	return (new_vector);
}
