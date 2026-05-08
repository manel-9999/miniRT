/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_counters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:08:05 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/10/06 16:07:00 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	count_sp(t_obj_sp **sp_arr)
{
	int	m;

	if (!sp_arr)
		return (0);
	m = 0;
	while (sp_arr[m])
		m++;
	return (m);
}

int	count_pl(t_obj_pl **pl_arr)
{
	int	m;

	if (!pl_arr)
		return (0);
	m = 0;
	while (pl_arr[m])
		m++;
	return (m);
}

int	count_cy(t_obj_cy **cy_arr)
{
	int	m;

	if (!cy_arr)
		return (0);
	m = 0;
	while (cy_arr[m])
		m++;
	return (m);
}

int	count_l(t_obj_L **l_arr)
{
	int	m;

	if (!l_arr)
		return (0);
	m = 0;
	while (l_arr[m])
		m++;
	return (m);
}
