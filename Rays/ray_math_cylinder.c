/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_math_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarvalh <mcarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 20:19:40 by edugonza          #+#    #+#             */
/*   Updated: 2025/11/10 14:54:30 by mcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ray_hits_within_height(t_v ray_vec, t_obj_cy cy, t_obj_C cam, float *t)
{
	t_v	*temp;
	t_v	*proj;
	t_p	p;

	p.x = ray_vec.dx * (*t) + cam.origin->x;
	p.y = ray_vec.dy * (*t) + cam.origin->y;
	p.z = ray_vec.dz * (*t) + cam.origin->z;
	temp = p_min_p(p,*cy.center);
	proj = num_times_vector(
			vector_dot_vector(*temp, *cy.n_vec), *cy.n_vec);
	if (vector_mag(*proj) > cy.height / 2)
	{
		free(temp);
		free(proj);
		return (1);
	}
	free(temp);
	free(proj);
	*t = *t;
	return (0);
}

/*
	// 1 - Point P to Origin of Cylinder
	// 2 - Projection of PO in Axis: Proj = ( PO.A ) * A
	// 2.1 - ( PO.A )
	// PO.A = t * [delta_x * xa + delta_y * ya + delta_z * za]
							+ xa(xc - xo) + ya(yc - yo) + za(zc - zo)
	// A = [delta_x * xa + delta_y * ya + delta_z * za]
	// B = xa(xc - xo) + ya(yc - yo) + za(zc - zo)
	// PO.A = A * t + B ==> this is a number "num"

	A = ray_vec.dx * cy.n_vec->dx + ray_vec.dy * cy.n_vec->dy
			+ ray_vec.dz * cy.n_vec->dz;
	B = cy.n_vec->dx*(cam.origin->x - cy.center->x)
			+ cy.n_vec->dy*(cam.origin->y - cy.center->y)
			+ cy.n_vec->dz*(cam.origin->z - cy.center->z);

	// 2.2 Proj = ( PO.A ) * A ==> (num*xa, num*ya, num*za)
	// 3 Perpendicular = PO - Proj
	// 3.1
	// xperp = xpo - xproj
	// xperp = delta_x * t + xc - xo       -       num*xa
	// xperp = delta_x * t + xc - xo       -       (A * t + B)* xa
	// xperp = delta_x * t + xc - xo       -       A * t * xa + B * xa
	// xperp = t * (delta_x - A * xa)  + xc - xo - B * xa
	// xperp = t * Cx  + Dx

	Cx = ray_vec.dx - A * cy.n_vec->dx;
	Dx = cam.origin->x - cy.center->x - B * cy.n_vec->dx;
	Cy = ray_vec.dy - A * cy.n_vec->dy;
	Dy = cam.origin->y - cy.center->y - B * cy.n_vec->dy;
	Cz = ray_vec.dz - A * cy.n_vec->dz;
	Dz = cam.origin->z - cy.center->z - B * cy.n_vec->dz;

	// 4 |Perp| = r
	// xperp^2 + yperp^2 + zperp^2 = r^2
	// (t * Cx  + Dx)^2 + (t * Cy  + Dy)^2 + (t * Cz  + Dz)^2 - r^2 = 0
	// (Cx^2+Cy^2+Cz^2) * t^2
			+ t * (2CxDx + 2CyDy + 2CzDz) + Dx^2 + Dy^2 + Dz^2 - r^2 = 0
	// ax^2 + bx + c = 0
	// a = (Cx^2+Cy^2+Cz^2)
	// b = (2CxDx + 2CyDy + 2CzDz)
	// c = Dx^2 + Dy^2 + Dz^2 - r^2

	result = get_lowest_t(
						(Cx*Cx+Cy*Cy+Cz*Cz),
						(2*Cx*Dx + 2*Cy*Dy + 2*Cz*Dz),
						Dx*Dx + Dy*Dy + Dz*Dz - (cy.diameter/2)*(cy.diameter/2),
						t);
*/

