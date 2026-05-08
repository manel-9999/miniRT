/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edugonza <edugonza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:53:00 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 18:05:55 by edugonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handle_movement(int keysym, t_vars *prog)
{
	float	x;
	float	y;
	float	z;

	x = prog->map->c->origin->x;
	y = prog->map->c->origin->y;
	z = prog->map->c->origin->z;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;
	if (z < 0)
		z = -z;
	if (keysym == 65362)
		prog->map->c->origin->z += z / 10;
	else if (keysym == 65364)
		prog->map->c->origin->z -= z / 10;
	else if (keysym == 65363)
		prog->map->c->origin->x += x / 10;
	else if (keysym == 65361)
		prog->map->c->origin->x -= x / 10;
	else if (keysym == 104)
		prog->map->c->origin->y += y / 10;
	else if (keysym == 108)
		prog->map->c->origin->y -= y / 10;
}

int	handle_input(int keysym, t_vars *prog)
{
	ft_printf("\n## New Key Pressed ##\n");
	if (keysym == XK_Escape)
	{
		mlx_loop_end(prog->ptr);
		return (1);
	}
	else
	{
		free(prog->map->c->screen_center);
		free(prog->map->c->screen_right);
		free(prog->map->c->screen_up);
		handle_movement(keysym, prog);
		calculate_screen(prog);
		build_image(prog);
	}
	return (0);
}

int	handle_x(t_vars *prog)
{
	ft_printf("\n## X Pressed ##\n");
	mlx_loop_end(prog->ptr);
	return (1);
}

// void	print_vector(t_v v, char *name)
// {
// 	printf("%s: [%.8f, %.8f, %.8f]\n", name, v.dx, v.dy, v.dz);
// 	return ;
// }

// void	print_point(t_p p, char *name)
// {
// 	printf("%s: [%.8f, %.8f, %.8f]\n", name, p.x, p.y, p.z);
// 	return ;
// }

int	return_error(t_vars *prog, char *str)
{
	errno = 1;
	perror(str);
	free_map(prog->map);
	if (prog->fd != -1)
		close(prog->fd);
	return (1);
}
