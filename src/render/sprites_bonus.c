/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:01:27 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/11 00:48:42 by pbremond         ###   ########.fr       */
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

	printf("%sx: %.3f\ty: %.3f\n", RED, sprite_x, sprite_y);
	sprite_x -= g->x;
	sprite_y -= g->y;
	printf("%sx: %.3f\ty: %.3f%s\n", GRN, sprite_x, sprite_y, RESET);
	transform.x = witchcraft * (g->dy * sprite_x + -g->dx * sprite_y);
	transform.y = witchcraft * (-g->cy * sprite_x + g->cx * sprite_y);
	printf("%sx: %.3f\ty: %.3f%s\n", YEL, transform.x, transform.y, RESET);
	return (transform);
}

// "FoR lOoPs ArE tOo DiFfIcuLt tO ReAd" god DAMN YOU NORM
// Also, I'm terribly sorry about that pos_y 3-liner.
void	c_draw_sprite_line(t_game *g, const t_sprt_attr *sprt, int frame_y)
{
	int			i;
	int			tex_pos_x;
	int			tex_pos_y;
	const int	*tex_addr;

	tex_pos_y = c_min(sprt->s->i->w - 1,
			(int)((float)(frame_y - sprt->coords_y.a)
				/ sprt->h * sprt->s->i->h));
	tex_addr = (const int *)c_get_const_target_addr(sprt->s->i, 0, tex_pos_y);
	i = sprt->bounds_x.a - 1;
	// printf("hello\n");
	while (++i < sprt->bounds_x.b)
	{
		if (sprt->do_draw_x[i] == false)
		{
			printf("false\n");
			continue ;
		}
		tex_pos_x = c_min(sprt->s->i->w - 1,
				(int)((float)(i - sprt->coords_x.a) / sprt->w * sprt->s->i->w));
		printf("colour: %X\n", tex_addr[tex_pos_x]);
		my_mlx_pixel_put(&g->f, i, frame_y, tex_addr[tex_pos_x]);
	}
}

// if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
void	c_render_current_sprite(t_game *g, t_sprt_attr *sprt,
	float ray_len_buf[])
{
	int	i;

	sprt->coords_x.a = (-sprt->w / 2) + sprt->screen_x;
	sprt->coords_x.b = (sprt->w / 2) + sprt->screen_x;
	sprt->bounds_x.a = c_max(0, sprt->coords_x.a);
	sprt->bounds_x.b = c_min(WIN_WIDTH - 1, sprt->coords_x.b);
	sprt->coords_y.a = (-sprt->h / 2) + (WIN_HEIGHT / 2);
	sprt->coords_y.b = (sprt->h / 2) + (WIN_HEIGHT / 2);
	sprt->bounds_y.a = c_max(0, sprt->coords_y.a);
	sprt->bounds_y.b = c_min(WIN_HEIGHT - 1, sprt->coords_y.b);
	i = sprt->bounds_x.a;
	while (i < sprt->bounds_x.b)
	{
		if (sprt->transform.y > 0.0f && sprt->transform.y < ray_len_buf[i])
			sprt->do_draw_x[i] = true;
		else
			sprt->do_draw_x[i] = false;
		++i;
	}
	// for (int j = 0; j < WIN_WIDTH; ++j)
	// 	printf("%d ", sprt->do_draw_x[j]);
	// ft_putchar('\n');
	i = sprt->bounds_y.a;
	printf("i: %d\tbounds_y.b: %d\n", i, sprt->bounds_y.b);
	while (i < sprt->bounds_y.b)
	{
		// printf("marche stp\n");
		c_draw_sprite_line(g, sprt, i++);
	}
}

// There's a memory problem SOMEWHERE HERE and I have NO FUCKING CLUE WHY OR WHERE
void	c_render_sprites(t_game *g, t_list *sprts_lst, float ray_len_buf[])
{
	const t_sprt	*sprt;
	t_pnt			transform;

	// c_calc_sprite_dist(g, sprts_lst);
	// sprts_lst = c_sort_sprites(g->sprts_lst);
	// g->sprts_lst = sprts_lst;
	while (sprts_lst)
	{
		t_sprt_attr		sprt_attr;
		sprt = (const t_sprt *)sprts_lst->content;
		sprt_attr.transform = c_sprite_projection_matrix(sprt->x, sprt->y, g);
		sprt_attr.screen_x = (int)((WIN_WIDTH / 2)
				* (1 + (transform.x / transform.y)));
		ft_printf("screen_x: %d\n", sprt_attr.screen_x);
		sprt_attr.w = abs((int)(WIN_HEIGHT / transform.y));
		sprt_attr.h = abs((int)(WIN_HEIGHT / transform.y));
		sprt_attr.s = sprts_lst->content;
		c_render_current_sprite(g, &sprt_attr, ray_len_buf);
		sprts_lst = sprts_lst->next;
	}
}