/*
Helper_array=
	[0] A;
	[1] B;
	[2] Cx;
	[3] Dx;
	[4] Cy;
	[5] Dy;
	[6] Cz;
	[7] Dz;
*/
int	ray_hits_infinite_cylinder(t_v ray_vec, t_obj_cy cy, t_obj_C cam, float *t)
{
	float	h[8];
	int		result;

	h[0] = ray_vec.dx * cy.n_vec->dx + ray_vec.dy
		* cy.n_vec->dy + ray_vec.dz * cy.n_vec->dz;
	h[1] = cy.n_vec->dx * (cam.origin->x - cy.center->x)
		+ cy.n_vec->dy * (cam.origin->y - cy.center->y)
		+ cy.n_vec->dz * (cam.origin->z - cy.center->z);
	h[2] = ray_vec.dx - h[0] * cy.n_vec->dx;
	h[3] = cam.origin->x - cy.center->x - h[1] * cy.n_vec->dx;
	h[4] = ray_vec.dy - h[0] * cy.n_vec->dy;
	h[5] = cam.origin->y - cy.center->y - h[1] * cy.n_vec->dy;
	h[6] = ray_vec.dz - h[0] * cy.n_vec->dz;
	h[7] = cam.origin->z - cy.center->z - h[1] * cy.n_vec->dz;
	result = get_lowest_t(
			(h[2] * h[2] + h[4] * h[4] + h[6] * h[6]),
			(2 * h[2] * h[3] + 2 * h[4] * h[5] + 2 * h[6] * h[7]),
			h[3] * h[3] + h[5] * h[5] + h[7] * h[7]
			- (cy.diameter / 2) * (cy.diameter / 2), t);
	return (result);
}

int	cy_hit_caps(t_v ray_vec, t_obj_cy cy, t_obj_C cam, float *t)
{
	t_obj_pl	cap;
	t_p			*pcheck;
	t_v			*vcheck;
	int			res;

	res = 0;
	cap.center = point_plus_vector(*cy.center, *cy.n_vec, cy.height / 2);
	cap.n_vec = build_vector(cy.n_vec->dx, cy.n_vec->dy, cy.n_vec->dz);
	res = pl_hit(ray_vec, cap, cam, t);
	if (!res)
	{
		pcheck = point_plus_vector(*cam.origin, ray_vec, *t);
		vcheck = p_min_p(*pcheck, *cap.center);
		if (vector_mag(*vcheck) > cy.diameter / 2)
		{
			res = 1;
			*t = 1000;
		}
		free(pcheck);
		free(vcheck);
	}
	free(cap.center);
	free(cap.n_vec);
	return (res);
}

int	cy_hit(t_v ray_vec, t_obj_cy cy, t_obj_C cam, float *t)
{
	float	t_temp;

	t_temp = -1;
	if (!ray_hits_infinite_cylinder(ray_vec, cy, cam, &t_temp))
	{
		if (!ray_hits_within_height(ray_vec, cy, cam, &t_temp))
			*t = t_temp;
	}
	t_temp = -1;
	if (!cy_hit_caps(ray_vec, cy, cam, &t_temp))
	{
		if (t_temp > 0 && (t_temp < *t || *t == -1))
			*t = t_temp;
	}
	t_temp = -1;
	reverse_vector(cy.n_vec);
	if (!cy_hit_caps(ray_vec, cy, cam, &t_temp))
	{
		if (t_temp > 0 && (t_temp < *t || *t == -1))
			*t = t_temp;
	}
	reverse_vector(cy.n_vec);
	if (*t > 0)
		return (0);
	return (1);
}

t_v	*n_from_cy(t_obj_cy cy, t_p *p_cylinder)
{
	t_v	*proj;
	t_v	*proj_norm;
	t_v	*temp;
	t_v	*cp;

	cp = p_min_p(*p_cylinder, *cy.center);
	proj_norm = NULL;
	if (fabs(vector_dot_vector(*cp, *cy.n_vec)) >= (cy.height / 2) - 0.001)
	{
		if (vector_dot_vector(*cp, *cy.n_vec) > 0)
			proj_norm = build_vector(cy.n_vec->dx, cy.n_vec->dy, cy.n_vec->dz);
		else
			proj_norm = build_vector(-cy.n_vec->dx, \
				-cy.n_vec->dy, -cy.n_vec->dz);
	}
	else
	{
		proj = num_times_vector(vector_dot_vector(*cp, *cy.n_vec), *cy.n_vec);
		temp = vector_minus_vector(*cp, *proj);
		proj_norm = vector_normalized(*temp);
		free(temp);
		free(proj);
	}
	free(cp);
	return (proj_norm);
}
