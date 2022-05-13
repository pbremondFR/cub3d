/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:01:27 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/13 19:30:59 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

// Camera matrix :
// [planeX   dirX]
// [planeY   dirY]
// --------------------
// Inverse of camera matrix :
// _______________1_______________   [ dir_y   -dir_x]
// (cam_x * dir_y - dir_x * cam_y) * [-cam_y    cam_x]

// Applies matrix witchcraft to project the sprite's position into camera space.
// The Y corresponds to the depth, the X to the "azimuth" of the sprite
t_pnt	c_sprite_projection_matrix(float sprite_x, float sprite_y,
	const t_game *g)
{
	const float	witchcraft = (1.0f / (g->cx * g->dy - g->dx * g->cy));
	t_pnt		transform;

	sprite_x -= g->x;
	sprite_y -= g->y;
	transform.x = witchcraft * (g->dy * sprite_x + -g->dx * sprite_y);
	transform.y = witchcraft * (-g->cy * sprite_x + g->cx * sprite_y);
	return (transform);
}

// "FoR lOoPs ArE tOo DiFfIcuLt tO ReAd" god DAMN YOU NORM
// Also, I'm terribly sorry about that pos_y 3-liner.
void	c_draw_sprite_line(t_game *g, const t_sprt_attr *sprt, int frame_y,
	int sprt_y_cursor)
{
	int			i;
	int			tex_pos_x;
	int			tex_pos_y;
	const int	*tex_addr;

	tex_pos_y = c_min(sprt->s->t_h - 1,
			(int)((float)sprt_y_cursor / sprt->h * sprt->s->t_h));
	tex_addr = (const int *)(sprt->s->addr + tex_pos_y * sprt->s->i->ls);
	i = sprt->bounds_x.a - 1;
	while (++i < sprt->bounds_x.b)
	{
		if (sprt->do_draw_x[i] == false)
			continue ;
		tex_pos_x = c_min(sprt->s->t_w - 1,
				(int)((float)(i - sprt->coords_x.a) / sprt->w * sprt->s->t_w));
		if ((tex_addr[tex_pos_x] & 0xff000000) != 0xff000000)
			my_mlx_pixel_put(&g->f, i, frame_y, tex_addr[tex_pos_x]);
	}
}

void	c_render_current_sprite(t_game *g, t_sprt_attr *sprt_a,
	float ray_len_buf[])
{
	int	i;

	sprt_a->coords_x.a = (-sprt_a->w / 2) + sprt_a->screen_x;
	sprt_a->coords_x.b = (sprt_a->w / 2) + sprt_a->screen_x;
	sprt_a->bounds_x.a = c_max(0, sprt_a->coords_x.a);
	sprt_a->bounds_x.b = c_min(WIN_WIDTH - 1, sprt_a->coords_x.b);
	sprt_a->coords_y.a = (-sprt_a->h / 2) + (WIN_HEIGHT / 2) + sprt_a->v_off;
	sprt_a->coords_y.b = (sprt_a->h / 2) + (WIN_HEIGHT / 2) + sprt_a->v_off;
	sprt_a->bounds_y.a = c_max(0, sprt_a->coords_y.a);
	sprt_a->bounds_y.b = c_min(WIN_HEIGHT - 1, sprt_a->coords_y.b);
	i = sprt_a->bounds_x.a;
	while (i < sprt_a->bounds_x.b)
	{
		if (sprt_a->transform.y > 0.0f && sprt_a->transform.y < ray_len_buf[i])
			sprt_a->do_draw_x[i] = true;
		else
			sprt_a->do_draw_x[i] = false;
		++i;
	}
	i = sprt_a->bounds_y.a;
	while (i < sprt_a->bounds_y.b)
	{
		c_draw_sprite_line(g, sprt_a, i, i - sprt_a->coords_y.a);
		++i;
	}
}

// Bruh moment
int	_set_vertical_offset(t_sprt_attr *sprt_a)
{
	if (sprt_a->s->v_pos == 0)
		return (0 / sprt_a->transform.y);
	// else if (sprt_a->s->v_pos == -1)
	// 	return ((int)((float)(sprt_a->s->i->h / 2) / sprt_a->transform.y));
	// else
	// 	return ((int)((float)(-sprt_a->s->i->h / 2) / sprt_a->transform.y));
	else if (sprt_a->s->v_pos == -1)
		return ((int)((float)((sprt_a->s->t_h / 2) * sprt_a->s->scale) / sprt_a->transform.y));
	else
		return ((int)((float)(-(sprt_a->s->t_h / 2) * sprt_a->s->scale) / sprt_a->transform.y));
}

// Sprite rendering loop
// BUG: Somewhere in here is a problem with vertical offset...
// If I can't fix this, it's better to only use 'N' position
void	c_render_sprites(t_game *g, t_list *sprts_lst, float ray_len_buf[])
{
	const t_sprt	*sprt;
	t_sprt_attr		sprt_attr;

	c_calc_sprite_dist(g, sprts_lst);
	sprts_lst = c_sort_sprites(g->sprts_lst);
	g->sprts_lst = sprts_lst;
	while (sprts_lst)
	{
		sprt = (const t_sprt *)sprts_lst->content;
		if (sprt->skip == false)
		{
			if (sprt->routine)
				sprt->routine(g, (t_sprt *)sprt);
			sprt_attr.transform = c_sprite_projection_matrix(sprt->x, sprt->y, g);
			sprt_attr.screen_x = (int)((WIN_WIDTH / 2)
					* (1 + (sprt_attr.transform.x / sprt_attr.transform.y)));
			sprt_attr.w
				= abs((int)(WIN_HEIGHT / sprt_attr.transform.y * sprt->scale));
			sprt_attr.h = sprt_attr.w;
			sprt_attr.s = sprts_lst->content;
			sprt_attr.v_off = _set_vertical_offset(&sprt_attr);
			c_render_current_sprite(g, &sprt_attr, ray_len_buf);
		}
		sprts_lst = sprts_lst->next;
	}
}
