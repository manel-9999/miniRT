/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_alc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 09:38:01 by mcarvalh          #+#    #+#             */
/*   Updated: 2025/11/10 14:33:24 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	calculate_screen(t_vars *prog)
{
	t_v	up;
	t_v	*temp;

	up.dx = 0;
	up.dy = 1;
	up.dz = 0;
	prog->map->c->screen_center = point_plus_vector(*prog->map->c->origin,
			*prog->map->c->n_vec, 1);
	temp = v_cross_v(up, *prog->map->c->n_vec);
	if (temp->dx == 0 && temp->dy == 0 && temp->dz == 0)
	{
		free(temp);
		temp = build_vector(1, 0, 0);
	}
	prog->map->c->screen_right = vector_normalized(*temp);
	free(temp);
	temp = v_cross_v(*prog->map->c->n_vec, *prog->map->c->screen_right);
	prog->map->c->screen_up = vector_normalized(*temp);
	free(temp);
	prog->map->c->pxl_size = tan((prog->map->c->degrees / 2) * M_PI / 180.0)
		/ (prog->img_w / 2);
	return ;
}

int	parse_ambient(char **temp, t_vars *prog)
{
	if (prog->map->a != NULL)
		return (return_error(prog, "Only one Ambient light (A) is allowed"));
	if (arg_count(temp) != 3 || (arg_count(temp) == 3
			&& (check_float(temp[1]) || check_colors(temp[2])
				|| ft_atof(temp[1]) < 0.0 || ft_atof(temp[1]) > 1.0)))
		return (return_error(prog, "Ambient light must have 2 arguments ==> "
				"(1) type float [0.0,1.0] // \
				(2) R,G,B [0-255, 0-255, 0-255] "));
	prog->map->a = malloc(sizeof(t_obj_A));
	if (!prog->map->a)
		return (return_error(prog, "Memory error allocating \
			Ambient light (A)"));
	prog->map->a->ratio = ft_atof(temp[1]);
	prog->map->a->color = parse_rgb_arr(temp[2]);
	return (0);
}

int	parse_camera(char **temp, t_vars *prog)
{
	printf("\n### parsing camera\n");
	if (prog->map->c != NULL)
		return (return_error(prog, "Only one Camera (C) is allowed"));
	if (arg_count(temp) != 4 || (arg_count(temp) == 4 && (check_int(temp[3])
				|| check_point(temp[1]) || check_vector(temp[2])
				|| ft_atoi(temp[3]) < 0 || ft_atoi(temp[3]) > 180)))
		return (return_error(prog, "Camera must have 3 arguments ==> (1) x,y,z "
				"point // (2) normalized vector // (3) type int [0,180]"));
	prog->map->c = malloc(sizeof(t_obj_C));
	if (!prog->map->c)
		return (return_error(prog, "Memory error allocating Camera (C)"));
	prog->map->c->origin = handle_origin_arr(temp[1]);
	prog->map->c->n_vec = handle_vector_arr(temp[2]);
	prog->map->c->degrees = ft_atoi(temp[3]);
	calculate_screen(prog);
	return (0);
}

int	parse_light(char **temp, t_vars *prog)
{
	int		count;

	printf("\n### parsing light\n");
	if (arg_count(temp) != 4 || (arg_count(temp) == 4 && (check_point(temp[1])
				|| check_float(temp[2]) || check_colors(temp[3])
				|| ft_atof(temp[2]) < 0 || ft_atof(temp[2]) > 1)))
		return (return_error(prog, "Light must have 3 arguments ==> (1) x,y,z "
				"point // (2) type float [0.0,1.0] "
				"// (3) R,G,B [0-255, 0-255, 0-255]"));
	count = count_l(prog->map->l_arr);
	if (prog->map->l_arr == NULL)
		prog->map->l_arr = malloc((count + 2) * sizeof(t_obj_L *));
	else
		prog->map->l_arr = ft_realloc(prog->map->l_arr, (count + 1)
				* sizeof(t_obj_L*), (count + 2) * sizeof(t_obj_L*));
	if (!prog->map->l_arr)
		return (return_error(prog, "Memory error allocating Light (L)"));
	prog->map->l_arr[count] = malloc(sizeof(t_obj_L));
	prog->map->l_arr[count]->origin = handle_origin_arr(temp[1]);
	prog->map->l_arr[count]->color = parse_rgb_arr(temp[3]);
	prog->map->l_arr[count]->ratio = ft_atof(temp[2]);
	prog->map->l_arr[count + 1] = NULL;
	return (0);
}
