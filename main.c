/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manelcarvalho <manelcarvalho@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:30:42 by edugonza          #+#    #+#             */
/*   Updated: 2025/10/23 14:33:50 by manelcarval      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_pixel(t_vars *prog, int i, int color)
{
	int	offset;
	int	x;
	int	y;

	y = (i / prog->img_w);
	x = (i % prog->img_w);
	if (x > 0 && x < prog->img_w && y > 0 && y < prog->img_w)
	{
		offset = (prog->img.line_len * y)
			+ (x * (prog->img.bits_per_pixel / 8));
		*((unsigned int *)(offset + prog->img.img_pxl_ptr)) = color;
	}
	return ;
}

void	ray_to_obj(t_vars *prog)
{
	unsigned int	color;
	t_v				*ray_vec;
	float			t;
	int				i;

	i = 0;
	while (i < prog->img_h * prog->img_w)
	{
		t = prog->map->limit_distance;
		color = prog->map->background_color;
		ray_vec = get_ray_eq(i, prog);
		ray_to_all_sps(prog, ray_vec, &t, &color);
		ray_to_all_pls(prog, ray_vec, &t, &color);
		ray_to_all_cys(prog, ray_vec, &t, &color);
		free(ray_vec);
		put_pixel(prog, i, color);
		i++;
	}
	return ;
}

void	build_image(t_vars *prog)
{
	ray_to_obj(prog);
	mlx_put_image_to_window(prog->ptr, prog->win,
		prog->img.img_ptr, (prog->win_h - prog->img_h) / 2,
		(prog->win_w - prog->img_w) / 2);
	printf("\n### Image built ###\n");
	return ;
}

int	main(int ac, char **av)
{
	t_vars	prog;

	prog.win_h = 920;
	prog.win_w = 920;
	prog.img_h = 900;
	prog.img_w = 900;
	if (input_checker(ac, av, &prog))
		return (1);
	if (init_mlx(&prog))
		return (1);
	build_image(&prog);
	mlx_key_hook(prog.win, handle_input, &prog);
	mlx_hook(prog.win, 17, 1L << 3, handle_x, &prog);
	mlx_loop(prog.ptr);
	free_mlx(&prog);
	return (0);
}
