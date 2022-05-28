/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:31:05 by pbremond          #+#    #+#             */
/*   Updated: 2022/05/28 08:58:07 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d_bonus.h>

inline bool	c_is_tile_collider_pnt(const t_cub *c, t_pnt p)
{
	return (c_is_tile_collider(c, (int)p.x, (int)p.y));
}

// ========================================================================== //
// ========================================================================== //
// ========================================================================== //

// Get the X and Y distance between player's hitbox and wall border.
t_pnt	c_get_aabb_dist(float pl_x, float pl_y, const t_pnt hbox,
	const t_ipair wall)
{
	t_pnt	dist;

	if (pl_x < (float)wall.a)
		dist.x = -(wall.a - (pl_x + hbox.x));
	else if (pl_x > (float)wall.a)
		dist.x = -((pl_x - hbox.x) - (wall.a + 1));
	else
		dist.x = 0;
	if (pl_y < (float)wall.b)
		dist.y = -(wall.b - (pl_y + hbox.y));
	else if (pl_y > (float)wall.b)
		dist.y = -((pl_y - hbox.y) - (wall.b + 1));
	else
		dist.y = 0;
	return (dist);
}

// Returns true if the hitbox of the player overlaps with given wall
static bool	_does_player_collide(float pl_x, float pl_y, t_pnt hbox,
	t_ipair wall)
{
	const t_ipair	a = {pl_x - hbox.x, pl_y - hbox.y};
	const t_ipair	b = {pl_x + hbox.x, pl_y - hbox.y};
	const t_ipair	c = {pl_x - hbox.x, pl_y + hbox.y};
	const t_ipair	d = {pl_x + hbox.x, pl_y + hbox.y};

	return ((a.a == wall.a && a.b == wall.b)
		|| (b.a == wall.a && b.b == wall.b)
		|| (c.a == wall.a && c.b == wall.b)
		|| (d.a == wall.a && d.b == wall.b));
}

static float	_solve_collision(float pos, const float dist,
	const int wall_pos)
{
	if (pos < wall_pos)
		pos -= dist;
	else
		pos += dist;
	return (pos);
}

#define NUM_SOLVE	8

// Finally, something that actually works. Neither particularily beautiful
// or efficient, but does what it needs!
void	c_collision_handling(t_game *g, float vel_x, float vel_y)
{
	const t_pnt		hbox = {PLAYER_HBOX_HALFSIZE, PLAYER_HBOX_HALFSIZE};
	const t_ipair	to_solve[] = {{g->x, g->y - 1}, {g->x - 1, g->y},
	{g->x + 1, g->y}, {g->x, g->y + 1},
	{g->x - 1, g->y - 1}, {g->x + 1, g->y - 1}, {g->x - 1, g->y + 1},
	{g->x + 1, g->y + 1}};
	int				i;
	t_pnt			dist;
	t_pnt			pos;

	pos.x = g->x + vel_x;
	pos.y = g->y + vel_y;
	i = -1;
	while ((t_uint)++i < NUM_SOLVE)
	{
		if (!c_is_tile_collider(g->c, to_solve[i].a, to_solve[i].b)
			|| !_does_player_collide(pos.x, pos.y, hbox, to_solve[i]))
			continue ;
		dist = c_get_aabb_dist(pos.x, pos.y, hbox, to_solve[i]);
		if (dist.x < dist.y)
			pos.x = _solve_collision(pos.x, dist.x, to_solve[i].a);
		else
			pos.y = _solve_collision(pos.y, dist.y, to_solve[i].b);
	}
	g->x = pos.x;
	g->y = pos.y;
}
