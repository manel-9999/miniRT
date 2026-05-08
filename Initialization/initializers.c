/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:23:28 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 14:30:46 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	validate_map(char **av, t_vars *prog)
{
	prog->fd = open(av[1], O_RDONLY);
	if (prog->fd == -1)
		exit (return_error(prog, "File cannot be opened"));
	prog->map = malloc (sizeof(t_map));
	prog->map->a = NULL;
	prog->map->c = NULL;
	prog->map->l_arr = NULL;
	prog->map->sp_arr = NULL;
	prog->map->pl_arr = NULL;
	prog->map->cy_arr = NULL;
	prog->map->limit_distance = 10000000;
	prog->map->background_color = 0x000000;
	parsing(prog->fd, prog);
	if (prog->map->a == NULL || prog->map->c == NULL
		|| count_l(prog->map->l_arr) == 0)
		exit (return_error(prog, "Error\nMap must contain one Ambient light "
				"(A), one Camera (C) and one Light (L)\n"));
	close(prog->fd);
	return (0);
}

int	input_checker(int ac, char *av[], t_vars *prog)
{
	char	**file_ext;

	prog->map = NULL;
	prog->fd = -1;
	if (ac != 2)
		exit(return_error(prog, "Usage: miniRT [map file]"));
	if (!ft_strchr(av[1], '.'))
		exit(return_error(prog, "File not supported - no extension found"));
	file_ext = ft_split(av[1], '.');
	if (file_ext[1] == NULL || ft_strcmp(file_ext[1], "rt") != 0)
	{
		ft_split_free(file_ext);
		exit(return_error(prog, "File not supported - \
			extension not supported"));
	}
	ft_split_free(file_ext);
	if (validate_map(av, prog))
		exit(return_error(prog, "not a valid map"));
	return (0);
}

int	init_mlx(t_vars *prog)
{
	prog->ptr = mlx_init();
	if (prog->ptr == NULL)
	{
		perror("mlx not correctly initialized");
		return (1);
	}
	prog->win = mlx_new_window(prog->ptr, prog->win_h, prog->win_w, "Main");
	if (prog->win == NULL)
	{
		perror("mlx not correctly initialized");
		free_mlx(prog);
		return (1);
	}
	prog->img.img_ptr = mlx_new_image(prog->ptr, prog->img_h, prog->img_w);
	prog->img.img_pxl_ptr = mlx_get_data_addr(prog->img.img_ptr,
			&prog->img.bits_per_pixel,
			&prog->img.line_len,
			&prog->img.endian);
	if (prog->img.img_ptr == NULL)
	{
		perror("mlx not correctly initialized");
		free_mlx(prog);
		return (1);
	}
	return (0);
}
