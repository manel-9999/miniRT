/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:36:14 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 17:01:52 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "Libft_power/libft.h"
# include "Libft_power/ft_printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <errno.h>

# define SHADOW 1e-3
# define SCALE 0.01f
# define SHINY 90.0f
# define STRENGHT 0.9f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}				t_p;

typedef struct s_vector
{
	float	dx;
	float	dy;
	float	dz;
}				t_v;

typedef struct s_obj_A
{
	unsigned int	color;
	float			ratio;
}				t_obj_A;

typedef struct s_obj_C
{
	int			degrees;
	float		pxl_size;
	t_p			*origin;
	t_p			*screen_center;
	t_v			*n_vec;
	t_v			*screen_up;
	t_v			*screen_right;
}				t_obj_C;

typedef struct s_obj_L
{
	unsigned int	color;
	float			ratio;
	t_p				*origin;
}				t_obj_L;

typedef struct s_obj_sp
{
	unsigned int	color;
	float			diameter;
	t_p				*center;
}				t_obj_sp;

typedef struct s_obj_pl
{
	unsigned int	color;
	t_p				*center;
	t_v				*n_vec;
}				t_obj_pl;

typedef struct s_obj_cy
{
	unsigned int	color;
	float			diameter;
	float			height;
	t_p				*center;
	t_v				*n_vec;
}				t_obj_cy;

typedef struct s_map
{
	unsigned int	background_color;
	float			limit_distance;
	t_obj_A			*a;
	t_obj_C			*c;
	t_obj_L			**l_arr;
	t_obj_sp		**sp_arr;
	t_obj_pl		**pl_arr;
	t_obj_cy		**cy_arr;
}				t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pxl_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_vars
{
	void		*ptr;
	void		*win;
	int			win_w;
	int			win_h;
	int			img_w;
	int			img_h;
	int			fd;
	t_img		img;
	t_map		*map;
}				t_vars;

typedef struct s_light_params
{
	t_vars			*prog;
	t_p				p_obj;
	t_v				*n_n_on_p;
	unsigned int	color;
}	t_light_p;

/////////------------------------ /////////
/////////---- INITIALIZATION ---- /////////
/////////------------------------ /////////

// DATA CHECKER VECTORS
int		check_vector(char *line);

// DATA CHECKER
int		check_int(char *line);
int		check_float(char *line);
int		check_colors(char *line);
int		check_point(char *line);

// INITIALIZERS
int		init_mlx(t_vars *prog);
int		input_checker(int ac, char *av[], t_vars *prog);

// PARSER ALC
void	calculate_screen(t_vars *prog);
int		parse_ambient(char **temp, t_vars *prog);
int		parse_camera(char **temp, t_vars *prog);
int		parse_light(char **temp, t_vars *prog);

// PARSE COUNTERS
int		count_sp(t_obj_sp **sp_arr);
int		count_pl(t_obj_pl **pl_arr);
int		count_cy(t_obj_cy **cy_arr);
int		count_l(t_obj_L **l_arr);

// PARSER OBJECTS
int		parse_sphere(char **temp, t_vars *prog);
int		parse_plane(char **temp, t_vars *prog);
int		parse_cylinder(char **temp, t_vars *prog);

// PARSE UTILS
t_p		*handle_origin_arr(char *str);
t_v		*handle_vector_arr(char *str);
int		parse_rgb_arr(char *str);
int		arg_count(char **str);

// PARSER
void	parsing(int fd, t_vars *prog);

/////////------------------------- /////////
/////////--------- UTILS --------- /////////
/////////------------------------- /////////

// FREE MEMORY
void	free_map(t_map *map);

// LINEAR MATH 2
t_v		*vector_plus_vector(t_v v1, t_v v2);
t_v		*vector_minus_vector(t_v v1, t_v v2);
float	vector_mag(t_v v);
t_v		*vector_normalized(t_v v);
void	reverse_vector(t_v *v);

// LINEAR MATH
t_v		*p_min_p(t_p p1, t_p p2);
t_p		*point_plus_vector(t_p point, t_v vector, float times);
t_v		*num_times_vector(float num, t_v vector);
t_v		*v_cross_v(t_v v1, t_v v2);
float	vector_dot_vector(t_v v1, t_v v2);

// MEMORY HANDLER
t_p		*build_point(float x, float y, float z);
t_v		*build_vector(float dx, float dy, float dz);
int		free_mlx(t_vars *prog);

/////////------------------------- /////////
/////////--------- RAYS --------- /////////
/////////------------------------- /////////

// APPLY RAY
void	ray_to_all_sps(t_vars *prog, t_v *r_vec, float *t, unsigned int *color);
void	ray_to_all_pls(t_vars *prog, t_v *r_vec, float *t, unsigned int *color);
void	ray_to_all_cys(t_vars *prog, t_v *r_vec, float *t, unsigned int *color);

// RAY MATH
t_v		*get_ray_eq(int i, t_vars *prog);
int		sp_hit(t_v ray_vec, t_obj_sp sp, t_obj_C cam, float *t);
int		pl_hit(t_v ray_vec, t_obj_pl pl, t_obj_C cam, float *t);
int		get_lowest_t(float a, float b, float c, float *t);

// RAY MATH CYLINDER
int		cy_hit(t_v ray_vec, t_obj_cy cy, t_obj_C cam, float *t);
t_v		*n_from_cy(t_obj_cy cy, t_p *p_cylinder);

/////////------------------------- /////////
/////////--------- ROOT --------- /////////
/////////------------------------- /////////

// MAIN
int		main(int ac, char **av);
void	build_image(t_vars *prog);
void	put_pixel(t_vars *prog, int i, int color);

// UTILS
int		handle_x(t_vars *prog);
int		handle_input(int keysym, t_vars *prog);
// void	print_vector(t_v v, char *name);
// void	print_point(t_p p, char *name);
int		return_error(t_vars *prog, char *str);

/////////------------------------- /////////
/////////--------- LIGHTS --------- /////////
/////////------------------------- /////////

// Lights
void	apply_lights(t_vars *prog, t_v n_on_p, t_p p_obj, unsigned int *color);
void	l_on_pxl(unsigned int *pxl_c, unsigned int light_c, float ratio,
			unsigned int ori_c );
t_v		*n_point_to_light(t_p p_obj, t_obj_L *light);

// Shadows
int		is_in_shadow(t_vars *prog, t_p p_obj, t_v n_on_p, t_obj_L *light);

// Lights utils
void	light_calcs(unsigned int *final_color, unsigned int L_color,
			float inten, unsigned int ori_color);
void	add_colors(unsigned int c1, unsigned int c2, unsigned int *result);
void	unpack_colors(int rgb[3], unsigned int color);
t_v		*get_half_vector(t_p p_obj, t_vars *prog, t_v light_dir);
void	specular(t_light_p *params, unsigned int *final_color, t_obj_L *light);
void	print_vector(t_v v, char *name);
void	print_point(t_p p, char *name);

#endif
