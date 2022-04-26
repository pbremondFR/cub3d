/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:04:49 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/26 23:05:51 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>

typedef struct s_int_pair
{
	int	a;
	int	b;
}				t_ipair;

typedef struct s_texture_line
{
	const char	*addr;
	int			ls;
}				t_tex_line;

// TODO: Optimize me, dipshit
const char	*c_fetch_texture_line(const t_img *texture, float texture_x)
{
	float	offset_f;
	int		offset_i;

	offset_f = texture_x * (float)texture->h;
	offset_i = (int)offset_f;
	// printf("offset: %d\n", offset_i);
	return (texture->addr + (offset_i * texture->ls));
}

int	min(int a, int b)
{
	return (a < b ? a : b);
}

int	get_pos_in_texture(t_ipair line_coords, int i, int ls, int print)
{
	float	pos;

	if (print)
		printf("i: %d\nline: %d\t%d\n", i, line_coords.a, line_coords.b);
	pos = ((float)(i - line_coords.a) / (float)(line_coords.b - line_coords.a));
	if (print)
		printf("posf: %.5f\n", pos);
	pos = pos * ls;
	if (print)
		printf("posd: %d\n", (int)pos);
	return (min(100, (int)pos));
}

void	whatever_the_fuck(t_game *g, t_tex_line *texture, int frame_x,
	int height)
{
	const int	*tex_addr = (const int *)texture->addr;
	const int	oct_line_size = texture->ls >> 2;
	t_ipair		line_coords;
	int			i;
	int			end;
	int			pos_in_texture;

	line_coords.a = (-height >> 1) + (WIN_HEIGHT >> 1); // Start
	line_coords.b = (height / 2) + (WIN_HEIGHT / 2); // End
	if (line_coords.a < 0)
		i = 0;
	else
		i = line_coords.a;
	if (line_coords.b > WIN_HEIGHT - 1)
		end = WIN_HEIGHT - 1;
	else
		end = line_coords.b;
	while (i < end) // i - line_coords.a -> position within texture
	{
		// if (frame_x == WIN_WIDTH / 2)
		// 	pos_in_texture = get_pos_in_texture(line_coords, i, oct_line_size, 1);
		// else
			pos_in_texture = get_pos_in_texture(line_coords, i, oct_line_size, 0);
		my_mlx_pixel_put(&g->f, frame_x, i, tex_addr[pos_in_texture]);
		++i;
	}
	// if (frame_x == WIN_WIDTH / 2)
	// 	printf("===END===\n");
}

void	c_start_draw_wall(t_game *g, t_ray *ray, int x)
{
	int			line_height;
	float		texture_x;
	const t_img	*texture_ptr;
	t_tex_line	tex_line;

	line_height = (int)(WIN_HEIGHT / ray->c_plane_len);
	if (ray->side == RAY_HIT_X)
	{
		if (ray->dir_x > 0)
			texture_ptr = g->c->w;
		else
			texture_ptr = g->c->e;
		texture_x = g->y + ray->c_plane_len * ray->dir_y;
	}
	else
	{
		if (ray->dir_y > 0)
			texture_ptr = g->c->s;
		else
			texture_ptr = g->c->n;
		texture_x = g->x + ray->c_plane_len * ray->dir_x;
	}
	texture_x -= floorf(texture_x);
	tex_line.addr = c_fetch_texture_line(texture_ptr, texture_x);
	tex_line.ls = texture_ptr->ls;
	whatever_the_fuck(g, &tex_line, x, line_height);
}
