/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:36 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 14:49:07 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_v	*p_min_p(t_p p1, t_p p2)
{
	t_v	*new_vector;

	new_vector = build_vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
	return (new_vector);
}

t_v	*vector_plus_vector(t_v v1, t_v v2)
{
	t_v	*new_vector;

	new_vector = build_vector(v1.dx + v2.dx, v1.dy + v2.dy, v1.dz + v2.dz);
	return (new_vector);
}

t_v	*vector_minus_vector(t_v v1, t_v v2)
{
	t_v	*new_vector;

	new_vector = build_vector(v1.dx - v2.dx, v1.dy - v2.dy, v1.dz - v2.dz);
	return (new_vector);
}

t_v	*num_times_vector(float num, t_v v)
{
	t_v	*new_vector;

	new_vector = build_vector(num * v.dx, num * v.dy, num * v.dz);
	return (new_vector);
}

t_v	*v_cross_v(t_v v1, t_v v2)
{
	t_v		*result;
	float	dx;
	float	dy;
	float	dz;

	dx = v1.dy * v2.dz - v1.dz * v2.dy;
	dy = v1.dz * v2.dx - v1.dx * v2.dz;
	dz = v1.dx * v2.dy - v1.dy * v2.dx;
	result = build_vector(dx, dy, dz);
	return (result);
}
