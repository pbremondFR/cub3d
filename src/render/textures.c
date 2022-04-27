/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:04:49 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/27 22:24:00 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

// TODO: Optimize me, dipshit
const char	*c_fetch_texture_col(const t_img *texture, float texture_x)
{
	float	offset_f;
	int		offset_i;

	offset_f = texture_x * (float)texture->h;
	offset_i = (int)offset_f;
	offset_i = c_min(offset_i, texture->h - 1);
	return (texture->addr + (offset_i * texture->ls));
}

static float	_get_texture_x_offset(const t_ray *ray, const t_game *g)
{
	float	texture_x;

	if (ray->side == RAY_HIT_X)
	{
		texture_x = g->y + ray->c_plane_len * ray->dir_y;
		texture_x -= floorf(texture_x);
		if (ray->dir_x < 0)
			texture_x = -texture_x + 1.0f;
	}
	else
	{
		texture_x = g->x + ray->c_plane_len * ray->dir_x;
		texture_x -= floorf(texture_x);
		if (ray->dir_y > 0)
			texture_x = -texture_x + 1.0f;
	}
	return (texture_x);
}

static const t_img	*_get_texture_ptr(const t_ray *ray, const t_game *g)
{
	if (ray->side == RAY_HIT_X && ray->dir_x > 0)
		return (g->c->w);
	else if (ray->side == RAY_HIT_X && ray->dir_x <= 0)
		return (g->c->e);
	else if (ray->side == RAY_HIT_Y && ray->dir_y > 0)
		return (g->c->s);
	else
		return (g->c->n);
}

void	c_start_draw_wall(t_game *g, t_ray *ray, int x)
{
	int			line_height;
	float		texture_x;
	const t_img	*texture_ptr;
	t_tex_line	tex_line;

	line_height = (int)(WIN_HEIGHT / ray->c_plane_len);
	texture_ptr = _get_texture_ptr(ray, g);
	texture_x = _get_texture_x_offset(ray, g);
	tex_line.addr = c_fetch_texture_col(texture_ptr, texture_x);
	tex_line.ls = texture_ptr->ls;
	tex_line.w = texture_ptr->w;
	draw_textures_wall_line(g, &tex_line, x, line_height);
}
