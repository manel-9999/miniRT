/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:25:36 by edugonza          #+#    #+#             */
/*   Updated: 2025/10/06 19:59:24 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_alc(t_map *map)
{
	int	i;

	i = 0;
	if (map->a)
		free(map->a);
	if (map->c)
	{
		free(map->c->origin);
		free(map->c->n_vec);
		free(map->c->screen_center);
		free(map->c->screen_up);
		free(map->c->screen_right);
		free(map->c);
	}
	while (i < count_l(map->l_arr))
	{
		free(map->l_arr[i]->origin);
		free(map->l_arr[i]);
		i++;
	}
	free(map->l_arr);
	return ;
}

void	free_sp(t_map *map)
{
	int	i;

	i = 0;
	if (map->sp_arr)
	{
		while (map->sp_arr[i] != NULL)
		{
			free(map->sp_arr[i]->center);
			free(map->sp_arr[i]);
			i++;
		}
		free(map->sp_arr);
	}
	return ;
}

void	free_pl(t_map *map)
{
	int	i;

	i = 0;
	if (map->pl_arr)
	{
		while (map->pl_arr[i] != NULL)
		{
			free(map->pl_arr[i]->n_vec);
			free(map->pl_arr[i]->center);
			free(map->pl_arr[i]);
			i++;
		}
		free(map->pl_arr);
	}
	return ;
}

void	free_cy(t_map *map)
{
	int	i;

	i = 0;
	if (map->cy_arr)
	{
		while (map->cy_arr[i] != NULL)
		{
			free(map->cy_arr[i]->center);
			free(map->cy_arr[i]->n_vec);
			free(map->cy_arr[i]);
			i++;
		}
		free(map->cy_arr);
	}
	return ;
}

void	free_map(t_map *map)
{
	if (map)
	{
		free_alc(map);
		free_sp(map);
		free_pl(map);
		free_cy(map);
	}
	free(map);
	return ;
}
