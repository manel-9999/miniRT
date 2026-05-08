/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:07:31 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/11/10 14:42:09 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parse_sphere(char **temp, t_vars *prog)
{
	int		count;

	printf("\n### parsing sphere\n");
	if (arg_count(temp) != 4 || (arg_count(temp) == 4 && (check_point(temp[1])
				|| check_float(temp[2])
				|| check_colors(temp[3]) || ft_atof(temp[2]) <= 0)))
		return (return_error(prog, "Sphere (sp) must have 3 arguments ==> (1) "
				"x,y,z point // (2) Diameter type float [> 0] // \
				(3) R,G,B [0-255, "
				"0-255, 0-255]"));
	count = count_sp(prog->map->sp_arr);
	if (prog->map->sp_arr == NULL)
		prog->map->sp_arr = malloc((count + 2) * sizeof(t_obj_sp *));
	else
		prog->map->sp_arr = ft_realloc(prog->map->sp_arr, (count + 1)
				* sizeof(t_obj_sp *), (count + 2) * sizeof(t_obj_sp *));
	if (!prog->map->sp_arr)
		return (return_error(prog, "Memory error allocating sphere (sp)"));
	prog->map->sp_arr[count] = malloc(sizeof(t_obj_sp));
	prog->map->sp_arr[count]->center = handle_origin_arr(temp[1]);
	prog->map->sp_arr[count]->diameter = ft_atof(temp[2]);
	prog->map->sp_arr[count]->color = parse_rgb_arr(temp[3]);
	prog->map->sp_arr[count + 1] = NULL;
	return (0);
}

int	parse_plane(char **temp, t_vars *prog)
{
	int		count;

	printf("\n### parsing plane\n");
	if (arg_count(temp) != 4 || (arg_count(temp) == 4 && (check_point(temp[1])
				|| check_vector(temp[2]) || check_colors(temp[3]))))
		return (return_error(prog, "Plane (pl) must have 3 arguments ==> (1) "
				"x,y,z point // (2) normalized vector // (3) R,G,B [0-255, "
				"0-255, 0-255]"));
	count = count_pl(prog->map->pl_arr);
	if (prog->map->pl_arr == NULL)
		prog->map->pl_arr = malloc((count + 2) * sizeof(t_obj_pl *));
	else
		prog->map->pl_arr = ft_realloc(prog->map->pl_arr, (count + 1)
				* sizeof(t_obj_pl *), (count + 2) * sizeof(t_obj_pl *));
	if (!prog->map->pl_arr)
		return (return_error(prog, "Memory error allocating plane (pl)"));
	prog->map->pl_arr[count] = malloc(sizeof(t_obj_pl));
	prog->map->pl_arr[count]->center = handle_origin_arr(temp[1]);
	prog->map->pl_arr[count]->n_vec = handle_vector_arr(temp[2]);
	prog->map->pl_arr[count]->color = parse_rgb_arr(temp[3]);
	prog->map->pl_arr[count + 1] = NULL;
	return (0);
}

int	parse_cylinder(char **temp, t_vars *prog)
{
	int		count;

	printf("\n### parsing cylinder\n");
	if (arg_count(temp) != 6 || (arg_count(temp) == 6 && (check_point(temp[1])
				|| check_vector(temp[2]) || ft_atof(temp[3]) <= 0
				|| ft_atof(temp[4]) <= 0 || check_colors(temp[5]))))
		return (return_error(prog, "Cy must have 5 args ==> (1) x,y,z point //"
				"(2) normalized vector // (3) Diameter float [> 0] // (4)"
				" Height float [> 0] // (5) R,G,B [0-255, 0-255, 0-255]"));
	count = count_cy(prog->map->cy_arr);
	if (prog->map->cy_arr == NULL)
		prog->map->cy_arr = malloc((count + 2) * sizeof(t_obj_cy *));
	else
		prog->map->cy_arr = ft_realloc(prog->map->cy_arr, (count + 1)
				* sizeof(t_obj_cy *), (count + 2) * sizeof(t_obj_cy *));
	if (!prog->map->cy_arr)
		return (return_error(prog, "Memory error allocating cylinder (cy)"));
	prog->map->cy_arr[count] = malloc(sizeof(t_obj_cy));
	prog->map->cy_arr[count]->center = handle_origin_arr(temp[1]);
	prog->map->cy_arr[count]->n_vec = handle_vector_arr(temp[2]);
	prog->map->cy_arr[count]->diameter = ft_atof(temp[3]);
	prog->map->cy_arr[count]->height = ft_atof(temp[4]);
	prog->map->cy_arr[count]->color = parse_rgb_arr(temp[5]);
	prog->map->cy_arr[count + 1] = NULL;
	return (0);
}
